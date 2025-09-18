#include <stdio.h>
#include <string.h>

int fun1(unsigned word) { return (int)((word << 24) >> 24); }

int fun2(unsigned word) { return ((int)word << 24) >> 24; }

int strlonger(char *s, char *t) { return strlen(s) - strlen(t) > 0; }

int main() {
    unsigned word = 0x00000076;
    printf("fun1: %x\n", fun1(word));
    printf("fun2: %x\n", fun2(word));

    word = 0x87654321;
    printf("fun1: %x\n", fun1(word));
    printf("fun2: %x\n", fun2(word));

    word = 0x000000C9;
    printf("fun1: %x\n", fun1(word));
    printf("fun2: %x\n", fun2(word));

    word = 0xEDCBA987;
    printf("fun1: %x\n", fun1(word));
    printf("fun2: %x\n", fun2(word));

    return 0;
}