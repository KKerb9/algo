#include "tmp.cpp"

const int MAX_MEM = 1e8;
int mpos = 0;
alignas(long long) char mem[MAX_MEM];

inline void * operator new(size_t n) {
        if (n & 7) n += 8 - (n & 7);
        char *res = mem + mpos;
        mpos += n;
        return (void *)res;
}

void operator delete(void *) {}
