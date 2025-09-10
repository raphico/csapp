# 2 Representing and manipulating information

- Computers store and process information using the binary number system (base-2), where each bit represents a two-valued signal: ON (1) and OFF (0). By grouping bits, computers can represent more complex data, such as non-negative integers, signed integers, real numbers, and characters.
- The three primary number representations are unsigned integers (non-negative numbers), two's-complement integers (negative integers), floating-point numbers (approximations of real numbers using base-2 scientific notations).
- Because a computer uses a fixed-number of bits, arithmetic operations can overflow when results exceed the representable range.
- Integer arithmetic is exact and satisfies familiar properties like commutativity and associativity, while float-pointing arithmetic approximates real numbers and is not associative due to finite precision
- Understanding these representations is crucial for writing correct, portable programs and for reasoning about potential pitfalls, including security vulnerabilities and unexpected behaviors in arithmetic operations.

# 2.1 Information storage

Instead of addressing individual bits, computers use bytes (8-bit blocks) as the smallest addressable unit of memory. Programs view memory as a linear array of bytes, called virtual memory, where each byte is identified by a unique number, known as its address. And the collection of all possible addresses forms the virtual address space. This virtual address space is a conceptual view provided to the program, implemented using a combination of RAM, disk storage, special, and operating system. At machine level, programs treat memory simply as blocks of bytes, without intrinsic knowledge of data types. The compiler maintains type information for generating correct code, but the executed instructions operate on raw bytes

## 2.1.1 Hexadecimal notation

Bit patterns are often written in hexadecimal (or just hex) because it is more compact than binary and easier to read and convert. Hex uses digits 0-9 and A-F (case insensitive) to represent 16 possible values of 4 bits. A single byte, consisting of 8 bits, can be represented in hex as 00 to FF. In C, hexadecimal constants are indicated with the prefix 0x (or 0X). To covert hex to binary, each hex digit corresponds to 4 binary bits, so conversion is done by expanding each digit to its 4-bit binary equivalent. And to convert binary to hex, we group the binary digits into 4 bit chunks to get hex

### Converting between decimal and hexadecimal

When a value x is a power of two (x = 2^n) its binary representation is 1 followed by n zeros. Since each hexadecimal digit corresponds to four binary bits, we can express n in the form i + 4j, where 0 <= i <= 3. The leading hex digit will be 1 (if i = 0), 2 (if i = 1), 4 (if i = 2), 8 (if i = 3) followed by j zeros. For example 2048 = 2^11; 11 = 3 + 4 \* 2 = 0x800

To convert a decimal number to hexadecimal, repeatedly divide by 16, recording the remainder each time. The remainders read in reverse order, give the hex digits. Conversely, to covert a hexadecimal number to decimal, multiply each hex digit with the appropriate power of 16 (depending on its position) and sum the results
