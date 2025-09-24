#include <stdio.h>

unsigned replace_low_bytes(unsigned x, unsigned y) {
    unsigned lsb = x & 0xFF;
    return (y & ~0xFF) | lsb;
}

int main() {
    printf("%x\n", replace_low_bytes(0x89ABCDEF, 0x76543210));
}
