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
