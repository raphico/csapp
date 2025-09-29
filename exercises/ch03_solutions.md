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
