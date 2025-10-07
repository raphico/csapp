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

# Practice problem 3.16

a %ebp+8, p at %ebp+12
1 movl 8(%ebp), %edx Get a
2 movl 12(%ebp), %eax Get p
3 testl %eax, %eax checks p == NULL
4 je .L3 jump if p == NULL
5 testl %edx, %edx checks a <= 0
6 jle .L3 if a <= 0
7 addl %edx, (%eax) *p = a + *p
8 .L3:

**A:**

```c
void cond(int a, int *p) {
    if (p == 0)
        goto done;
    if (a <= 0)
        goto done;
    *p += a;
    goto done;
done:
    return;
}
```

**B:**

The condition `p && a > 0` requires evaluating two sub-conditions with short-circuit logic. The compiler implement this by generating two conditional branches

# Practice problem 3.17

**A:**

```c
int absdiff(int x, int y) {
    int result;
    if (x < y)
        goto true;
    result = x - y;
    goto done;
true:
    result = y - x;
done:
    return result;
}
```

**B:**

If the if statement doesn't have an else, Rule 1 slightly more efficient and simpler, because you can just jump over the then. While rule 2 adds unnecessary jumps

# Practice problem 3.18

```
x at %ebp+8, y at %ebp+12
1 movl 8(%ebp), %eax            ; load x into %eax
2 movl 12(%ebp), %edx           ; load y into %edx
3 cmpl $-3, %eax                ; Compare -3 : x (computes x + 3)
4 jge .L2                       ; if x >= -3 goto L2
5 cmpl %edx, %eax               ; Compare y : x (computes x - y)
6 jle .L3                       ; if x <= y goto L3
7 imull %edx, %eax              ; val = x * y
8 jmp .L4                       ; goto done
9 .L3:
10  leal (%edx,%eax), %eax      ; val = x + y
11  jmp .L4                     ; goto done
12 .L2:
13  cmpl $2, %eax               ; Compare 2 : x (computes x - 2)
14  jg .L5                      ; if x > 2 goto L5
15  xorl %edx, %eax             ; val = x ^ y
16  jmp .L4                     ; goto done
17 .L5:
18  subl %edx, %eax             ; val =  x - y
19 .L4:                         ; return val in %eax
```

```c
int test(int x, int y) {
    int val = x - y;
    if (x < -3) {
        if (x > y)
            val = x * y;
        else
            val = x + y;
    } else if (x <= 2) {
        val = x ^ y;
    }
    return val;
}
```

# Practice problem 3.19

**A. What is the maximum value of n for which we can represent n! with a 32-bit int?**

$$
n! <= 2^31 - 1
$$

which is about 13!

**B. What about for a 64-bit long long int?**

$$
n! <= 2^63 - 1
$$

which is about 20!

# Practice problem 3.20

**A. Make a table of register usage, similar to the one shown in Figure 3.14(b).**

| Register | Variable | Initially |
| -------- | -------- | --------- |
| %eax     | x        | x         |
| %edx     | n        | n         |
| %ecx     | y        | y         |

**B. Identify test-expr and body-statement in the C code, and the corresponding lines in the assembly code.**

test-expr:

```
8       testl %edx, %edx
9       jle .L5
10      cmpl %edx, %ecx
11      jl .L2
```

body-statement:

```
5       addl %edx, %eax
6       imull %edx, %ecx
7       subl $1, %edx
```

**C. Add annotations to the assembly code describing the operation of the program, similar to those shown in Figure 3.14(b).**

```
x at %ebp+8, y at %ebp+12, n at %ebp+16
1   movl 8(%ebp), %eax      ; Load x into %eax
2   movl 12(%ebp), %ecx     ; Load y into %ecx
3   movl 16(%ebp), %edx     ; Load n into %edx
4   .L2:
5       addl %edx, %eax     ; Computes x += n
6       imull %edx, %ecx    ; computes y *= n
7       subl $1, %edx       ; Computes n--
8       testl %edx, %edx    ; Checks if n == zero
9       jle .L5             ; if n <= 0 goto done
10      cmpl %edx, %ecx     ; Computes y -= n
11      jl .L2              ; if y < n goto L2
12  .L5:                    ; returns x
```

# Practice problem 3.21

**A. Register %edx is initialized on line 6 and updated within the loop on line 11. Consider this to be a new program variable. Describe how it relates to the variables in the C code.**

%edx initially holds `a + b`, and since only a changes in the loop, %edx is incremented alongside a to always hold the updated `(a + b)` without recomputing the sum in every iteration

**B. Create a table of register usage for this function.**

| Register | Variable | Initially |
| -------- | -------- | --------- |
| %ecx     | a        | a         |
| %ebx     | b        | b         |
| %eax     | result   | 1         |
| %edx     | abp      | a + b     |

**C. Annotate the assembly code to describe how it operates**

```
a at %ebp+8, b at %ebp+12
1   movl 8(%ebp), %ecx      Load a
2   movl 12(%ebp), %ebx     Load b
3   movl $1, %eax           Set result = 1
4   cmpl %ebx, %ecx         Compares b : a (computes a - b)
5   jge .L11                if a >= b goto done
6   leal (%ebx,%ecx), %edx  abp = b + a
7   movl $1, %eax           compiler redundantly reassigns result = 1
8   .L12:
9       imull %edx, %eax    result *= abp
10      addl $1, %ecx       a++
11      addl $1, %edx       abp += 1
12      cmpl %ecx, %ebx     Compare a : b (computes b - a)
13      jg .L12             if b > a loop
14  .L11:                    return result
```

**D. Write a goto version of the function (in C) that mimics how the assembly code program operates**

```c
int loop_while(int a, int b) {
    int result = 1;
    if (a >= b)
        goto done;
    int apb = a + b;
loop:
    result *= abp;
    a++;
    abp += 1;
    if (b > a)
        goto loop;
done:
    return result;
}
```

# Practice problem 3.22

```
x at %ebp+8
1   movl 8(%ebp), %edx      Load x
2   movl $0, %eax           Set val = 0
3   testl %edx, %edx        Checks x == 0
4   je .L7                  if x == 0 goto L7
5   .L10:
6       xorl %edx, %eax     val ^= x
7       shrl %edx           x >>= 1
8       jne .L10            if x == 0 loop
9   .L7:
10      andl $1, %eax       val &= 1
```

**A. Use the assembly-code version to fill in the missing parts of the C code.**

```c
int fun_a(unsigned x) {
    int val = 0;
    while (x != 0) {
        val ^= x; // 1) 0000 ^ 1001 = 1001 9 2) 1001 ^ 0100 = 1101 13 3) 1101 ^ 0010 = 1111 15 16 16
        x >>= 1; // 0001
    }
    return val & 0x1; 15
}
```

**B. Describe in English what this function computes.**

Each iteration:

- xors value with x
- shifts x right by 1
- continues until x is 0

So:

- `val` = x ^ (x >> 1) ^ (x >> 2) ^ ... until x is 0
- The `& 1` at the end gets the LSB of `val`. So the function only returns the LSB of `val`

Let say:

$$
x = b_{k}b_{k-1}\ddots b_{2}b_{1}b_{0}
$$

- After shifting right by 0 -> LSB = $b_{0}$
- After shifting right by 1 -> LSB = $b_{1}$
- ...and so on

So the LSB of the result is just:

$$
b_{0} \oplus b_{1} \oplus b_{2} \ddots b_{k}
$$

$$
\text{result} = (\text{sum of bits of } x) \bmod 2
$$

if even number of 1s in x -> result 0
if odd number of 1s in x -> result 1

# Practice problem 3.23

```
x at %ebp+8
1   movl 8(%ebp), %ebx      ; load x
2   movl $0, %eax           ; initialize val = 0
3   movl $0, %ecx           ; initialize i = 0
4 .L13:
5   leal (%eax,%eax), %edx  ; compute 2 * val
6   movl %ebx, %eax         ; temporarily load x
7   andl $1, %eax           ; extract LSB of x: x & 1
8   orl %edx, %eax          ; val = (2 * val) | (x & 1)
9   shrl %ebx               ; x >>= 1
10  addl $1, %ecx           ; i++
11  cmpl $32, %ecx          ; Compare 32 : i (computers i - 32)
12  jne .L13                ; if i != 32 loop
```

**A. Use the assembly-code version to fill in the missing parts of the C code.**

```c
int fun_b(unsigned x) {
    int val = 0;
    int i;
    for (i = 0; i != 32; i++) {
        val = (2 * val) | (x & 1);
        x >>= 1;
    }
    return val;
}
```

**B. Describe in English what this function computes.**

Reverses the bit order of x

# Practice problem 3.24

**A. What would we get if we naively applied our rule for translating the for loop into a while loop? What would be wrong with this code?**

```c
int sum = 0;
int i = 0;
while (i < 10) {
    if (i & 1)
        continue;
    i++;
    sum += i;
}
```

If we naively translate for loop into a while loop, the continue statement would skip the incrimination of i, resulting in an infinite loop

**B. How could you replace the continue statement with a goto statement to ensure that the while loop correctly duplicates the behavior of the for loop?**

```c
int sum = 0;
int i = 0;
loop:
    if (i & 1)
        goto update;
    sum += i
update:
    i++;
    if (i < 10)
        goto loop;

```

# Practice problem 3.25

**A. What is the approximate miss penalty?**

Given:

- $T_{OK} = 16$
- $T_{MP} = ?$
- $T_{avg} = 31$
- $p = 0.5$

$$
T_{avg}(p) = T_{OK} + pT_{MP}
$$

$$
31 = 16 + 0.5 \cdot T_{MP}
$$

$$
T_{MP} = 15 / 0.5 = 30\text{ cycles}
$$

**B. How many cycles would the function require when the branch is mispredicted?**

$$
T_{MP} + T_{OP} = 30 + 16 = 46\text{ cycles}
$$

# Practice problem 3.26

**A. What operation is OP?**

`/`

**B. Annotate the code to explain how it works.**

```
Register: x in %edx
1   leal 3(%edx), %eax  ; computes x + 3
2   testl %edx, %edx    ; computes x & x = x (tests signs and zero)
3   cmovns %edx, %eax   ; if x >= 0 keep x instead of x + 3
4   sarl $2, %eax       ; arithmetically shift x by 2 to the right (divide by 4, rounds toward $-\infty$)
```

# Practice problem 3.27

```
x at %ebp+8, y at %ebp+12
1   movl 8(%ebp), %ebx      ; Loads x
2   movl 12(%ebp), %ecx     ; Loads y
3   testl %ecx, %ecx        ; test y signs and zero
4   jle .L2                 ; if y <= 0 goto L2
5   movl %ebx, %edx         ; edx = x
6   subl %ecx, %edx         ; edx = x - y
7   movl %ecx, %eax         ; eax = y
8   xorl %ebx, %eax         ; eax = x ^ y
9   cmpl %ecx, %ebx         ; compares y : x (computes x - y)
10  cmovl %edx, %eax        ; if x < y eax = edx (x - y)
11  jmp .L4                 ; goto done
12 .L2:
13  leal 0(,%ebx,4), %edx   ; edx = x * 4
14  leal (%ecx,%ebx), %eax  ; eax = x + y
15  cmpl $-2, %ecx          ; compares y : -2 (computes y + 2)
16  cmovge %edx, %eax       ; if y >= -2 eax = edx (x * 4)
17 .L4:                     ; return eax
```

```c
int test(int x, int y) {
    int val = x * 4;
    if (y > 0) {
        if (x < y)
            val = x - y;
        else
            val = x ^ y;
    } else if (y < -2)
        val = x + y;
    return val;
}
```

# Practice problem 3.28

```
x at %ebp+8
1   movl 8(%ebp), %eax  ; Load x
2   addl $2, %eax       ; index = x + 2, minimum case label = -2
3   cmpl $6, %eax       ; computes index - 6
4   ja .L2              ; if index > 6 goto default case, maximum case label = 4
5   jmp *.L8(,%eax,4)
```

Jump table for switch2

```
1 .L8:
2 .long .L3 ; case -2
3 .long .L2 ; case - 1
4 .long .L4 ; case 0
5 .long .L5 ; case 1
6 .long .L6 ; case 2
7 .long .L6 ; case 3
8 .long .L7 ; case 4
```

- Line 6 and 7 have the same destination
- Entry 3 in the jump table also jumps to the default case, meaning the isn't a real case for for x = -1

**A. What were the values of the case labels in the switch statement body?**

The integer values used for case lables in the switch statments include: -2, -1, 0, 1, 2, 3, 4

**B. What cases had multiple labels in the C code?**

labels 2 and 3

# Practice problem 3.29

```asm
a at %ebp+8, b at %ebp+12, c at %ebp+16
1   movl 8(%ebp), %eax      ; Load a
2   cmpl $7, %eax           ; Compute a - 7
3   ja .L2                  ; if a > 7 goto loc_def
4   jmp *.L7(,%eax,4)       ; Goto *jt[a] entries: 0...7

5 .L2:                      ; default case
6   movl 12(%ebp), %eax     ; answer = b
7   jmp .L8                 ; Goto done

8 .L5:                      ; case 4
9   movl $4, %eax           ; answer = 4
10  jmp .L8                 ; Goto done

11 .L6:                     ; case 5
12  movl 12(%ebp), %eax     ; Load b
13  xorl $15, %eax          ; b ^ 15
14  movl %eax, 16(%ebp)     ; c = b ^ 15
                            ; fallthrough to case 0 from case 5
15 .L3:                     ; case 0
16  movl 16(%ebp), %eax     ; Load c
17  addl $112, %eax         ; answer = c + 112
18  jmp .L8                 ; Goto done

19 .L4:                     ; case 2 and case 7
20  movl 16(%ebp), %eax     ; answer = c
21  addl 12(%ebp), %eax     ; answer += b
22  sall $2, %eax           ; answer <<= 2
23 .L8:                     ; done
```

```asm
1 .L7:
2   .long .L3   ; case 0
3   .long .L2   ; case 1
4   .long .L4   ; case 2
5   .long .L2   ; case 3
6   .long .L5   ; case 4
7   .long .L6   ; case 5
8   .long .L2   ; case 6
9   .long .L4   ; case 7
```

```c
int switcher(int a, int b, int c)
{
    int answer;
    switch(a) {
    case 5: /* Case A */
        c = b ^ 15;
        /* Fall through */
    case 0: /* Case B */
        answer = c + 112;
        break;
    case 2: /* Case C */
    case 7: /* Case D */
        answer = (c + b) << 2;
        break;
    case 4: /* Case E */
        answer = 4;
        break;
    default:
        answer = b;
    }
    return answer;
}

```

# Practice problem 3.30

**A. To what value does register %eax get set?**

%eax holds the return address (the address of the instruction immediately after the call)

**B. Explain why there is no matching ret instruction to this call.**

The return address is immediately popped into %eax, so ret would no longer have a valid address to return to

**C. What useful purpose does this code fragment serve?**

To obtain the address of the next instruction or load the PC into a register

# Practice problem 3.31

There's no inconsistency. By IA32 convention:

- %eax, %ecx, and %edx are caller-save registers: the callee can freely modify them without restoring their values
- %ebx, %esi, and %edi are callee-save registers: the callee must save their original values (typically on the stack) and restore them before returning

Hence, the procedure saves %ebx, %esi, and %edi at entry (lines 2–4) and restores them later, while freely modifying %eax, %ecx, and %edx

# Practice problem 3.32

```asm
1   movsbl 12(%ebp),%edx    ; Load byte, sign-extended to 4-byte -> char d
2   movl 16(%ebp), %eax     ; Load 4-byte value -> int *p
3   movl %edx, (%eax)       ; Stores d into address p
4   movswl 8(%ebp),%eax     ; Load 2-byte value, sign extended to 4-byte -> short c
5   movl 20(%ebp), %edx     ; Load 4-byte int -> x
6   subl %eax, %edx         ; Compute x - c
7   movl %edx, %eax         ; Returns x - c
```

```c
int fun(short c, char d, int *p, int x) {
    *p = d;
    return x-c;
}
```

# Practic problem 3.33

```asm
1 proc:
2   pushl %ebp          ; Saves the caller's %ebp
3   movl %esp, %ebp     ; Creates a new frame pointer for the procedure frame
4   subl $40, %esp      ; allocates 40 bytes on the stack frame
5   leal -4(%ebp), %eax ; Get x
6   movl %eax, 8(%esp)  ; Store &x
7   leal -8(%ebp), %eax ; Get y
8   movl %eax, 4(%esp)  ; Store &y
9   movl $.LC0, (%esp)  ; Pointer to string "%x %x"
10  call scanf
11  movl -4(%ebp), %eax
12  subl -8(%ebp), %eax
13  leave
14  ret
```

**A. What value does %ebp get set to on line 3?**

Before the proc starts executing %esp = 0x800040. When the proc executing, line 2 decrements the stack pointer by 4 and stores %ebp (0x800060) at the new top. So now:

%esp = 0x800040 - 0x4 = 0x80003C

And line 3, %ebp is set to %esp: %ebp = 0x80003C

**B. What value does %esp get set to on line 4?**

Lin 4 allocates 40 bytes on the stack, so:

%esp = %esp - 40 = 0x80003C - 0x28 = 0x800014

**C. At what addresses are local variables x and y stored?**

x is stored at -4(%ebp) = 0x80003C - 0x4 = 0x800038
y is stored at -8(%esp) = 0x80003C - 0x8 = 0x800034

# Practice problem 3.34

```asm
1   movl 8(%ebp), %ebx      ; Load x into %ebx
2   movl $0, %eax           ; Set return register %eax = 0
3   testl %ebx, %ebx        ; Set flags based on x (ZF=1 if x=0)
4   je .L3                  ; if x == 0 goto L3
5   movl %ebx, %eax         ; %eax = x
6   shrl %eax               ; %eax = x >> 1
7   movl %eax, (%esp)       ; push x >> 1 onto the stack
8   call rfun               ; recursive call: rfun (x >> 1)
9   movl %ebx, %edx         ; %edx = x
10  andl $1, %edx           ; %edx = x & 1 (extract LSB)
11  leal (%edx,%eax), %eax  ; eax = (x & 1) + <result of recurisve call>
12 .L3:                     ; returns %eax
```

**A. What value does rfun store in the callee-save register %ebx?**

Line 1 loads argument x into %ebx. So rfun stores x in %ebx

**B. Fill in the missing expressions in the C code shown above**

```c
int rfun(unsigned x) {
    if (x == 0)
        return 0;
    unsigned nx = x >> 1;
    int rv = rfun(nx);
    return (x & 0x1) + rv;
}
```

**C. Describe in English what function this code computes**

rfun returns the number of 1 bits in the binary representation of x

# Practice problem 3.35

| Array | Element size | Total size | Start address | Element _i_   |
| ----- | ------------ | ---------- | ------------- | ------------- |
| S     | 2            | 14         | $x_{S}$       | $x_{S} + 2i$  |
| T     | 4            | 12         | $x_{T}$       | $x_{T} + 4i$  |
| U     | 4            | 24         | $x_{U}$       | $x_{U} + 4i$  |
| V     | 12           | 96         | $x_{V}$       | $x_{V} + 12i$ |
| W     | 4            | 16         | $x_{W}$       | $x_{W} + 4i$  |

# Practice problem 3.36

| Expression | Type     | Value               | Assembly code              |
| ---------- | -------- | ------------------- | -------------------------- |
| S + 1      | short \* | $x_{s} + 2$         | leal 2(%edx),%eax          |
| S[3]       | short    | $M[x_{s} + 6]$      | movw 6(%edx),%ax           |
| &S[i]      | short \* | $x_{s} + 2i$        | leal (%edx,%ecx,2),%eax    |
| S[4*i + 1] | short    | $M[x_{s} + 8i + 2]$ | movw 2(%edx,%ecx,8),%ax    |
| S + i - 5  | short \* | $x_{s} + 2i - 10$   | leal -10(%edx,%ecx,2),%eax |

# Practice problem 3.37

```asm
i at %ebp+8, j at %ebp+12
1   movl 8(%ebp), %ecx          ; Get i
2   movl 12(%ebp), %edx         ; Get j
3   leal 0(,%ecx,8), %eax       ; Compute i*8
4   subl %ecx, %eax             ; Compute i*7
5   addl %edx, %eax             ; Compute i*7 + j
6   leal (%edx,%edx,4), %edx    ; Compute 5*j
7   addl %ecx, %edx             ; Compute 5*j + i
8   movl mat1(,%eax,4), %eax    ; Read from M[mat1 + 4*(i*7 + j)]
9   addl mat2(,%edx,4), %eax    ; Read from M[mat1 + 4*(i*7 + j)] + M[mat2 + 4*(5*j + i)]
```

So N = 7 (the number of columns in mat1), M = 5 (the number of columns in mat2)
