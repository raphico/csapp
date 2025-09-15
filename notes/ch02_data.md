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

## 2.1.5 Representing strings

A string is encoded as a null-terminated array of characters. Each character is represented using an encoding standard such as ASCII or Unicode, which map bit patterns to characters. Since strings are variable-length, the end is marked with the NUL character ('\0'), whose hexadecimal value is 0x00. This ensures programs know where the string ends. Because encodings like ASCII are standardized, text data is more platform-independent than binary data.

## 2.1.6 Representing code

Programs, at machine-level, are just sequence of bytes with no knowledge of the original source code. Because different machine types, and even same processor under different operating system, use different and often incompatible instruction encodings, binary code is rarely portable across systems

## 2.1.7 Introduction to Boolean Algebra

Logic is about checking whether a statement follows from other statements.

- Logic rules or operations are basic rules for combining truth values (True/False). In computers, these truth values are represented as 0s and 1s. For example:
  - AND (&): outputs 1 only if both inputs are 1
  - OR (|): outputs 1 if at least one input is 1
  - NOT (~): flips 1 to 0 and 0 to 1
  - XOR (^): outputs 1 if both inputs are different
- Logic reasoning is the process applying these rules to reach conclusions: start with assumptions (premises), apply operations (AND, OR, NOT), and arrive at conclusions that must be true if the premises are true
- Logic matters because it prevents contradictions, ensures correctness in math, and gives computers rules for making decisions. At the hardware level, computers represent and process data with on/off signals (0s and 1s) and use logic operations to combine these bits into meaningful outcomes or outputs

Boolean algebra is a branch of mathematics that deals with variables having two possible values, 0 and 1, and with logic operations that captures the basic rules of logic reasoning

- It represent truth values (True/False) as binary values (1/0)
- It defines logic operations such as:
  - AND (^)
  - OR (v)
  - NOT (¬)

It matters because it gives precise, mathematical way to describe and manipulate logic, which provides the foundation for digital circuits, and programming, used to simplify digital circuits and design complex decision making processes

A bit vector can represent a finite set, where each position in the vector corresponds to an element in the set {0, 1, ..., w - 1}. The rightmost bit is a<sub>0<sub>, the next is a<sub>1<sub>, and so on, up to a<sub>w - 1<sub> on the left. A bit value of 1 means the element is in the set, while a bit value of 0 means it is not. For example, given the bit vector:

a = [01101001]

a<sub>0<sub> = 1, therefore element 0 is in the set
a<sub>1<sub> = 0, therefore element 1 is not in the set
a<sub>2<sub> = 0, therefore element 2 is not in the set
.
.
.
a<sub>7<sub> = 0, there element 7 is not in the set

Therefore, the bit vector encodes the set: A = {0, 3, 5, 6}

With this way of encoding sets, boolean operations | and & correspond to set union and intersection

## 2.1.8 Bit-Level Operations in C

A bitwise operation is an operation that acts directly on individual bits of a binary number. In C, the operators map directly to Boolean algebra:

- & → AND
- | → OR
- ~ → NOT
- ^ → XOR (exclusive OR)

These operators can be applied to any integral type (e.g. char, int, short, long, unsigned versions, etc.). To understand their effect, it easier to:

1. Convert the values from hexadecimal to binary
2. apply the operation bit by bit
3. covert the result back to hexadecimal

### Bit masking

Bit masking refers to the using of bitwise operations to "zero out" or "pick out" specific parts of a binary number. For example using `0xFF` as a mask:

- `0xFF` in binary is `11111111`
- `x & 0xFF` means that "keep only the lowest 8 bits of x, and turn everything else into 0"

Using `~0`:

- `~0` means "bitwise NOT of 0"
- In binary, 0 is all zeros, flipping all bits gives all ones

so `~0` produces a mask of all ones:

- On a 32-bit machine `~0` gives 32 ones = `0xFFFFFFFF`
- On a 64-bit machine `~0` gives 64 ones = `0xFFFFFFFFFFFFFFFF`
- Making ~0 more portable across systems than hardcoding `0xFFFFFFFF`

## 2.1.9 Logical operations in C

C has logical operators (|| -> OR, && -> AND, ! -> NOT) that look similar to bitwise operators but behave differently:

- nonzero values are treated as True and 0 as false
- They return either 1 (True) or 0 (False)
- Example: 0x56 && 0x33 = 1, because they are both nonzero

Key differences:

- scope: Logical operators work on whole values (true/false), not individual bits
- short-circuiting:
  - && stops if the first value is False
  - || stops if the first value is True
  - This prevents unnecessary evaluation

## 2.1.10 Shift operations in C

Shift operations are bitwise operations, but instead of combining bits that move the bits of a binary number left or right:

1. Left shift: moves bits left by k, drops the leftmost k bits, and fills in k zeros on the right
2. Right shift: moves bits right by k, drops the rightmost k bits, and how the left is filled depends on the type:
   - Logical right shift: fills in k zeros on the left
   - Arithmetic right shift: fills with copies of the most significant bit (preserves sign for signed numbers)

Examples:

[01100011] << 4 -> [00110000]
[10010101] >> 4 logical -> [00001001]
[10010101] >> 4 arithmetic -> [11111001]

C rules:

- `unsigned` -> right shift is always logical
- `signed` -> implementation-dependent, but almost all systems use arithmetic shifts.
