int uadd_ok(unsigned x, unsigned y) {
    unsigned s = x + y;
    return s >= x ? 1 : 0;
}
