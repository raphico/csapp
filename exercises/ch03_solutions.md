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
