# Practice problem 3.1

| Operand        | Value |
| -------------- | ----- |
| %eax           | 0x100 |
| 0x104          | 0xAB  |
| $0x108         | 0x108 |
| (%eax)         | 0xFF  |
| 4(%eax)        | 0xAB  |
| 9(%eax,%edx)   | 0x11  |
| 260(%ecx,%edx) | 0x13  |
| 0xFC(,%ecx,4)  | 0xFF  |
| (%eax,%edx,4)  | 0x11  |

# Practice problem 3.2

1 movl %eax, (%esp)
2 movw (%eax), %dx
3 movb $0xFF, %bl
4 movb (%esp,%edx,4), %dh
5 pushl $0xFF
6 movw %dx, (%eax)
7 popl %edi

# Practice problem 3.3

**1 movb $0xF, (%bl)**

An 8-bit register like %bl can't be used as a register address, only 32-bit registers

**2 movl %ax, (%esp)**

Attempts to move 32-bit from a 16-bit register

**3 movw (%eax),4(%esp)**

assemblers forbid two memory operands

**4 movb %ah,%sh**

%sh isn't a real register

**5 movl %eax,$0x123**

The destination can not be an immediate type, only a register or memory type

**6 movl %eax,%dx**

The destination operand has incorrect size

**7 movb %si, 8(%ebp)**

Only 8-bit registers can be used for byte operations

# Practice problem 3.4

| src_t         | dest_t        | Instruction        |
| ------------- | ------------- | ------------------ |
| int           | int           | movl %eax, (%edx)  |
| char          | int           | movsbl %al, (%edx) |
| char          | unsigned      | movsbl %al, (%edx) |
| unsigned char | int           | movzbl %al, (%edx) |
| int           | char          | movb %al, (%edx)   |
| unsigned      | unsigned char | movb %al, (%edx)   |
| unsigned      | int           | movl %eax, (%edx)  |

# Practice problem 3.5

1 movl 8(%ebp), %edi Get xp
2 movl 12(%ebp), %edx Get yp
3 movl 16(%ebp), %ecx Get zp
4 movl (%edx), %ebx Get y at yp
5 movl (%ecx), %esi Get z at zp
6 movl (%edi), %eax Get x at xp
7 movl %eax, (%edx) store x at yp
8 movl %ebx, (%ecx) store y at zp
9 movl %esi, (%edi) store z at xp

```c
void decode1(int *xp, int *yp, int *zp) {
    int x = *xp
    int y = *yp;
    int z = *zp

    *yp = x;
    *zp = y;
    *xp = z;
}
```

# Practice problem 3.6

| Instruction                 | Result       |
| --------------------------- | ------------ |
| `leal 6(%eax), %edx`        | $6 + x$      |
| `leal (%eax,%ecx), %edx`    | $x + y$      |
| `leal (%eax,%ecx,4), %edx`  | $x + 4y$     |
| `leal 7(%eax,%eax,8), %edx` | $7 + 9x$     |
| `leal 0xA(,%ecx,4), %edx`   | $10 + 4y$    |
| `leal 9(%eax,%ecx,2), %edx` | $9 + x + 2y$ |

# Practice problem 3.7

| Instruction               | Destination | Value |
| ------------------------- | ----------- | ----- |
| `addl %ecx,(%eax)`        | 0x100       | 0x100 |
| `subl %edx,4(%eax)`       | 0x104       | 0xA8  |
| `imull $16,(%eax,%edx,4)` | 0x10C       | 0x110 |
| `incl 8(%eax)`            | 0x108       | 0x14  |
| `decl %ecx`               | %ecx        | 0x0   |
| `subl %edx,%eax`          | %eax        | 0xFD  |

# Practice problem 3.8

1 movl 8(%ebp), %eax Get x
2 shll $2, %eax x <<= 2
3 movl 12(%ebp), %ecx Get n
4 sarl %cl, %eax x >>= n

# Practice problem 3.9

```c
int arith(int x,
          int y,
          int z)
{
    int t1 = x ^ y;
    int t2 = t1 >> 3;
    int t3 = ~t2;
    int t4 = t3 - z;
    return t4;
}
```

# Practice problem 3.10

**A. Explain the effect of this particular Exclusive-Or instruction and what useful operation it implements.**

$X ^ X = 0$, so `xorl %edx,%edx` sets all bits of `%edx` to zero

**B. What would be the more straightforward way to express this operation in assembly code?**

`movl $0, %edx`

**C. Compare the number of bytes to encode these two different implementations of the same operation.**

xor instruction is encoded more compactly

# Practice problem 3.11

1 movl 8(%ebp) %eax
2 xorl %edx, %edx
3 divl 12(%ebp)
4 movl %eax, 4(%esp)
5 movl %edx, (%esp)

# Practice problem 3.12

**A. What data type is num_t?**

Because GCC uses both 16(%ebp) and 20(%ebp), y spans 64 bits, and the multiplication is done with `mull`. So it must be `unsigned long long`

**B. Describe the algorithm used to compute the product and argue that it is correct.**

1 movl 12(%ebp), %eax Get x
2 movl 20(%ebp), %ecx Get y_h
3 imull %eax, %ecx Compute s = x*y_h
4 mull 16(%ebp) Compute t = x*y_l
5 leal (%ecx,%edx), %edx Add s to t_h
6 movl 8(%ebp), %ecx Get dest
7 movl %eax, (%ecx) Store t_l
8 movl %edx, 4(%ecx) Store s+t_h

We are computing:

$$
dest = (\text{unsigned 32-bit } x) \times (\text{unsigned 64-bit } y)
$$

$$
y = y_h \cdot 2^32 + y_l
$$

$$
x \cdot y = x \cdot y_h \cdot 2^32 + x \cdot y_l
$$

# Practice problem 3.13

**A:**

`cmpl` means 32-bit comparison. So `data_t` is either: `int` or `unsigned int`. `setl` is signed less than condition (it uses $SF$ ^ $OF$). That boils down `data_t` to `int`, and COMP is `<`

**B:**

The suffix 'w' indicates 16-bit operands, while the comparison is for a two's complement $>=$; therefore, we can infer that:

- `data_t` = `short`
- `COMP` = $>=$

**C:**

The suffix 'b' indicates 8-bit operands, while `setb` is for a unsigned $<$; therefore, we can infer that:

- `data_t` = `unsigned char`
- `COMP` = $<$

**D:**

The suffix 'l' indicates 32-bit operands, while `setne` is for $!=$, which is the same for both unsigned and signed values; therefore, we can infer that:

- `data_t` is either `int`, `unsigned`, or pointers
- `COMP` = $!=$

# Practice problem 3.14

**A:**

The suffix 'l' indicates 32-bit operands, while `setne` is for $!=$, which is the same for both unsigned and signed values; therefore, we can infer that:

- `data_t` is either `int`, `unsigned`, or pointers
- `TEST` = $!=$

**B:**

The suffix 'w' indicates 16-bit operands, while `sete` is for $==$, which is the same for both unsigned and signed values; therefore, we can infer that:

- `data_t` is either `short` or `unsigned short`
- `TEST` = $==$

**C:**

The suffix 'b' indicates 8-bit operands, while `setg` is for a two's complement $>=$; therefore, we can infer that:

- `data_t` = `char`
- `TEST` = $>$

**D:**

The suffix 'w' indicates 16-bit operands, while `seta` means $>$ in unsigned comparison; therefore, we can infer that:

- `data_t` = `unsigned short`
- `TEST` = $>$

# Practice problem 3.15

**A:**

The encoded offset is at 0x05 (decimal 5). With PC-relative addressing, the jump target is computed as:

$$
\text{target } = \text{next instruction address } + \text{offset}
$$

$$
\text{target } = 0x05 + 0x8048291 = 0x8048296
$$

Therefore the instruction is:

```
je 8048296
```

**B:**

The encoded offset is 0xe7 (decimal -25 in two's complement), and the next instruction address is 0x8048359:

```
jb 8048340
```

**C:**

The offset is encoded as 0x12 (decimal 18), and the jump target is at 0x8048391; therefore the mov address is at:

$$
0x8048391 - 0x12 = 0x804837f
$$

and the jump instruction is 2 bytes long (`74 12`). So its address is at:

$$
\text{jump instruction address} = \text{next instruction address} - 2
= 0x804837f - 2
= 0x804837d
$$

**D:**

The offset is encoded in little-endian, so 0xffffffe0 (decimal -32 in two's complement), and the next instruction address 0x80482c4 (134513348)

$$
\text{target} = \text{next instruction address} + \text {offset}
$$

$$
\text{target} = 134513348 - 32 = 0x80482A4
$$

The instruction is:

```
jmp 80482a4
```

**E:**

The first two byte denote an indirect jump, and the last four byte of the byte encoding on the left (fc 9f 04 08) represent the absolute address in little-endian
