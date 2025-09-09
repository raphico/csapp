# 1.1 Information is Bits + context

- All information in a computer—files, programs, data, and network traffic—is stored as bits (0s and 1s)
- The bits themselves don't carry meaning; the context in which they are read or used determines whether they represent texts, numbers, images, or instructions
- Character data is encoded using standards like ASCII or Unicode, which are just conventions that map bits to characters
- Files that exclusively store ASCII characters are text files; all other files are binary files

# 1.2 Programs are translated by other programs into different form

- Source code (human-readable) must be translated into machine code (binary instructions) before the computer can run it
- The translation is performed by a compiler driver (e.g. `gcc`), which orchestrates four phases:

1. preprocessing (cpp): handles directives starting with `#` (e.g. `#include`, `#define`) and outputs a modified C program (`.i`)
2. compilation (cc1): translates the preprocessed file (`.i` ) into assembly code (`.s`). This stage also applies some optimizations (e.g. constant folding, dead code elimination)
3. Assembly (as): translates assembly code `.s` into relocatable object code (`.o`), binary file containing machine instructions
4. Linking (id): combines object files (e.g. hello.o with library files like printf.o) into a single executable file, ready to load and run

# 1.3 It pays to understand how compilation systems work

While compilers usually generate correct and efficient code, programmers can benefit from understanding the compilation system because it helps them:

- optimize performance: make informed coding choices by knowing how high-level constructs translate to machine code and interact with memory
- Debug link-time errors: resolve issues related to variable scope, libraries, and symbol resolutions
- Avoid security vulnerabilities: especially buffer overflows, by understanding how data and control are stored in memory

# 1.4 Processors Read and Interpret Instructions Stored in Memory

The shell is a command-line interpreter that provides a text-based interface for interacting the operating system. It also provides an interactive REPL environment where:

- it reads user input
- evaluates them
- prints output (if any)
- loops back to accept more input

When you type a command:

- if it's a built-in command, the shell executes it directly
- if it's not built-in, the shell assumes it's the name of an executable file, and attempts to load it into memory and run it

## 1.4.1 Hardware organization of a system

The hardware organization of a system describes how the main physical component are structured and connected.

1. Buses:

   - Communication pathways that transfer information between components
   - Data moves in fixed-sized chunks of bytes called words (commonly 4 bytes = 32 bits or 8 bytes = 64 bits)
   - Word size is a key system parameter that affects both performance and addressing

2. I/O Devices:

   - Connect the system to the external world
   - Examples: keyboard and mouse for user input, display for user output, and disk drive for long-term storage of data and programs
   - Each device communicates with the system via a controller (chip on motherboard) or adapter (plug-in card), which transfers data between the device and the I/O bus

3. Main memory:

   - Temporary storage device for program instructions and the data its manipulates while executing
   - Physically built from DRAM chips
   - Logically organized as a linear array of bytes, each with a unique address
   - Different C data types occupy different number of bytes (e.g. `int` = 4 bytes, `double` = 8 bytes)

4. Processor:

   - Executes instructions stored in the main memory
   - Contains:
     - Program Counter (PC): holds the address of the current instruction
     - Register File: small, fast storage of word-sized registers (each register holds exactly 1 word, e.g. On a 32-bit CPU, a word = 4 bytes).
     - ALU (Arithmetic/Logic Unit): performs arithmetic and logic operations
   - Execution model (defined by the ISA)
     - Load: Copies data or a word from the main memory into a register
     - Store: Copies a word from a register into the main memory
     - Operate: copies the content of two registers into the ALU, performs arithmetic/logic operation and stores the result in a register
     - Jump: Updates the PC to a new instruction address

Modern CPU implement this simple model using complex techniques for speed, but the ISA gives the abstraction programmers work with

## 1.4.2 Running an executable

When we run an executable:

1. When we type the command, keystrokes from the keyboard travel through the USB controller into memory, where the shell reads them.
2. When we hit enter, the shell knowns the command is complete, and issues a system call to the OS to "load and run this file." The OS with the help of the disk controller and DMA (dynamic memory access) transfers the file content (code and data) from the executable object file into the main memory, bypassing the CPU to save time
3. Once loaded, the CPU sets it PC to the starting address of `main` in memory, and starts executing it
4. To print "hello, world\n", the program copies the string bytes from memory into registers, send them via I/O system to the display controller, which makes them appear on the screen

So, Running a program = input -> shell -> OS loads binary -> CPU executes instructions -> Output

# 1.5 Caches matter

A Computer spends much of its time moving data between storage layers rather than purely computing. For example: when you run a program, the program instructions is copied from disk -> main memory -> processor, and data flows through the same hierarchy towards the display. This is because different storage device balance speed, size, and cost.

Because of physics and cost-tradeoffs smaller storage devices are faster and more expensive than larger ones. Registers are extremely fast but tiny; main memory (DRAM) is larger, but significantly slower; disks are even larger, but thousands of times slower. This creates a processor-memory performance gap: CPUs keep getting faster than the main memory does. To bridge this gap, modern systems use cache memories: small, fast storage (using SRAM) that sit between the CPU and the main memory

1. L1 cache: very fast, small (KBs)
2. L2 cache: larger (hundreds of KBs-MBs), slower than L1 cache, but still faster than DRAM
3. L3 cache: even larger, slower than L2, but still faster than DRAM

Caches are effective because they exploit the principle of locality (the tendency to reuse recent or nearby data and instructions) so that most operations hit the cache, giving the system the benefit of both large memory and fast memory

Being aware of the cache, allows us to write programs that are 10x faster simply by improving memory access patterns

# 1.6 Storage devices form a hierarchy

Storage devices are organized as a memory hierarchy, where smaller, faster, expensive storage sits closer to the CPU and larger, slower, cheaper storage sits farther away. Each level serves as a cache for the next lower level: register caches L1, L1 caches L2, and so on. This design balances speed and cost. Understanding the hierarchy allows us to write programs that exploits locality and perform efficiently

# 1.7 The operating system manages the hardware

An operating system is a software layer that lets programs run on hardware without needing to worry about hardware complexity. Without an OS, applications would have to be rewritten for each machine type, programs could easily interfere with each other, and developers would need to handle every device detail directly.

The OS is important because it:

1. Abstraction: it hides complexity behind simple models like processes, files, and virtual memory
2. Uniformity: It offers a consistent interface so that applications can run on different machines with minimal change
3. Protection and resource management: It enforces memory protection, process isolation, privilege levels, while still also managing CPU time, memory, and devices

## Processes

A process is the operating system's abstraction of running a program. It gives the illusion that a program has it the CPU, memory, and I/O devices all to itself, even though in reality these resources are shared among many programs.

The OS maintains this illusion through context switching. A process's context includes all the information needed to pause and resume it: the program counter (the next instructions to execute), CPU registers (the temporary execution state), and memory state (data and stack). When switching, the OS saves one process's context and restores another's, allowing a single CPU to interleave many processes so that they appear to run in parallel

Processes are necessary because:

1. Isolation: each program runs in its own protected space, preventing interference
2. Convenience: the OS can suspend, resume, or terminate processes independently, simplifying resource management
3. Responsiveness: by rapidly switching between processes, the system stays interactive instead of waiting for one task to finish

## Threads

A control flow is the sequence in which a program’s instructions are executed, determined by constructs like loops, conditionals, and function calls. A process usually has a single control flow, meaning that the CPU executes one sequence of instruction at a time

Modern systems allow a process to have multiple control flows called threads. Each thread has its own program counter and registers, but all threads within a process share the same code and data, which makes communication between them efficient

Threads are useful because:

1. On multiprocessor systems, threads can run in parallel, speeding up execution
2. sharing data is easier between threads than between processes
3. They enable concurrency: multiple instructions sequence can progress independently, keeping the program responsive

Threads give independent execution, but they don't guarantee parallelism. Parallelism only happens if they are enough processors for multiple threads to run simultaneously

Analogy: If a computer system is a restaurant, each kitchen is a process with its own utensils, and each cook in a kitchen is a thread, independently preparing different parts of the meal

## Virtual memory

Virtual memory is an OS abstraction that gives each process an illusion that they have exclusive use of the entire main memory. Each process sees a virtual address space, a uniform layout that always looks the same regardless of what the process is running. Behind the scenes, the hardware and OS translate these virtual addresses into actual physical addresses in RAM, so two processes using the same virtual addresses are mapped to different physical location. A process virtual address space is divided to well-defined regions, each with a specific purpose:

At the bottom are the code and data loaded from the executable file (fixed in size for that process when its starts running), followed by the heap, which grows and shrink dynamically as the program allocates and frees memory; higher up is the region for shared libraries such as the C standard library; at the top is the stack where the compiler implement function calls: it grows and shrinks dynamically as functions are called and return; and finally at the very top is reserved for the kernel, which user programs can't access directly.

To make this illusion possible the OS stores a process's virtual memory on disk and uses the main memory as a cache for parts that are currently in use

## Files

A file is a sequence of bytes, with no inherent structure imposed by the system. Every I/O device, including a disk, keyboard, and even a network, is modelled as a file. All input and output operations is performed through a small set of system calls (UNIX I/O) that read and write files. This uniform file abstraction hides the messy details of device-specific technologies from applications, so the same program can work across different devices and systems without modification. So, we model I/O devices as files because it gives applications a uniform interface for input and output

# 1.8 Systems communicate with other systems using networks

Modern systems rarely operate in isolation—they communicate with other systems over a network. The OS treats the network as another I/O device, so sending data across a network looks similar to writing to a file. Applications like email, web browsing, and remote login all build on this model of copying sequence of bytes between machines

# 1.9 Important themes

## 1.9.1 Concurrency and parallelism

Concurrency is the ability of a system to manage multiple tasks at the same time either by interleaving their execution (rapidly switching between them or scheduling them asynchronously) or executing them simultaneously

Parallelism refers to the use of concurrency to run multiple tasks at the same time, speeding up execution

Modern computers often have multiple processors (through multicore chips or hyperthreading). Multiprocessing can improve a system's performance in two main ways:

1. it reduces the need to simulate concurrency by rapidly switching between tasks, since multiple tasks can truly run at the same time
2. it can speed up a single application program, but only if the program is designed to exploit thread-level parallelism

## 1.9.2 The importance of abstractions in computer systems

- Abstraction is a key concept in computer science, allowing complex systems to be simplified and used without knowing all the internal details.
- In programming, APIs are a form of abstraction, letting programmers use code without understanding its inner workings.
- Processor abstractions: The instruction set architecture (ISA) presents a simple, sequential model of execution, even though modern hardware may execute multiple instructions in parallel. This allows the same machine code to run on different processor implementations.
- Operating system abstractions:
  - Files → abstraction of I/O devices
  - Virtual memory → abstraction of program memory
  - Processes → abstraction of a running program
  - Virtual machines → abstraction of the entire computer (processor, OS, and programs), allowing programs to run across different OSes or hardware setups.

Overall, abstractions hide complexity, ensure portability, and make systems easier to use and program.
