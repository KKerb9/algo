#include "tmp.cpp"

template<typename T>
struct FenwickTree {
        int maxn;
        ve<T> ft;

        FenwickTree() {}
        FenwickTree(int n) : maxn(n) {
                ft.resize(maxn);
        }

        void build(int *s) {
                for (int i = 0; i < maxn; i++) {
                        ft[i] += s[i];
                        int j = i | (i + 1);
                        if (j < maxn) ft[j] += ft[i];
                }
        }

        void update(int i, T x) {
                for (; i < maxn; i |= (i + 1)) ft[i] += x;
        }

        T get(int ql, int qr) {
                return get(qr - 1) - get(ql - 1);
        }

        T get(int r) {
                fchmin(r, maxn - 1);
                T res = 0;
                for (; r >= 0; r = (r & (r + 1)) - 1) res += ft[r];
                return res;
        }

        int lower_bound(int pos) {
                int k = 0;
                for (int l = 29; l >= 0; l--) {
                        if (k + (1 << l) <= maxn && ft[k + (1 << l) - 1] <= pos) {
                                k += (1 << l);
                                pos -= ft[k - 1];
                        }
                }
                return k;
        }

        int descent() {
                int k = 0;
                for (int l = 29; l >= 0; l--) {
                        if (k + (1 << l) <= maxn && ft[k + (1 << l) - 1] == (1 << l)) {
                                k += (1 << l);
                        }
                }
                return k;
        }
};