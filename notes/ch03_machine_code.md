# 3 Machine-level representation of programs

Computers execute machine code, sequence of bytes that encode low-level instructions that manipulate data, manage memory, manage storage, and communicate over a network. A compiler translates source code to machine code according to the programming language's rules, the target machine's instruction set, and the operating system's conventions. The GCC C compiler first produces assembly code (a human-readable form of machine code), before invoking an assembler and linker to produce the final executable.

> Why does GCC first produce assembly code, why not just jump straight from C source to machine code?
>
> 1. Transparency & debugging: Developers can inspect or tune what the compiler is
>    generating
> 2. Portability of the compiler itself: Instead of having to generate machine
>    code for every platform, the compiler can generate assembly text and let the
>    assembler (which is platform-specific) handle the exact encoding
> 3. Modularity: Splitting tasks into stages (compiler -> assembler -> linker)
>    makes the toolchain more flexible and maintainable

High-level languages like C and Java abstract machine-level implementation. Compared to assembly, they are more productive and reliable, offering features like type-checking that catch errors early. Modern compilers can generate code this is often as efficient as hand-written assembly. Most importantly, high-level code is portable across different machines, while assembly is tightly bound to a specific architecture

Even though compilers generate assembly automatically, knowing how to read and understand machine code is valuable:

- It helps programmers analyze compiler optimizations
- Tune performance-critical code
- Understand runtime behavior (like memory layout in concurrency)
- Detect security vulnerabilities that exploit low-level details

Reading compiler-generated assembly requires understanding how C constructs are translated to machine code. Optimizing compilers can rearrange code, eliminate unnecessary computation, and transform constructs (like recursion to iteration) for efficiency. Studying this assembly is a form of reverse engineering—analyzing how the system was created by working backward. Mastering these details is essential for deeper understanding and for correctly reasoning about performance and behavior

1. There are two main machine language (a set of binary instructions that a CPU can understand):

   - IA32: 32-bit intel architecture
   - x86-64: the 64-bit extension of IA32, which adds new instructions, larger registers, and the ability to address more memory

> Takeaway: you don't need to memorize every IA32 quirks, just the one relevant to modern compilers and OSes

2. 32-bit vs 64-bit
   - 32-bit = ~4 GB memory limit.
   - 64-bit = can access huge memory (~256 TB).
   - Transition from 32 → 64-bit is ongoing; many OSes still run 32-bit apps.
   - x86-64 includes enhancements that help optimizing compilers generate faster code.

> Takeaway: x86-64 is not just “bigger addresses”—it’s also better for compiler optimization and performance

3. Optimizations and reading compiler output
   - Higher optimization levels in gcc can drastically transform code.
   - Reading assembly helps understand these transformations.

> Takeaway: Knowing assembly lets you reason about compiler optimizations and performance

4. Inline and full assembly in C
   - Sometimes you need to write assembly yourself (whole functions or inline).
   - Useful to access low-level features not exposed by C.

> Takeaway: While rare, embedding assembly is a tool for special performance or hardware-level tasks.

5. Floating-point instructions
   - Older: x87 instructions (arcane, mostly historical).
   - Newer: SSE instructions (multimedia, now standard for floating-point on modern IA32 and x86-64).

> Takeaway: Focus on SSE if you want to understand floating-point computation; x87 is mostly for historical understanding.

> x86 processors evolved gradually, keeping backward compatibility while adding new features (64-bit, SSE, vector instructions). For your purposes, focus on IA32 instruction set, memory model (flat addressing), and the 64-bit x86-64 extension, because that’s what modern compilers (gcc) and OSs (Linux) actually use.

# 3.2 Program Encodings

The GCC C compiler (default on Linux) provides different levels of optimization through flags such as `O1`, `O2`, and higher. Higher optimization levels generally make programs run faster, but they also increase compilation time and can make debugging harder. In fact, the compiler may transform the code so much that the machine code looks very different from the original source, may it harder to debug. For learning, -O1 is a good balance because the generated code still resembles the source, but in practice `-O2` is usually preferred for performance

Compilation isn't one step, it's a pipeline of transformations. The processes typically has four main phases:

1. Preprocessing: Handles directives like `#include`, `#define`, and conditional compilation (`#if/#endif`). The output is still C code, but now self-contained (all headers and macros are expanded).

2. Compilation: Translates the preprocessed C code into assembly, a human-readable form of machine instructions.

3. Assembly: converts assembly into object code. Object code contains actual machine instructions, but it's incomplete: addresses for functions/variables defined elsewhere are left as placeholders (relocations).

4. Linking: combines all object files (from your code and from libraries), resolves references to external functions and variables, and produces a single executable that the CPU can run

## 3.2.1 Machine-level code

### ISA

The Instruction Set Architecture (ISA) acts like contract between the hardware and software. It defines:

- Processor state: what information the CPU maintains (e.g. program counter, registers)
- Instruction format: how instructions are encoded in binary and what operations are available
- Instruction effects: what happens when each instruction executes

The ISA presents the illusion that the CPU executes instructions sequentially. In reality modern processors run instructions in parallel and out of order. However, they enforce rules so that the visible outcome is the same as if instructions had run sequentially. This abstraction makes life easier for programmers; they can rely on the ISA's simpler model without worrying about the CPU's internal complexity.

### Virtual memory

Virtual memory is an operating system abstraction that gives each program the illusion of having exclusive access to the entire memory. From the program's perspective, memory looks like a large, contiguous array of bytes called the virtual address space.

Each program runs its own virtual address space, which typically includes:

- the program's machine code
- extra information reserved for the OS
- a runtime stack for function calls and return values
- and dynamically allocated memory (the heap)

Behind the scenes, the OS and hardware translate these virtual addresses into actual physical memory locations using DRAM, CPU caches, disk storage (for paging), and the Memory Management Unit (MMU). Even though a 32-bit machine can address up to 4 GB of virtual memory, in practice each program only gets access to certain valid portions of it, managed and protected by the OS.

This abstraction simplifies programming, because developers don’t need to worry about where data physically resides—they just see a big linear array of memory.

### Machine code

When you drop down from C to IA32 machine, you start to see part of the processor states that C normally hides:

1. Program counter (`%eip`)
   - holds the address to the next instruction to be executed
2. Integer registers (8 total in IA32, each 32-bits)
   - Used for addresses (like pointers), integer values, local variables, and return values
3. Condition code registers
   - Store flags (1-bit values that record the outcome of a recent arithmetic/logic ops)
   - Used for control flow. For example `if (x == y) {...}` in C becomes: do an operation -> check zero flag -> jump if needed
4. Floating-point registers
   - dedicated for storing and manipulating floating-point numbers

The notion of types only exist in higher-level languages. At machine level, there is no distinction between signed vs. unsigned, integers vs. pointers, or arrays vs. structs. The hardware only sees sequences of bits. It the compiler and programming language rules that give those patterns meaning and enforce type distinctions.

Machine instructions perform very simple, low-level operations—like adding the contents of two registers, moving data between registers and memory, or jumping to another instruction when a condition is met. The compiler’s role is to translate high-level constructs (loops, functions, arithmetic expressions) into the right sequence of these basic instructions, so that the program’s logic is preserved at the machine level.

## 3.2.2 Code example

- Each line of assembly corresponds to a CPU instruction.
- What the CPU actually executes is not assembly text, but a sequence of bytes—the machine code encoding of those instructions.
- The CPU has no knowledge of the original C source; it only follows the byte-coded instructions defined by the ISA.
- Machine code can be inspected with disassemblers (e.g., objdump), which decode the byte sequence back into assembly-like mnemonics.
- IA-32 instructions vary in length (1–15 bytes). Common/simple operations use compact encodings, while rare/complex ones require more bytes.
- Instruction encodings are unambiguous: starting from any byte, there is exactly one valid decoding.
- Disassemblers rely purely on binary encoding; they don’t need the original source or assembly text.
- Instruction names may differ slightly (e.g., push vs. pushl) but still represent the same operation.
- To produce an executable, the linker merges multiple object files (from your code and libraries), resolves references to functions and variables, assigns addresses, and outputs a single program.
- Executables are larger than individual object files because they also contain startup, shutdown, and OS-interaction information.

## 3.2.3 Notes on formatting

Compiler-generated assembly can be hard to read. It often contains:

- Directives (lines starting with `.`) for the assembler and linker, not the programmer
- Lacks comments that explain how instructions map to the original C source

To make it clearer, we can:

- Ignore most directives, and focus on the instructions, which correspond directly to CPU actions
- Add comments that explain how instructions maps back to the original C source

This makes the assembly code look similar to how assembly programmers write and reason about code

# 3.3 Data formats

Because IA32 is an extension of Intel's original 16-bit architecture, Intel's terminology is a bit legacy-driven:

- a word means 16 bits
- a double word (dword) means 32 bits
- a quad word (qword) means 64 bits

Even though modern processors are 32-bit (or 64-bit), many instructions mostly operate on bytes (8-bits) or double words (32-bits)

In IA32, C primitive data types are stored in fixed-width units:

- `char` = 1 byte
- `short` = word
- `int` and all pointers = double word
- `long int` = double word, because the CPU natural word size is 4 bytes
- `float` = 4 bytes (single precision)
- `double` = 8 bytes (double precision)
- `long double` = 10 bytes (extended precision, usually padded to 12 bytes by gcc)

In IA32 assembly, most instructions come in different forms depending on the operand size. To make that explicit, the assembler uses a one-letter suffix:

- b → byte (8 bits)
- w → word (16 bits)
- l → long (32 bits / double word)

And, as the text says, l gets reused for two different things:

- integer “long word” (32-bit) values
- 8-byte double-precision floating point values

There’s no confusion because floating point ops use their own instruction set (fldl, fstpl, etc.) and registers (the x87 FPU or SSE).

# 3.4 Accessing information

An IA32 CPU has 8 32-bit registers: six general-purpose (%eax, %ecx, %edx, %ebx, %esi, %edi) registers and two for stack management (%esp, %ebp). For backwards compatibility the low-order 16 bits of all registers and the low-order 8 bits of the first four can be accessed independently, while the stack registers follow strict conventions for function calls, stack frames, and local variable access.

IA32 instructions operate on operands, which specify the source of data or the destination for results:

- Immediate: A constant value, written with `$` followed by an integer value in standard C notation (e.g. `$-577`, `$0x57`)
- Register: The content of a CPU register. Depending on the instruction, registers can be accessed as 32-bit, 16-bit, or 8-bit values. Using the notation $E_{a}$ for an arbitrary register a, $R[E_{a}]$ denotes its current value
- Memory: A value stored at a computed memory address (effective address). Notation $M_{b}[Addr]$ refers to b-byte value starting at address `Addr`

Memory operands support multiple addressing modes combining:

- Immediate offset (`Imm`)
- Base register (`Eb`)
- Index register (`Ei`)
- Scale factor (`s` = 1, 2, 4, 8)

The effective address is computed as:

```
Addr = Imm + R[Eb] + R[Ei] * s
```

Examples:

- `(%eax)` → `M[R[%eax]]`
- `(%eax, %ebx)` → `M[R[%eax] + R[%ebx]]`
- `Imm(%eax)` → `M[Imm + R[%eax]]`
- `Imm(%eax,%ebx,s)` → `M[Imm + R[%eax] + R[%ebx] * s]`

Simpler forms are just special cases where some components are omitted. These modes are especially useful for accessing arrays and struct elements efficiently.

## 3.4.2 Data movement instructions

Data movement is a core operation in IA32, and operand notation make these instructions flexible. Instructions are grouped into classes, where each class does the same operation, but on different operand size. For example, the `mov` class has `movb`, `movw`, and `movl` which copy 1-, 2-, 4- bytes values respectively to their destinations.

Instructions in the `mov` class require two operands: a source (immediate, register, memory) and a destination (register, memory). They can't copy directly between two memory locations, so memory-to-memory moves require two steps, via a register. Variants like `movz` and `movs` handle copying smaller values into larger destinations, using sign-extension or zero-extension to fill upper bits

> IA32 forbids memory-to-memory `mov` because allowing two memory operands would force the CPU to compute two effective addresses and perform to memory access in a single instruction, which complicates pipeline and slows execution since memory is far slower than registers
> Register-to-register `mov` is allowed because both operands are already in the CPU, so data movement happens really fast without waiting on memory, making it cheap and efficient

The stack is a last-in, first-out (LIFO) structure used primarily to manage procedure calls. In IA32, the stack is stored in memory and grows downward, so the top element has the lowest address. The stack pointer (`%esp`) always holds the address of the current top.

- Push (`pushl`): decrements the stack pointer by 4 (for a double word) and stores the value at the new top. It's equivalent to `subl $4,%esp`, followed by `movl src,(%esp)`, but encoded more compactly (1 byte instead of 6 bytes)
- Pop (`popl`): reads the value at the stack pointer into the destination, then increments the stack pointer by 4. The popped value remains in memory, until overwritten, but is no longer considered part of the stack
- Since the stack shares the same memory space as code and data, values deeper in the stack can also be accessed with normal memory addressing (e.g. mov `4(%esp),%edx`)

In IA32 assembly, dereferencing a pointer involves two steps:

- load the pointer's value (the memory address it holds) from the stack into a register
- Use that register as the effective address to read or write the actual value in memory

Local variables are often stored in registers rather memory, since register access is much faster than memory access
