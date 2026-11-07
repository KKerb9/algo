#include "tmp.cpp"

// кол-во чисел >= x
struct MST {
        int mxn;
        ve<vi> st;

        MST() {}
        MST(vi &a) : mxn(a.size()) {
                st.resize(4 * mxn);
                build(a, 0, 0, mxn);
        }

        void build(vi &a, int v, int l, int r) {
                st[v].resize(r - l);
                if (r - l == 1) {
                        st[v] = {a[l]};
                        return;
                }
                int mid = (r + l) / 2;
                build(a, 2 * v + 1, l, mid);
                build(a, 2 * v + 2, mid, r);
                merge(all(st[2 * v + 1]), all(st[2 * v + 2]), st[v].begin());
        }

        int get(int ql, int qr, int x, int v, int l, int r) {
                if (qr <= l || r <= ql) return 0;
                if (ql <= l && r <= qr) {
                        return r - l - (lower_bound(all(st[v]), x) - st[v].begin());
                }
                int mid = (r + l) / 2;
                return get(ql, qr, x, 2 * v + 1, l, mid) + get(ql, qr, x, 2 * v + 2, mid, r);
        }

        int get(int ql, int qr, int x) { return get(ql, qr, x, 0, 0, mxn); }
};