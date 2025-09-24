# Practice problem 2.1

## A. 0x39A7F8 to binary

Expand each hex digit to its 4-bits binary equivalence:

```
3    9    A    7    F    8

0011 1001 1010 0111 1111 1000
```

Combining them: `0x39A7F8 = 001110011010011111111000 = 1110011010011111111000`

## B. Binary 1100100101111011 to hexadecimal

Group the binary into 4-bit chunks and convert each chunk to their corresponding hex:

```
1100 1001 0111 1011

C    9    7    B
```

Combining them: `0xC97B`

## C. 0xD5E4C to binary

Expand each hex digit to its 4-bits binary equivalence:

```
D    5    E    4    C

1101 0101 1110 0100 1100
```

Combining them: `0xD5E4C = 11010101111001001100`

## D. Binary 1001101110011110110101 to hexadecimal

The binary has 22 bits which is not a multiple of 4. So we pad on the left with 2 zeros, and group the binary into 4-bits chunks to get their hex

```
0010 0110 1110 0111 1011 0101

2    6    E    7    B    5
```

Combining them: `1001101110011110110101 = 0x26E7B5`

# Practice problem 2.2

| **n** | **2ⁿ (Decimal)** | **2ⁿ (Hexadecimal)** |
| ----- | ---------------- | -------------------- |
| 9     | 512              | 0x200                |
| 19    | 524288           | 0x80000              |
| 14    | 16,384           | 0x4000               |
| 16    | 65536            | 0x10000              |
| 17    | 131072           | 0x20000              |
| 5     | 32               | 0x20                 |
| 7     | 128              | 0x80                 |

# Practice problem 2.3

| **Decimal** | **Binary** | **Hexadecimal** |
| ----------- | ---------- | --------------- |
| 0           | 0000 0000  | 0x00            |
| 167         | 1010 0111  | 0xA7            |
| 62          | 0011 1110  | 0x3E            |
| 188         | 1011 1100  | 0xBC            |
| 55          | 0011 0111  | 0x37            |
| 136         | 1000 1000  | 0x88            |
| 243         | 1111 0011  | 0xF3            |
| 82          | 0101 0010  | 0x52            |
| 172         | 1010 1100  | 0xAC            |
| 231         | 1110 0111  | 0xE7            |

# Practice problem 2.4

A. 0x503c + 0x8 = 0x5044
B. 0x503c − 0x40 = 0x4ffc
C. 0x503c + 64 = 0x507c
D. 0x50ea − 0x503c = 0xae

# Practice problem 2.5

A. Little endian: 21 Big endian: 87
B. Little endian: 2143 Big endian: 8765
C. Little endian: 214365 Big endian: 876543

# Practice problem 2.6

A.

`0x00359141 = 0000 0000 0011 0101 1001 0001 0100 0001 = 00000000001101011001000101000001`

`0x4A564504 = 0100 1010 0101 0110 0100 0101 0000 0100 = 01001010011001000101000001101000 `

B.

```
a = 0000 0000 0011 0101 1001 0001 0100 0001
b =   0100 1010 0101 0110 0100 0101 0000 0100
```

When shifted optimally (place b starting at a's index 2), 26 bits match

C.

The bits that don't match:

1. The a's two leading bits, and the b's two least-significant bits
2. And four bits inside the overlapped area

# Practice problem 2.7

`616263646566`

# Practice problem 2.8

| Operation | Result      |
| --------- | ----------- |
| a         | \[01101001] |
| b         | \[01010101] |
| \~a       | \[10010110] |
| \~b       | \[10101010] |
| a & b     | \[01000001] |
| a \| b    | \[01111101] |
| a ^ b     | \[00111100] |

# Practice problem 2.9

A.

Flipping each bits

| R   | G   | B   | Color   | Complement (R,G,B) | Complement Color |
| --- | --- | --- | ------- | ------------------ | ---------------- |
| 0   | 0   | 0   | Black   | 1 1 1              | White            |
| 0   | 0   | 1   | Blue    | 1 1 0              | Yellow           |
| 0   | 1   | 0   | Green   | 1 0 1              | Magenta          |
| 0   | 1   | 1   | Cyan    | 1 0 0              | Red              |
| 1   | 0   | 0   | Red     | 0 1 1              | Cyan             |
| 1   | 0   | 1   | Magenta | 0 1 0              | Green            |
| 1   | 1   | 0   | Yellow  | 0 0 1              | Blue             |
| 1   | 1   | 1   | White   | 0 0 0              | Black            |

B.

Blue | Green = [001] | [010] = [011] = Cyan
Yellow & Cyan = [110] | [011] = [010] = Green
Red ^ Magenta = [100] | [101] = [001] = Blue

# Practice problem 2.10

| Step      | x                                   | y                                   |
| --------- | ----------------------------------- | ----------------------------------- |
| Initially | a                                   | b                                   |
| Step 1    | a                                   | a ^ b                               |
| Step 2    | a ^ (a ^ b) = a ^ a ^ b = 0 ^ b = b | a ^ b                               |
| Step 3    | b                                   | b ^ (a ^ b) = b ^ b ^ a = 0 ^ a = a |

# Practice problem 2.11

A.

For an array of length 2k + 1, the middle element is at index k. In the last iteration, the loop condition is `first <= last`, so `first = last = k`

B.

We pass the address to the same element, so inside the xor_swap function call: `*y = *x ^ *y = 0`. After that line the value is destroyed and set to 0. The rest just shuffle zeros

C.

By stopping the iteration when the first meets the last:

```c
for (first = 0, last = cnt - 1;
    first < last;
    first++, last--) {
    }
```

# Practice problem 2.12

A. `0xFF & x`

B.

`~x & ~0xFF` -> flips of byte of x then sets the least significant to zero
`x & 0xFF` -> zeros out all byte except the least significant byte
`(~x & ~0xFF) | (x & 0xFF)`

C.`x | 0xFF`

# Practice problem 2.13

[solution](../code/ch02_vax.c)

# Practice problem 2.14

| Expression | Value | Expression | Value |
| ---------- | ----- | ---------- | ----- |
| x & y      | 0x20  | x && y     | 1     |
| x \| y     | 0x7F  | x \|\| y   | 1     |
| \~x \| \~y | 0xDF  | !x \|\| !y | 0     |
| x & !y     | 0x00  | x && ~y    | 1     |

# Practice problem 2.15

!(x ^ y)

# Practice problem 2.16

| Hex  | Binary   | x << 3 (Binary) | x << 3 (Hex) | x >> 2 (Logical Binary) | x >> 2 (Hex) | x >> 2 (Arithmetic Binary) | x >> 2 (Hex) |
| ---- | -------- | --------------- | ------------ | ----------------------- | ------------ | -------------------------- | ------------ |
| 0xC3 | 11000011 | 00011000        | 0x18         | 00110000                | 0x30         | 11110000                   | 0xF0         |
| 0x75 | 01110101 | 10101000        | 0xA8         | 00011101                | 0x1D         | 00011101                   | 0x1D         |
| 0x87 | 10000111 | 00111000        | 0x38         | 00100001                | 0x21         | 11100001                   | 0xE1         |
| 0x66 | 01100110 | 00110000        | 0x30         | 00011001                | 0x19         | 00011001                   | 0x19         |

# Practice problem 2.17

| Hexadecimal | Binary  | B2U₄(x)                | B2T₄(x)                 |
| ----------- | ------- | ---------------------- | ----------------------- |
| 0xE         | \[1110] | 2³ + 2² + 2¹ = 14      | −2³ + 2² + 2¹ = −2      |
| 0x0         | \[0000] | 0                      | 0                       |
| 0x5         | \[0101] | 2² + 2⁰ = 5            | 2² + 2⁰ = 5             |
| 0x8         | \[1000] | 2³ = 8                 | -2³ = -8                |
| 0xD         | \[1101] | 2³ + 2² + 2⁰ = 13      | -2³ + 2² + 2⁰ = -3      |
| 0xF         | \[1111] | 2³ + 2² + 2¹ + 2⁰ = 15 | -2³ + 2² + 2¹ + 2⁰ = -1 |

# Practice problem 2.18

### A. `0x1B8`

- Hex: `0x000001B8`
- MSB = `0` → positive.
- Decimal = $1·256 + 11·16 + 8 = 440$.

### B. `0x8`

- Hex: `0x00000008`
- MSB = `0`.
- Decimal = 8.

### C. `0x14`

- Hex: `0x00000014`
- MSB = `0`.
- Decimal = $1·16 + 4 = 20$.

### D. `0xFFFFFE58`

- MSB = `1` → negative.
- 16's complement: (0xffffffff - 0xfffffe58) + 0x1 = 0x000001a8 = 424

So decimal = **–424**

### E. `0xFFFFFE74`

- MSB = `1`
- 16's complement: (0xffffffff - 0xfffffe74) + 0x1 = 0x0000018c = 396

So decimal = **–396**.

### F. `0x8`

- Same as before

### G. `0x44`

- Hex: `0x44` = $4·16 + 4 = 68$.

### H. `0xFFFFFEC8`

- MSB = `1`.
- 16's complement: (0xffffffff - 0xfffffec8) + 0x1 0x00000138 312

So decimal = **–312**.

### I. `0x10`

- Hex: `0x10` = 16.

### J. `0xC`

- Hex: `0xC` = 12.

### K. `0xFFFFFEEC`

- MSB = `1`.
- 16's complement: (0xffffffff - 0xfffffeec) + 0x1 = 0x00000114 = 276

So decimal = **–276**.

### L. `0x8`

- Again = 8.

### M. `0x20`

- Hex: `0x20` = $2·16 = 32$.

# Practice problem 2.19

| Hexadecimal | Binary  | B2U₄(x)                | B2T₄(x)                 |
| ----------- | ------- | ---------------------- | ----------------------- |
| 0xE         | \[1110] | 2³ + 2² + 2¹ = 14      | −2³ + 2² + 2¹ = −2      |
| 0x0         | \[0000] | 0                      | 0                       |
| 0x5         | \[0101] | 2² + 2⁰ = 5            | 2² + 2⁰ = 5             |
| 0x8         | \[1000] | 2³ = 8                 | -2³ = -8                |
| 0xD         | \[1101] | 2³ + 2² + 2⁰ = 13      | -2³ + 2² + 2⁰ = -3      |
| 0xF         | \[1111] | 2³ + 2² + 2¹ + 2⁰ = 15 | -2³ + 2² + 2¹ + 2⁰ = -1 |

| x   | T2U₄(x) |
| --- | ------- |
| -8  | 8       |
| -3  | 13      |
| -2  | 14      |
| -1  | 15      |
| 0   | 0       |
| 5   | 5       |

**1:**

T2B₄(-8) = 1000
B2U₄(1000) = 8

**2:**

T2B₄(-3) = 1101
B2U₄(1101) = 8 + 4 + 1 = 13

**3:**

T2B₄(-2) = 1110
B2U₄(1110) = 8 + 4 + 2 = 14

**4:**

T2B₄(-1) = 1111
B2U₄(1111) = 8 + 4 + 2 + 1 = 15

**4, 5:**

For values between 0 <= x <= 2<sup>w - 1</sup>, the two's complement and unsigned representation are identical

# Practice problem 2.20

For values between 0 <= x <= 2<sup>w - 1</sup>, the two's complement and unsigned representation are identical. While for negative values, the unsigned interpretation is the signed value plus 2<sup>w</sup>

# Practice problem 2.21

| Expression                     | Type     | Evaluation |
| ------------------------------ | -------- | ---------- |
| `-2147483647-1 == 2147483648U` | unsigned | 1          |
| `-2147483647-1 < 2147483647`   | signed   | 1          |
| `-2147483647-1U < 2147483647`  | unsigned | 0          |
| `-2147483647-1 < -2147483647`  | signed   | 1          |
| `-2147483647-1U < -2147483647` | unsigned | 1          |

# Practice problem 2.22

A. [1011] -> -8 + 0 + 2 + 1 = -5
B. [11011] -> -16 + 8 + 0 + 2 + 1 = -5
C. [111011] -> -32 + 16 + 8 + 0 + 2 + 1 = -5

# Practice problem 2.23

**A:**

| **w**      | **fun1(w)** | **fun2(w)** |
| ---------- | ----------- | ----------- |
| 0x00000076 | 0x00000076  | 0xFFFFFF76  |
| 0x87654321 | 0x00000021  | 0xFFFFFF21  |
| 0x000000C9 | 0x000000C9  | 0xFFFFFFC9  |
| 0xEDCBA987 | 0x00000087  | 0xFFFFFF87  |

**B:**

- func1 extracts the least significant byte, zero-extended
- func2 extracts the least significant byte, sign-extended

# Practice problem 2.24

| **Hex Original** | **Hex Truncated** | **Unsigned Original** | **Unsigned Truncated** | **Two’s complement Original** | **Two’s complement Truncated** |
| ---------------- | ----------------- | --------------------- | ---------------------- | ----------------------------- | ------------------------------ |
| 0                | 0                 | 0                     | 0                      | 0                             | 0                              |
| 2                | 2                 | 2                     | 2                      | 2                             | 2                              |
| 9                | 1                 | 9                     | 1                      | -7                            | 1                              |
| B                | 3                 | 11                    | 3                      | -5                            | 3                              |
| F                | 7                 | 15                    | 7                      | -1                            | -1                             |

# Practice problem 2.25

The problem arises because length is unsigned. when length is 0, the expression length - 1 doesn't produce -1 but 0xFFFFFFFF (on a 32-bit machine, due to an implicit casting from signed to unsigned) which is about 4 billion. So the loop attempts to access memory beyond the bounds of the array, resulting in a memory error.

This can be fixed by just updating the loop condition `i < length` instead of `i <= length - 1`

# Practice problem 2.26

**A & B:**

strlen returns a size_t (an unsigned int). In the expression strlen(s) - strlen(t), both values are unsigned, so the subtraction is performed in unsigned arithmetic. So if the subtraction is negative, the result maps to a very large unsigned value. so the condition > 0 evaluates to true instead of false

**C:**

Casting both values to an signed int `(int) strlen(s) - (int) strlen(t) > 0`

# Practice problem 2.27

[Solution](../code/ch02_problem_2.27.c)

# Practice problem 2.28

| Hex (x) | Decimal (x) | Decimal (additive inverse) | Hex (additive inverse) |
| ------- | ----------- | -------------------------- | ---------------------- |
| 0       | 0           | 0                          | 0                      |
| 5       | 5           | 11                         | B                      |
| 8       | 8           | 8                          | 8                      |
| D       | 13          | 3                          | 3                      |
| F       | 15          | 1                          | 1                      |

# Practice problem 2.29

| **x** | **y** | **x + y** | **x +t₅ y** | **Case**                     |
| ----- | ----- | --------- | ----------- | ---------------------------- |
| 10100 | 10001 | -27       | 00101       | negative overflow            |
| 11000 | 11000 | -16       | 10000       | no overflow, negative result |
| 10111 | 01000 | -1        | 11111       | no overflow, negative result |
| 00010 | 00101 | 7         | 00111       | no overflow, positive result |
| 01100 | 00100 | 16        | 10000       | positive overflow            |

# Practice problem 2.30

[Solution](../code/ch02_problem_2.30.c)

# Practice problem 2.31

With 4-bit arithmetic:

- lets say x = 7 and y = 3, sum = 10
- but the representable range of 4-bit two's complement is -8 to 7
- the result is truncated: 10 mod 16 = -6 (1010)

- sum - x = -6 - 7 = -13. In 4-bit arithmetic: -13 mod 16 = 3. So it holds
- sum - y = -6 - 3 = -9. In 4-bit arithmetic: -9 mod 16 = 3. So it also holds

So the function returns 1, even when an overflow occurs

# Practice problem 2.32

The negative range goes further than the positive range by 1. So if y == TMIN, then y can't be represented (it wraps around to itself). So the bug happens when y = TMIN, regardless of x

# Practice problem 2.33

| **x (Hex)** | **x (Decimal)** | **x -t₄ x (Decimal)** | **x -t₄ x (Hex)** |
| ----------- | --------------- | --------------------- | ----------------- |
| 0           | 0               | 0                     | 0                 |
| 5           | 5               | -5                    | D                 |
| 8           | -8              | -8                    | 8                 |
| D           | -5              | 5                     | 5                 |
| F           | -1              | 1                     | 1                 |

The bit pattern generated by two's complement and unsigned negative is the same, only the interpretation changes

# Practice problem 2.34

| Mode        | x         | y         | x · y        | Truncated x · y |
| ----------- | --------- | --------- | ------------ | --------------- |
| Unsigned    | 4 \[100]  | 5 \[101]  | 20 \[010100] | 4 \[100]        |
| Two’s comp. | -4 \[100] | -3 \[101] | 12 \[001100] | -4 \[100]       |
| Unsigned    | 2 \[010]  | 7 \[111]  | 14 \[001110] | 6 \[110]        |
| Two’s comp. | 2 \[010]  | -1 \[111] | -2 \[110]    | -2 \[110]       |
| Unsigned    | 6 \[110]  | 6 \[110]  | 36 \[100100] | 4 \[100]        |
| Two’s comp. | -2 \[110] | -2 \[110] | 4 \[0000100] | -4 \[100]       |

# Practice problem 2.35

**1.**

- The exact mathematical multiplication of two w-bit numbers in two's complement `x ⋅ y`, can need up to 2w bits to store without overflowing
- Split the 2w bits product into two halves:
  - upper w bits: v
  - lower w bits: u

Then the exact mathematical product can be written as:

x ⋅ y = v ⋅ 2<sup>w</sup> + u

That’s just like saying in decimal: if I write a number as “high digits” and “low digits,” then

$$
\text{number} = (\text{high}) \times 10^k + (\text{low}).
$$

For example:

Take the number **3725**.
Let’s split it so that the **low part** has 2 digits ($k=2$):

- High part = 37
- Low part = 25

Now check:

$$
3725 = 37 \times 10^2 + 25
$$

$$
3725 = 37 \times 100 + 25
$$

$$
3725 = 3700 + 25
$$

- The lower w bits are the same as the machine's truncated result: p. The only difference is that u is being interpreted as unsigned, while p is being interpreted as two's complement
- If the MSB of u is 0, then p and u have the same value
- If the MSB of u is 1, then p is negative and u is a large positive, and the two differ by exactly 2<sup>w</sup>

$$ x \cdot y = v \cdot 2^w + u = v \cdot 2^w + (p + p*{w-1} \cdot 2^w) $$
$$ x \cdot y = p + (v + p*{w-1}) \cdot 2^w $$
$$ t = v + p\_{w-1} $$
$$ x \cdot y = p + t \cdot 2^w $$

So:

- For positive exact products that fit, v = 0; therefore, t = 0
- For negative exact products that fit, v is all ones in two's complement, but adding p<sub>w - 1</sub> (which is 1), sets v back to 0; therefore t = 0

**2:**

- Dividing p by nonzero x gives a quotient q and a remainder r
- And the remainder (r) must be smaller than the divisor (x)

**3:**

$$ x \cdot y = p + 0 \cdot 2^w $$
$$ x \cdot y = p $$
$$ p = x \cdot q + 0 $$
$$ p = x \cdot q $$
$$ x \cdot y = x \cdot q $$
$$ q = y $$

# Practice problem 2.36

[Solution](../code/ch02_problem_2.36.c)

# Practice problem 2.37

**A:**

No, doing multiplication in `long long unsigned` makes it less likely to produce a wrapped product. However, malloc takes `size_t`, which on a 32-bit machine is 32-bits, so the product is truncated to 32-bits, so we get the same wrap around we are trying to avoid

**B:**

Exit the function if the product exceeds `size_t`

```c
...
if (ele_cnt != 0 && ele_size > SIZE_MAX / ele_cnt) return NULL;
...
```

# Practice problem 2.38

So, LEA (Load Effective Instruction) can compute expressions in the form:

$$
(a << k) + b
$$

Where:

- k = 0, 1, 2, 3. So a can be left shifted by 0-3 bits
- b = 0 or b = a

Shifting left by k is equivalent to multiplying by $2^k$:

$$
(a << k) + b = a \cdot 2^k + b
$$

Since b can be 0 or a, we have two cases:

- b = 0, $a \cdot 2^k$
- b = a $a \cdot 2^k + a = a \cdot (2^k + 1)$

Case 1, b = 0:

| k   | result = a \* 2^k |
| --- | ----------------- |
| 0   | a \* 1 = a        |
| 1   | a \* 2            |
| 2   | a \* 4            |
| 3   | a \* 8            |

Case 2, b = a:

| k   | result = a\*(2^k + 1) |
| --- | --------------------- |
| 0   | a\*(1 + 1) = 2a       |
| 1   | a\*(2 + 1) = 3a       |
| 2   | a\*(4 + 1) = 5a       |
| 3   | a\*(8 + 1) = 9a       |

So multiples of a that can be computed with a single LEA instruction: `a, 2a, 3a, 4a, 5a, 8a, 9a`

# Practice problem 2.39

When n is the bit position of the MSB, n = w - 1

$$
(x << (n + 1)) - (x << m) = (x << (w - 1 + 1)) - (x << m)
(x << w) - (x << m)
$$

Shifting a w bit pattern by w bit to the left will yield 0. So:

$$
(x << w) - (x << m) = 0 - (x << m) = -(x << m)
$$

# Practice problem 2.40

| K   | shifts | Add/Subs | Expression              |
| --- | ------ | -------- | ----------------------- |
| 6   | 2      | 1        | (x << 3) - (x << 1)     |
| 31  | 1      | 1        | (x << 5) - x            |
| −6  | 2      | 1        | (x << 1) - (x << 3)     |
| 55  | 2      | 2        | (x << 6) - (x << 3) - x |

# Practice problem 2.41

- If n = m, form A only requires one shift and no addition, while form B requires two shifts and 1 subtraction
- If n = m + 1, form A and B require two shifts and one addition/subtraction
- if n > m + 1, form A requires multiple shifts and additions, while form B requires two shifts and 1 subtraction

# Practice problem 2.42

[Solution](../code/ch02_problem_2.42.c)

# Practice problem 2.43

$$
M \cdot x = x \cdot 32 - x
M = 32 - 1 = 31
$$

An arithmetic right shift by k is equivalent to dividing by $2^k$:

$$
N = 2^3 = 8
$$

# Practice problem 2.44

**A:**

When $x = TMIN$, $x - 1$ wraps to TMAX; so, $x - 1 < 0$ evaluates to false instead of true

**B:**

The expression is always true because the first part $(x & 7) != 7$ evaluates to false when the lower 3 bits are 1s, which is when $x mod 8 = 7$ (x = 7, 15, 23, ...). But in those case left shifting by 29 moves the three ones to the top three positions, so the sign bit is set to 1. Thus, $(x << 29) < 0$ evaluates to true

**C:**

The expression is not always true. It fails for values of x ($\plusmn 46340$) where squaring overflows into the negative range.

**D:**

This expression is always true because the first part only evaluates to false when $x \geq 0$. But in that case, since every positive number has a negative counterpart $-x \leq 0$ evaluates to true

**E:**

This expression is not always true. It fails when $x = TMIN$, because $TMIN$ doesn't have a positive counterpart, it wraps back to itself. So $-x \geq 0$ evaluates to false when $x = TMIN$

**F:**

This is always true, because signed and unsigned addition produce the same bit pattern

**G:**

True:

$$
x * ~y = x * (-y - 1)
ux * uy = x * y
x * (-y - 1) + x * y = -xy - x + x * y = -x (y + 1 - y) = -x
$$

# Problem problem 2.45

| Fractional value | Binary representation | Decimal representation |
| ---------------- | --------------------- | ---------------------- |
| $1/8$            | $0.001$               | $0.125$                |
| $3/4$            | $0.11$                | $0.75$                 |
| $25/16$          | $1.1001$              | $1.5625$               |
| $43/16$          | $10.1011$             | $2.6975$               |
| $9/8$            | $1.001$               | $2.125$                |
| $47/8$           | $101.111$             | $5.875$                |
| $51/16$          | $11.0011$             | $3.1875$               |

# Practice problem 2.46

**A. What is the binary representation of 0.1 − x?**

$$
0.1_{10} = 0.00011001100110011001100...
$$

$$
0.1_{10} - x = 0.00011001100110011001100... - 0.00011001100110011001100 = 0.0000000000000000000000011001100...
$$

**B. What is the approximate decimal value of 0.1 − x?**

The Tail `0.0000000000000000000000011001100...` exactly the same pattern of $0.1_{10}$, just shifted to the right by 20 bits:

$$
.1 \times 2^-20 = 9.5 \times 10^-8
$$

**C. The clock starts at 0 when the system is first powered up and keeps counting up from there. In this case, the system had been running for around 100 hours. What was the difference between the actual time and the time computed by the software?**

$$
9.5 \times 10^-8 \times * 100 * 60 * 60 = 0.34332275 seconds
$$

**D. The system predicts where an incoming missile will appear based on its velocity and the time of the last radar detection. Given that a Scud travels at around 2000 meters per second, how far off was its prediction?**

$$
0.34332275 \times 2000 \approx 687 meters
$$

# Practice problem 2.47

| Bits    | $e$ | $E$ | $2^E$ | $f$ | $M$ | $2^E × M$    | $V$ (Decimal) |
| ------- | --- | --- | ----- | --- | --- | ------------ | ------------- |
| 0 00 00 | 0   | 0   | 1     | 0/4 | 0/4 | 0/4          | 0.0           |
| 0 00 01 | 0   | 0   | 1     | 1/4 | 1/4 | 1/4          | 0.25          |
| 0 00 10 | 0   | 0   | 1     | 2/4 | 2/4 | 2/4          | 0.5           |
| 0 00 11 | 0   | 0   | 1     | 3/4 | 3/4 | 3/4          | 0.75          |
| 0 01 00 | 1   | 0   | 1     | 0/4 | 4/4 | 4/4          | 1.0           |
| 0 01 01 | 1   | 0   | 1     | 1/4 | 5/4 | 5/4          | 1.25          |
| 0 01 10 | 1   | 0   | 1     | 2/4 | 6/4 | 6/4          | 1.5           |
| 0 01 11 | 1   | 0   | 1     | 3/4 | 7/4 | 7/4          | 1.75          |
| 0 10 00 | 2   | 1   | 2     | 0/4 | 4/4 | 8/4          | 2.0           |
| 0 10 01 | 2   | 1   | 2     | 1/4 | 5/4 | 10/4         | 2.5           |
| 0 10 10 | 2   | 1   | 2     | 2/4 | 6/4 | 12/4         | 3.0           |
| 0 10 11 | 2   | 1   | 2     | 3/4 | 7/4 | 14/4         | 3.5           |
| 0 11 00 |     |     |       |     |     | +$\infin$    |               |
| 0 11 01 |     |     |       |     |     | $\text{NaN}$ |               |
| 0 11 10 |     |     |       |     |     | $\text{NaN}$ |               |
| 0 11 11 |     |     |       |     |     | $\text{NaN}$ |               |

# Practice problem 2.48

1. The binary representation of $3510593$ is:

$$
1101011001000101000001
$$

2. Normalize it into the IEEE 754 form:

$$
(-1)^0 \times 1.101011001000101000001 \times 2^21
$$

3. Encode into 32-bit IEEE 754 format:

1 + 8 + 23

- sign bit: $0$
- exponent field:
  $$
  E = e - bias
  e = bias + E = 127 + 21 = 148
  148 -> 10010100
  $$
- fraction field: $10101100100010100000100$

$$
01001010010101100100010100000100
$$

1. Convert to hex

$$
0100 1010 0101 0110 0100 0101 0000 0100

0x4A564504
$$

# Practice problem 2.49

**A. For a floating-point format with an n-bit fraction, give a formula for the smallest positive integer that cannot be represented exactly (because it would require an n+1-bit fraction to be exact). Assume the exponent field size k is large enough that the range of representable exponents does not provide a limitation for this problem.**

The smallest non-representable integer has binary representation 1, followed n zeros, followed by 1:

$$
2^{1 + n} + 1
$$

**B. What is the numeric value of this integer for single-precision format (n = 23)?**

$$
2^{23 + 1} + 1 = 16777217
$$

# Practice problem 2.50

**A. 10.010<sub>2</sub>**

$$
10.010_{2} = 2.25
$$

Rounding to the nearest half (.5). The halves around it are 2.0 (10.0<sub>2</sub>) and 2.5 (10.1<sub>2</sub>).

- Distance to 2.0: $2.25 - 2.0 = 0.25$
- Distance to 2.5: $2.5 - 2.25 = 0.25$

So its exactly halfway, so we pick the one whose last fractional bit is even (0), which is 2.0

**B. 10.011<sub>2</sub>**

$$
10.011_{2} = 2.375
$$

The halves around 2.375 are 2.0 (10.0<sub>2</sub>) and 2.5 (10.1<sub>2</sub>)

- Distance to 2.0: $2.375 - 2.0 = 0.375$
- Distance to 2.5: $2.5 - 2.375 = 0.125$

since $0.125 < 0.375$, 2.375 is closer to 2.5. So we round to 2.5

**C. 10.110<sub>2</sub>**

$$
10.110_{2} = 2.75
$$

The halves around 2.75 are 2.5 (10.1<sub>2</sub>) and 3.0 (11.0<sub>2</sub>)

- Distances to 2.75: $2.75 - 2.5 = 0.25$
- Distances to 3.0: $3.0 - 2.75 = 0.25$

So its exactly halfway, so we pick the one whose last fractional bit is even (0), which is 3.0

**D. 11.001<sub>2</sub>**

$$
11.001_{2} = 3.125
$$

The halves around 3.125 are 3.0 (11.0<sub>2</sub>) and 3.5 (11.1<sub>2</sub>)

- Distances to 3.0: $3.125 - 3.0 = 0.125$
- Distances to 3.5: $3.5 - 3.125 = 0.375$

Since $0.125 < 0.375$, 3.0 is closer to 3.125. So we round to 3.0

# Practice problem 2.51

**A. What is the binary representation of x'**

$$
0.1 = 0.0001100110011001100110011\dots_{2}
$$

We are keeping only the first 23 fractional bits. And since the 24th bit was a 1, and the remaining bits were not all zeros, the number is not exactly halfway between the rounding candidates, so it is rounded up:

To round up, you add 1 to the last kept bit (the 23rd fractional bit):

$$
x' = 0.00011001100110011001101_{2}
$$

**B. What is the approximate decimal value of x' − 0.1?**

When we rounded we added 1 to the 23rd fractional bit:

$$
x' - 0.1 \approx = 2^-24 = 2.38 \times 10^-8
$$

**C. How far off would the computed clock have been after 100 hours of operation?**

$$
2.38 \times 10^-8 \times 100 \times 60 \times 60 = 0.00857 seconds
$$

**D. How far off would the program’s prediction of the position of the Scud missile have been?**

$$
0.00857 \times 2000 = 17.1 meters
$$

# Practice problem 2.52

| Format A Bits | Format A Value | Format B Bits | Format B Value |
| ------------- | -------------- | ------------- | -------------- |
| 011 0000      | 1              | 0111 000      | 1              |
| 101 1110      | 15/2           | 1001 111      | 15/2           |
| 010 1001      | 25/32          | 0110 100      | 3/4            |
| 110 1111      | 31/2           | 1011 000      | 16             |
| 000 0001      | 1/64           | 0001 000      | 1/64           |
