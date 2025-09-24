#include <stdio.h>

int is_little_endian() {
    unsigned x = 1; // In memory: 0x00000001 (assuming 32-bit int, but works for any size)
    unsigned char *b = (unsigned char *) &x; // points to the first byte
    return *b == 1; // if the first byte is 1 -> little endian, else -> big endian
}

int main() {
    printf("%d\n", is_little_endian());
}
