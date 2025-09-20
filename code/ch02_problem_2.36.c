#include <limits.h>

int tmult_ok(int x, int y) {
    long long p = (long long) x * y;

    return p <= INT_MAX && p >= INT_MIN; 
}
