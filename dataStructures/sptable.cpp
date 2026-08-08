#include "tmp.cpp"

int get(const ve<vi> &spt, int l, int r) {
        int k = 31 - __builtin_clz(r - l);
        return min(spt[k][l], spt[k][r - (1 << k)]);
}

ve<vi> build(const vi &a, int n, int logn) {
        ve<vi> spt(logn, vi(n, INF));
        for (int i = 0; i < n; i++) {
                spt[0][i] = a[i];
        }
        for (int l = 0; l < logn - 1; l++) {
                for (int i = 0; i + (2 << l) <= n; i++) {
                        spt[l + 1][i] = min(spt[l][i], spt[l][i + (1 << (l))]);
                }
        }
        return move(spt);
}
