#include <stdio.h>

unsigned replace_byte(unsigned x, int i, unsigned char b) {
    unsigned shift = 8 * i;
    unsigned mask = 0xFF << shift;
    return (x & ~mask) | ((unsigned) b << shift);
}

int main() {
    printf("%x\n", replace_byte(0x12345678, 2, 0xAB)); // 0x12AB5678
    printf("%x\n", replace_byte(0x12345678, 0, 0xAB)); // 0x123456AB
}
