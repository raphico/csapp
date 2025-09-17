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

A bit vector can represent a finite set, where each position in the vector corresponds to an element in the set {0, 1, ..., w - 1}. The rightmost bit is a<sub>0</sub>, the next is a<sub>1</sub>, and so on, up to a<sub>w - 1</sub> on the left. A bit value of 1 means the element is in the set, while a bit value of 0 means it is not. For example, given the bit vector:

a = [01101001]

a<sub>0</sub> = 1, therefore element 0 is in the set
a<sub>1</sub> = 0, therefore element 1 is not in the set
a<sub>2</sub> = 0, therefore element 2 is not in the set
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

# 2.2 Integer representations

## 2.2.1 Integral Data types

- Integral data types are types that represent finite ranges of integers
- C integral types come in different sizes: char, short, int, long, long long
- Each can be signed (default, allows negatives) or unsigned (only nonnegative)
- The exact number of bytes depends on the machine and compiler, but the standard guarantees minimum ranges
- On 32-bit machines, long is often 32-bits; on 64-bit machines long is often 8 bytes
- Negative ranges go further than positive ranges (because of two's-complement representation)
- long long (introduced in C99) guarantees at least 8-bytes, making it good for very large integers

## 2.2.2 Unsigned Encodings

In binary, each bit has a place value, meaning the position on the bit in the binary number determines its value. In binary, consisting of 4 bits:

- the right most bit is worth 2<sup>0</sup> = 1
- the next bit (bit 1) is worth 2<sup>1</sup> = 2
- then bit 2 is worth 2<sup>2</sup> = 4
- then bit 3 is worth 2<sup>3</sup> = 8

If a bit is 1, it contributes its place value. If it's 0, it contributes nothing

Given a bit vector x = [x<sub>3</sub>, x<sub>2</sub>, x<sub>2</sub>, x<sub>1</sub>, x<sub>1</sub>], its corresponding unsigned integer representation can be expressed as:

- `w` = number of bits.
- Each bit `xᵢ` is either `0` or `1`
- Its contribution is `xᵢ · 2ⁱ`.
- You add up all contributions for `i = 0` (rightmost) up to `w − 1` (leftmost).

So:

$$
B2U_w(x) = \sum_{i=0}^{w-1} x_i \cdot 2^i
$$

Example for `w = 4`, `x = [1011]`:

$$
B2U_4([1011]) = 1·2³ + 0·2² + 1·2¹ + 1·2⁰ = 8 + 0 + 2 + 1 = 11
$$

- With w bits, the smallest unsigned integer is [0...0] = 0
- The largest is [1...1] = 2<sup>w</sup> - 1
- The B2U<sub>w</sub> maps bit vectors of length w to unsigned integers in the range [0, 2<sup>w</sup> - 1]
- This mapping is bijection

## 2.2.3 Two's complement encodings

The (r - 1)'s complement and r's complement are mathematical construct (where r is the base, usually 2 for binary) primarily used in digital systems to:

- simplify subtraction operations by converting it to addition: `A - B` = `A + (complement of B)`. This means hardware onl need adders, not separate subtractors
- represent negative numbers by mapping certain large positive values to negative values

- Two's complement is the standard way to represent signed integers in computers
- It works by interpreting the most significant bit (MSB), also called the sign bit, to have negative weight:
  - Instead of having weight of 2<sup>w - 1</sup> (like in signed representation), it has weight -2<sup>w - 1</sup>
  - If its 0, the number is nonnegative
  - If its 1, the number is negative
- The formula is:

$$
B2T_w(x) = -x_{w-1} \cdot 2^{w-1} + \sum_{i=0}^{w-2} x_i \cdot 2^i
$$

- Example with 4-bit numbers:
  - B2T<sub>4</sub>([0001]) = -0·2<sup>3</sup> + 0·2<sup>2</sup> + 0·2<sup>1</sup> + 1·2<sup>0</sup> = 0 + 0 + 0 + 1 = 1
  - B2T<sub>4</sub>([0101]) = -0·2<sup>3</sup> + 1·2<sup>2</sup> + 0·2<sup>1</sup> + 1·2<sup>0</sup> = 0 + 4 + 0 + 1 = 5
  - B2T<sub>4</sub>([1011]) = -1·2<sup>3</sup> + 0·2<sup>2</sup> + 1·2<sup>1</sup> + 1·2<sup>0</sup> = -8 + 0 + 2 + 1 = -5
  - B2T<sub>4</sub>([1111]) = -1·2<sup>3</sup> + 1·2<sup>2</sup> + 1·2<sup>1</sup> + 1·2<sup>0</sup> = -8 + 4 + 2 + 1 = -1

A w-bit number in two's complement representation has a representable range of:

- The least representable value is given by [10...0] = -2<sup>w - 1</sup>
- The largest representable value is given by [01...1] = 2<sup>w - 1</sup> - 1
- Giving us a representable range of [-2<sup>w - 1</sup>, 2<sup>w - 1</sup> - 1]

### Properties

1. Asymmetric range
   - Two's complement range is asymmetric: |TMIN| = |TMAX| + 1
   - Reason: zero takes up a slot in the nonnegative side, making the negative range go further by 1
2. Unsigned vs Signed
   - The maximum unsigned value is (UMAX) is exactly twice the maximum two's-complement value plus 1: UMAX = 2TMAX + 1
   - This is because the negative patterns in signed interpretation become large positive values when viewed unsigned
3. Portability concerns
   - C doesn't force compilers to use two's complement, but most machines do
   - `<limits.h>` defines machine-specific ranges of different integer data types

### 2.2.4 Conversions between Signed and Unsigned

When casting between unsigned value and signed value (with the same word size), the bit pattern doesn't change, only the interpretation changes. For example, the 16-bit two's complement representation of -12,345 is `0xCFC7` in hex, when casting the -12,345 to an unsigned integer value, `0xCFC7` now reads 53191.

- Negative numbers become large unsigned numbers
- Large unsigned numbers beyond TMAX wrap into negative signed values
- For values between 0 <= x <= 2<sup>w - 1</sup>, signed and two's complement representation match the same bit pattern (MSB = 0)
- For other values, the interpretation depends on whether the MSB is treated as a sign bit or part of magnitude
- Every negative number has a MSB of 1, so its unsigned interpretation is always the signed value plus 2<sup>w</sup>
  $$
  T2U(x) =
  \begin{cases}
  x & x \geq 0 \\
  x + 2^w & x < 0
  \end{cases}
  $$
- If the unsigned value is smaller 2<sup>w - 1</sup>, the MSB = 0, and the two's complement is identical. If the unsigned value is larger 2<sup>w - 1</sup>, then MSB = 1, AND the two's complement is unsigned value minus 2<sup>w</sup>
  $$
  U2T_w(u) =
  \begin{cases}
  u, & u < 2^{w-1} \\
  u - 2^w, & u \geq 2^{w-1}
  \end{cases}
  $$

### 2.2.5 Signed vs Unsigned C

1. Signed vs unsigned in C
   - C supports both signed and unsigned integers
   - By default, constants like 12345 or 0x1A2B are signed
   - Adding `u`/`U` suffix makes them unsigned
   - C doesn't force machines/compilers to use two's complement representation, but almost all machines use two's complement
2. Conversion between signed and unsigned
   - Conversion doesn't change the bits, only how they're interpreted
   - On a two's complement machine, for signed to unsigned, apply T2U<sub>w</sub>; for unsigned to signed, apply U2T<sub>w</sub>, where w is the number of bits for the data type
   - Conversion can happen due to explicit cast or implicitly when an expression of one type is assigned to a variable of another
3. Printing values
   - printf specifiers:
     - %d = signed decimal
     - %u = unsigned decimal
     - %x = hexadecimal
   - printf doesn’t look at type info → it just prints the bits in the format you tell it.
4. Mixed signed/unsigned expressions
   - If one operand is unsigned, the signed one is implicitly casted to unsigned
   - This avoids negative numbers, but may be unexpected results
   - Example: `-1 < 0U   // -1 gets cast to unsigned → 4294967295U < 0U → false`

### 2.2.6 Expanding the Bit Representation of a number

1. Zero extension
   - To convert an unsigned integer to a larger data type, just add leading zeros
2. Sign extension
   - To covert a two's complement integer to a larger data, just add copies of the MSB in the leading position
3. Why sign extension works
   - The MSB has a negative weight of -2<sup>w - 1</sup>
   - When we extend, the added 1s contribute to the weight, but they cancel when combined with the original MSB
4. Signed to unsigned conversion, plus promotion, can produce different result depending on the order
   - When converting an signed short to an unsigned int, C first promotes the short to an int before casting to unsigned
   - If we instead cast to int before promotion, we would get a different result

### 2.2.7 Truncating Numbers

Truncation means reducing a number from a wider word size (w bits) to a narrower one (k bits). This is achieve by dropping the upper (w - k) bits and keeping the lower k bits.

- For unsigned numbers:

  - Truncating is equivalent to computing the remainder mod 2<sup>k</sup>: new value = x mod 2<sup>k</sup>.
  - This ensures that the result is always within the representable range (0 to 2<sup>k</sup> - 1), and "wraps-around" if it exceeds

- For two's complement (signed) numbers:

  - We still take low k bits, which equal x mod 2<sup>k</sup>.
  - But then, we reinterpret those k-bits as a two's complement integer: new value = U2T<sub>w</sub>(x mod 2<sup>k</sup>).
  - This means the truncated value could now be negative if the most significant bit of the k-bit result is 1

### 2.2.8 Advice on Signed vs Unsigned

Implicit casting can lead subtle, non-intuitive behavior, especially when converting between signed and unsigned types. Because this conversion without any clear indication, it easy for programmers to overlook and introduce bugs. Unsigned integers in C often cause subtle bugs due to implicit signed–unsigned conversions, so many languages (like Java) avoid them entirely and use only two’s-complement signed integers. Still, unsigned types are useful when treating data as raw bits (e.g., flags, addresses) or when implementing modular and multiprecision arithmetic
