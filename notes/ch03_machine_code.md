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

# 3.5 Arithmetic and Logical operations

IA32 assembly organizes arithmetic and logic instructions into four categories: load effective address, unary, binary, and shifts. Each class has size-specific variants—`b` (byte), `w` (word), `l` (double word)—to indicate the operand, with the exception of `leal`, which exists only in double word form. Unary instructions operate on a single operand, while binary instructions require two operands

## 3.5.1 Load effective address

The `leal` instruction computes an effective address expression (base + index \* scale + displacement) and stores the result in a register (not memory). It’s commonly used for pointer arithmetic and as a compact way to express integer arithmetic

## 3.5.2 Unary and binary operations

Unary instructions operates on a single operand, which can either be an address or a register or a memory location, and this operand serves as both the source and the destination. For example: `incl (%esp)` increments the 4-byte value at the top of the stack.

Binary instructions operate on two operands. The first operand can be an immediate, a register, or a memory location. While the second operand can either be a register or a memory location, but never a memory location when the first operand is also a memory. The second operand serves as both a source and the destination. For example: `subl %eax, %edx` $=$ `%edx = %eax - %edx`

## 3.5.3 Shift operations

Shift instructions require two operands:

1. shift amount: either an 8-bit immediate (0 - 31) or the %cl register. Only %cl is allowed as a register for the shift amount
2. value to shift: can be a register or a memory location

- left shifts: shl and sal are identical; they shift left and fill the least-significant bits with zeros
- right shifts:
  - sar = arithmetic right shift; fills the most-significant bits with the sign bit
  - shr = logical right shift; fills the most-significant bits with zeros

> Notes: the CPU only looks at the low-order 5 bits of the shift amount, because a 32-bit value can only be shifted 0-31 positions, anything else will be meaningless

## 3.5.4 Discussion

The compiler optimizes arithmetic by reusing registers and substituting faster instructions, while preserving the overall result

## 3.5.5 Special arithmetic operations

Regular `imul` only produces a 32-bit product, but IA32 assembly provides special one-operand multiply and divide instructions that use the `%edx:%eax` register pair as a 64-bit value.

In multiplication, `%edx` holds the high-order 32 bits and `%eax` holds the low-order 32-bits of the product.

In division, `%edx:%eax` stores the dividend. For signed division, the high-order bits in `%edx` must be filled by sign-extending `%eax` using the cltd instruction. While for unsigned division, `%edx` is filled with zeros. The divisor is given as the operand, and the result is split with the quotient in `%eax` and the remainder in `%edx`

# 3.6 Control

Not all programs run instructions sequentially, constructs like conditionals, loops, and switches require conditional execution. At machine level, this is achieved by testing data and then either altering the control flow (with jumps) or data flow

## 3.6.1 Condition codes

The CPU maintains a single condition code register that contains several 1-bit flags, each recording the outcome of a recent arithmetic/logic operation:

- CF (Carry Flag): set if the most recent operation generated a carry out of the MSB (used to detect unsigned overflow)
- ZF (Zero Flag): set if the most recent operation yielded zero
- SF (Sign Flag): set if the most recent operation yielded a negative value
- OF (Overflow Flag): set if the most recent operation caused a two's complement overflow

All arithmetic/logic operation set the condition codes, except `leal`, which only computes an effective address. For example:

- XOR: set CF and OF to 0
- shift operations: set the CF to the last bit shifted out, and OF to 0
- INC/DEC: set the ZF and OF, but leave the CF unchanged

CMP instructions behaves like the SUB instructions, but only set condition codes (no destination update). It sets ZF to zero if the operands are equal, and the other flags reflect ordering. TEST instructions behave similar to the AND instructions but only sets condition codes (no destination is updated). Often used to check if a value is zero, negative, positive, or matches a bit mask

## 3.6.2 Accessing the condition codes

One common way to use condition codes is with SET instructions, which set a single byte to 0 0r 1 depending on certain flag combinations. The instruction suffixes (e.g. `setl`, `setb`) specify the conditions begin tested, not the operand size. A SET instruction writes to a single-byte register or memory location, and to obtain 32-bit results, the upper 24 bits must be cleared

1. Background:
   - CMP computes $a - b$, (without storing it) and sets condition codes
   - Then the SET instructions reads those flags and decides whether to write 0 or 1
2. Equality (`sete` or "set when equal"):
   - If $a = b$, then $a - b = 0$, so $ZF = 1$
   - Therefore `sete` just checks the Zero Flag
3. Signed comparisons (`setl` or "set if less than"):
   - For signed integers, we can about SF and OF
   - If no overflow ($OF = 0$): $a < b$, $SF = 1$
   - If overflow occurs ($OF = 1$): the sense of "less" flips, so you must use $SF$ ^ $OF$
   - So the processor actually computes $SF$ ^ $OF$ to test signed $<$
   - Other signed comparisons ($<=$, $>$, $>=$) are built from ZF and SF ^ OF
4. Unsigned comparisons (`setb` or "set if below"):
   - For unsigned integers, subtraction sets the CF when $a < b$
   - So:
     - Unsigned $<$ uses CF
     - Unsigned $<=$ uses CF and ZF

At machine level, values are just bits, so there's no inherent distinction between signed and unsigned types. Most arithmetic instructions work the same for both, but some operations (e.g. shifts, multiplication/division, and comparisons) require different instructions or use different condition codes to handle signed and unsigned values correctly

## 3.6.3 Jump instructions and their encodings

Jump instructions alter control flow by transferring execution to a labeled target. Labels in assembly mark destinations, and the assembler encodes them as actual addresses in machine code

Jump instructions transfer execution either unconditionally (`jmp`) or conditionally based on condition codes. An unconditional jump can be direct (to a label e.g. `jmp .L1`) or indirect (via a register or memory location e.g. `jmp *(%eax)`, `jmp *%eax`), while conditional jumps are always direct. Their suffixes match those of SET instructions, denoting condition rather than operand sizes. In assembly, jump targets appear as labels, but the assembler/linker encodes them as actual addresses, often using PC-relative offsets (difference between the target's instruction address and the address of the instruction immediately after the jump).

Assemblers encode jump targets as relative offsets rather than absolute addresses because:

- compact encoding: only 1-2 bytes is needed for the offset rather than a 4-byte absolute address
- relocatable: an object file can be loaded anywhere in memory without rewriting jump instructions because the offset remains the same

## 3.6.4 Translating conditional branches

C Conditionals are encoded in assembly as conditional and unconditional jumps

## 3.6.5 Loops

C loops don't have a direct machine-code equivalent; compilers implement them using conditional jumps, usually by first translating all loop types into a do-while loop. This approach simplifies code generation by providing a simple, uniform structure for handling all loop types

### Do-while loops

Do-while loops execute the body at least once before testing the condition. If the condition evaluates to true, the control jumps back to the start of the loop. Compilers implement do-while loops using a combination of a loop label, the loop body, a condition check, and a conditional jump

```
do
   body-statement
   while (test-expression);
```

becomes

```
loop:
   body
   t = test-expression
   if (t)
      goto loop;
```

%eax holds the result because it's the return register

### While loops

While loops, unlike do-while loops, may not execute the body at all. To implement them, compilers typically translate them into a do-while loop structure but insert an initial condition branch to skip the body if needed

```
while (test-expr)
   body-statement

if (!test-expr)
   goto done;
do
   body-statement
   while (test-expr);
done:
```

### For loops

Compilers implement for loops by first translating them into an equivalent while loop, and then into a do-while loop:

```
for (init-expr; test-expr; update-expr)
   body-statement

init-expr;
while (test-expr) {
   body-statement
   update-expr;
}

init-expr
if (!test-expr)
   goto done;
do {
   body-statement
   update-expr;
} while (test-expr);
done:

init-expr
if (!test-expr)
   goto done;
loop:
   body-statement
   update-expr;
   t = text-expr;
   if (t)
      goto loop;
done:
```

## 3.6.6 Conditional move instructions

Modern processors execute multiple instructions in parallel using pipelining, which requires predicting the next instruction path to keep the pipeline full of instructions to execute. Conditional branches disrupt this flow because a wrong prediction requires CPU to flush and refill the pipeline, wasting 20-40 clock cycles. This penalty is especially severe when conditions are unpredictable (e.g. `if (x < y)`).

To avoid this stalls, modern architecture use conditional move (CMOV) instructions, which eliminates branching by changing data flow instead of control flow. The processor computes both outcomes in parallel and conditionally copies the correct value, allowing the pipeline to remain full and performance consistent. Compilers use CMOV when the cost of computing both outcomes is lower than than the expected penalty of branch mispredictions.

> A clock cycle is the smallest timing unit of a processor
> Each cycle corresponds to a tick of the processor's internal clock
> The clock frequency (e.g. 3 GHZ) tells you how many cycles happen per second
> Every operation takes one or more cycles to complete
> So a branch misprediction that cost 40 clock cycles means the CPU loses the equivalent of 40 clock ticks' worth of work

Assume:

- $p$ = probability of misprediction
- $T_{OK}$ = cycles required to execute code when prediction is correct
- $T_{MP}$ = extra cycles lost per prediction or misprediction penalty

Then the average time required to execute code as a function of $p$:

$$
T_{avg}(p) = (1 - p)T_{OK} + p(T_{OK} + T_{MP}) = T_{OK} + pT_{MP}
$$

The slowdown factor (how many times slower one case is compared to another) is:

$$
T_{MP} / T_{OK}  + 1
$$

Conditional move instructions copy a value from a source register or memory location to a destination register only if the specified condition holds. They operate on 32- or 16-bit operands, and the operand size is inferred from the destination register. Unlike jump instructions, CMOV instructions don't alter control flow; the processor simply reads the source, checks the condition codes, and updates the destination accordingly. Semantically, this corresponds to:

```
vt = then-expr;
v = else-expr;
t = test-expr;
if (t) v = vt;
```

However, CMOV instructions cannot be used when either outcome can trigger an error (e.g. null pointer dereference) or produce a side effect (e.g. updating a global variable). In such cases, branching is required to preserve correct behavior. Compilers only use CMOV instructions selectively: when both outcomes are error-free and side-effect-free, and when cost of performing both outcomes is lower than the potential penalty of branch misprediction

## 3.6.7 Switch statements

A switch statement enables multi-branching based on the value of an integer expression. It provides a more readable and organized alternative to long-chains of if-else statements.

Compilers implement switch statements either as a chain of conditional tests or by using a jump table. When a switch has many cases or the case values form a dense range of values, compilers typically use a jump table for efficiency.

A jump table is an array of code addresses, where entry `i` contains the address of the code to execute when the switch index equals i. The program uses the switch value to index into this table and then directly jump to the corresponding case. This makes the time to select a case independent of the number of cases, making it faster than checking condition in sequence.

# 3.7 Procedures

A procedure transfers both control and data between program parts. On IA32, hardware instructions handle only the control transfer, while data passing and local-variable management rely on stack manipulation

## 3.7.1 Stack frame structure

In IA32, the stack is used to manage procedure calls by storing information each procedure needs while it executes. Each procedure call get its own stack frame, a region that holds:

- arguments passed to the procedure
- return address (where to resume after returning)
- saved registers (to resume the caller's state)
- local variables (when registers are insufficient or their addresses are needed)

Two key registers define the frame:

- %ebp (frame pointer): fixed reference point for accessing local variables and parameters
- %esp (stack pointer): holds the address of the current top as stack shrinks and grows

When procedure P calls procedure Q:

- P pushes Q's argument, then the return address
- Q, upon starting, saves P's %ebp, sets %ebp = %esp, and allocates space for locals by decrementing %esp
- Q may also use frame to store arguments for any procedure it calls

## 3.7.2 Transferring Control

The `call`, `ret`, and `leave` instructions manage control flow between procedures

- `call`
  - Pushes the return address (the address right after the call) onto the stack
  - Then jumps to the start of the called procedure
  - Can be direct (`call Label`) or indirect (`call *operand`, using a register or memory location)
- `ret`
  - pops the return address off the stack and jumps back to that address
  - works correctly if the stack pointer points to where the preceding call stored the return address
- `leave`
  - Prepares the stack for returning by:
    1. Setting `%esp = %ebp` (restore the stack pointer to the start of the current frame)
    2. `pop %ebp` (restore the caller's frame pointer and move `%esp` to the end of the caller's frame)
  - Equivalent to the sequence:
    ```asm
    movl %ebp, %esp
    popl %ebp
    ```
- After this, `ret` completes the return by transferring control to the saved address
- The `%eax` register holds return values for functions that return integers or pointers

## 3.7.3 Register usage conventions

Since registers are shared among all procedure calls, conventions are needed to prevent one procedure from destroying another's data during a call.

By IA32 convention:

1. Caller-save registers: `%eax`, `%edx`, `%ecx`
   - The caller must save these if it wants their values preserved across calls, because the callee can freely modify them
2. Callee-save registers: `%esi`, `%ebx`, `%edi`
   - The callee must save and restore these if it must use them
   - The caller can assume their values stay unchanged after the call
3. `%esp` and `%ebp` are maintained according to stack frame convention

## 3.7.4 Procedure example

- **Stack Frame:**
  Each procedure (function) gets its own section of the stack to store:

  - Local variables
  - Saved registers
  - Return address
  - Caller’s frame pointer (`%ebp`)

- **Frame Pointer Chain:**

  - `pushl %ebp` saves the **caller’s** frame pointer.
  - `movl %esp, %ebp` sets up the **callee’s** frame pointer.
  - This creates a linked chain of frames for stack tracing/debugging.

- **Caller Actions:**

  1. Save old `%ebp`, set up new one.
  2. Allocate stack space for locals (e.g., `subl $24, %esp`).
  3. Compute and push arguments (e.g., `leal -4(%ebp), %eax`).
  4. Call the function (`call swap_add`), which pushes the return address.

- **Callee Setup:**

  1. Save caller’s `%ebp` → `pushl %ebp`
  2. Set `%ebp` → `movl %esp, %ebp`
  3. Save callee-saved registers (e.g., `%ebx`)

- **Accessing Arguments:**

  - Arguments are found _above_ `%ebp`:

    - `8(%ebp)` → first argument (`xp`)
    - `12(%ebp)` → second argument (`yp`)

  - Locals are found _below_ `%ebp` (negative offsets).

- **Returning:**

  - Restore saved registers (`popl %ebx`, `popl %ebp`)
  - `ret` pops the return address and jumps back to caller.
  - Caller can use `leave` to clean up its own frame.

- **Stack Alignment Convention:**

  - gcc often allocates stack space in multiples of **16 bytes** for data alignment, even if not all space is used.

## 3.7.5 Recursive procedures

The stack naturally handle recursive calls by giving each its own space and automatically cleaning up when each return

# 3.8 Array allocation and access

C array are just contiguous blocks of memory. Accessing an array element `a[i]` is really just pointer arithmetic `*(a + i)`. Compilers optimize these address computations for efficiency that the machine code might not look like the original indexing expression. Understanding this mapping is crucial for reading and reasoning about compiled code

## 3.8.1 Basic principles

For declaration:

```c
T A[N]
```

- Each element has size L bytes, where `L = sizeof(T)`
- The array occupies $L \times N$ bytes in contiguous memory
- If the starting address of the array is $x_{A}$

The address of element `A[i]` is given by:

$$
x_{A} + L \cdot i
$$

## 3.8.2 Pointer arithmetic

When you do arithmetic on a pointer, the computed value is scaled according to the size of the data type referenced by the pointer.

If

- $p$ points to a type $T$
- $x_{p}$ is the memory address it holds
- $L$ is the size (in bytes) of type T

then

$$
p + i \rightarrow x_{p} + L \cdot i
$$

| C Expression | Meaning                   | Equivalent Assembly Behavior |
| ------------ | ------------------------- | ---------------------------- |
| `A[i]`       | “element i of array A”    | `*(A + i)`                   |
| `&A[i]`      | address of element i      | base + scaled index          |
| `*(A + k)`   | dereference at offset `k` | load from base + (k × size)  |

Pointer differences within the same data structure `&E[i] - E` yield integer indices, automatically scaled by element size

## 3.8.3 Nested Arrays

For declaration:

```c
T D[R][C]
```

- C stores all element row by row (i.e., all of row 0 first, then row 1, etc.)
- Each row is an array of C elements of type T
- The whole array occupies $L \times R \times C \text{ bytes}$

If the array starting address is $x_{D}$, the address of the array element `D[i][j]`:

$$
x_{D} + L \cdot (C \cdot i + j)
$$

## 3.8.4 Fixed-sized arrays

- For fixed-size arrays, compilers know each array's dimension at compile time, so it can precompute offsets and optimize memory access
- Instead of recalculating the full index expression (like `A[i][j] = i * N + j`) each time, the compiler turns it into simple pointer increments
- Accessing elements in a loop becomes faster, because each iteration just moves the pointer to the next element rather than recomputing the full address

> Key takeaway: Arrays are arranged contiguously in memory, and compilers exploit this predictable layout to generate efficient address computations

## 3.8.5 Variable-sized arrays

- For variable-sized arrays, compilers can't precompute element addresses, since the array's size is given at runtime
- To access element, compilers must calculate the full address dynamically (e.g. `base + (i * N + j) * size`)
- The compiler can’t simplify the arithmetic into pointer increments because it doesn’t know the stride between elements in advance

> Key takeaway: Variable-sized arrays trade flexibility for performance: each element access cost time because the address math happens at runtime, not during compilation

# 3.9 Heterogenous data structures

A C struct is a user-defined type that groups object of possibly different types into a single composite object. All fields are stored contiguously in memory, and a pointer to the struct points to its first byte. The compiler records the byte offset (how far, in bytes, a field is located from the start address) of each field and uses these offsets to generate memory references for field access

- Pointer arithmetic and LEA instructions efficiently compute addresses like `&r->a[i]`
- An array or another struct is embedded directly within the struct, not a pointer to another block of memory
- Field selection is entirely resolved at compile time; the machine code has no notion of field names
