unsigned int x = 0x12A01, y = 0x341B1, z = 0xA324, w = 0x4320B;
unsigned int myrand() {
    // Running time is less than 30% against inbuilt rand() function
    // Visit "https://en.wikipedia.org/wiki/Xorshift" for more details
    unsigned int t = x;
    t ^= t << 11;
    t ^= t >> 8;
    tie(x, y, z) = tie(y, z, w);
    w ^= w >> 19;
    w ^= t;
    return w;
}