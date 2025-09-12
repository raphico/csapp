# 2 Representing and manipulating information

- Computers store and process information using the binary number system (base-2), where each bit represents a two-valued signal: ON (1) and OFF (0). By grouping bits, computers can represent more complex data, such as non-negative integers, signed integers, real numbers, and characters.
- The three primary number representations are unsigned integers (non-negative numbers), two's-complement integers (negative integers), floating-point numbers (approximations of real numbers using base-2 scientific notations).
- Because a computer uses a fixed-number of bits, arithmetic operations can overflow when results exceeds the representable range.
- Integer arithmetic is exact and satisfies familiar properties like commutativity and associativity, while float-pointing arithmetic approximates real numbers and is not associative due to finite precision
- Understanding these representations is crucial for writing correct, portable programs and for reasoning about potential pitfalls, including security vulnerabilities and unexpected behaviors in arithmetic operations.

# 2.1 Information storage

Instead of addressing individual bits, computers use bytes (8-bit blocks) as the smallest addressable unit of memory. Programs view memory as a linear array of bytes, called virtual memory, where each byte is identified by a unique number, known as its address. And the collection of all possible addresses forms the virtual address space. This virtual address space is a conceptual view provided to the program, implemented using a combination of RAM, disk storage, special hardware, and operating system software . At machine level, programs treat memory simply as blocks of bytes, without intrinsic knowledge of data types. The compiler maintains type information for generating correct code, but the executed instructions operate on raw bytes

## 2.1.1 Hexadecimal notation

Bit patterns are often written in hexadecimal (or just hex) because it is more compact than binary and easier to read and convert. Hex uses digits 0-9 and A-F (case insensitive) to represent 16 possible values of 4 bits. A single byte, consisting of 8 bits, can be represented in hex as 00 to FF. In C, hexadecimal constants are indicated with the prefix 0x (or 0X). To covert hex to binary, each hex digit corresponds to 4 binary bits, so conversion is done by expanding each digit to its 4-bit binary equivalent. And to convert binary to hex, we group the binary digits into 4 bit chunks to get hex

### Converting between decimal and hexadecimal

When a value x is a power of two (x = 2^n) its binary representation is 1 followed by n zeros. Since each hexadecimal digit corresponds to four binary bits, we can express n in the form i + 4j, where 0 <= i <= 3. The leading hex digit will be 1 (if i = 0), 2 (if i = 1), 4 (if i = 2), 8 (if i = 3) followed by j zeros. For example 2048 = 2^11; 11 = 3 + 4 \* 2 = 0x800

To convert a decimal number to hexadecimal, repeatedly divide by 16, recording the remainder each time. The remainders read in reverse order, give the hex digits. Conversely, to covert a hexadecimal number to decimal, multiply each hex digit with the appropriate power of 16 (depending on its position) and sum the results

## 2.1.2 Words

Word size refers to the number of bits a CPU is designed to process has a single, natural unit. It's the typical size of:

1. Registers: how much data can be held in a register
2. Memory addressing: the size of pointers (memory addresses), and how much memory the CPU can directly address. For a machine of w-bits word size, the virtual address space ranges from 0 to 2^w - 1. That's 2^w unique addresses
3. Instruction width
4. Integer representation: the typical size of integers that the CPU handles natively

So a Computer with a 32-bit word size has a virtual address space of 4GB (about 4 billion bytes)

## 2.1.3 Data sizes

Computer support multiple data formats with different sizes. In C, a `char` represents a byte, typically used for characters but it can also valid for small integers. Integers can vary in size with qualifiers like `short`, `long`, `long long`, which maps to 2 bytes, 4 bytes, or 8 bytes depending on the machine and compiler. `long` typically matches the machine's word size, while `long long` (introduced in C99) allows full 64-bit integers. Pointers also occupy the full word-size of the machine. Floating-point types include float (4 bytes) and double (8 bytes). Since exact sizes depend on the system, portable C programs should avoid assuming fixed sizes. Many older programs assume, for example, that an int can hold a pointer—valid on 32-bit systems but incorrect on 64-bit, leading to bugs.

## 2.1.4 Addressing and Byte ordering

Multi-byte objects are stored contiguously in memory, with the object's address being the address of its lowest (first) byte. For example, if an `int x` has address 0x100, its 4-bytes occupy 0x100-0x103. The order in which those bytes are stored depends on endianness:

1. Big-endian: stores the most-significant bit first (at the lowest address). Used by Intel-compatible machines
2. Little-endian: stores the least-significant bit first (at the lowest address). Use by IBM and Sun systems

Some modern processors are bi-endian, meaning it can be configured to be either little- or bi-endian

There is no technological reason to choose one over the other. As long as one convention is selected and adhered to consistently

Byte ordering is often abstracted away from application programmers. However, there are three main situations where endianness matters:

1. Networking: Different machines on a network may use different endianness, so they most both translate to and from a common network standard
2. Low-level memory inspection: When looking at raw byte sequence, endianness can cause values to appear reversed, especially on little-endian machines
3. Casting: casting objects to raw byte pointers (common in C), they can directly observe the byte-level layout of different types. This reveals endianness differences, as well as the distinct representations of integers, floats, and pointers.
