#include "tmp.cpp"

struct SegTreeFast {
        struct Node {
                int x;
                Node() : x(INFLL) {}
                Node(int _x) : x(_x) {}
        };

        Node merge(const Node &l, const Node &r) {
                return (l.x <= r.x) ? l : r;
        }

        int maxn;
        ve<Node> st;

        SegTreeFast() {}
        SegTreeFast(int n) : maxn(n) {
                st.resize(maxn * 2);
        }
        SegTreeFast(vi &a) : maxn(a.size()) {
                st.resize(2 * maxn);
                for (int i = 0; i < maxn; i++) {
                        st[maxn + i] = Node(a[i]);
                }
                for (int i = maxn - 1; i > 0; i--) {
                        st[i] = merge(st[(i << 1LL)], st[(i << 1LL) | 1]);
                }
        }

        void update(int i, int x) {
                i += maxn;
                st[i] = x;
                i >>= 1;
                while (i) {
                        st[i] = merge(st[(i << 1LL)], st[(i << 1LL) | 1]);
                        i >>= 1;
                }
        }

        Node get(int l, int r) {
                l += maxn;
                r += maxn;
                Node res;
                while (l < r) {
                        if (l & 1) {
                                res = merge(res, st[l]);
                                l++;
                        }
                        if (r & 1) {
                                r--;
                                res = merge(res, st[r]);
                        }
                        l >>= 1;
                        r >>= 1;
                }
                return res;
        }
};

struct SegTreeFastMass {
        struct Node {
                int x;
                Node() : x(INFLL) {}
                Node(int _x) : x(_x) {}
        };

        Node merge(const Node &l, const Node &r) {
                return (l.x <= r.x) ? l : r;
        }

        int maxn;
        int logn;
        ve<Node> st;
        vi sp;

        SegTreeFastMass() {}
        SegTreeFastMass(int n, int lg) : maxn(n), logn(lg) {
                st.resize(2 * maxn);
                sp.resize(maxn);
        }
        SegTreeFastMass(vi &a, int lg) : maxn(a.size()), logn(lg) {
                st.resize(2 * maxn);
                sp.resize(maxn);
                for (int i = 0; i < maxn; i++) st[i + maxn] = Node(a[i]);
                for (int i = maxn - 1; i > 0; i--) st[i] = merge(st[(i << 1LL)], st[(i << 1LL) | 1]);
        }

        void update(int l, int r, int x) {
                l += maxn, r += maxn;
                int ql = l, qr = r;
                while (l < r) {
                        if (l & 1) {
                                st[l].x += x;
                                if (l < maxn) sp[l] += x;
                                l++; 
                        }
                        if (r & 1) {
                                r--;
                                st[r].x += x;
                                if (r < maxn) sp[r] += x;
                        }
                        l >>= 1;
                        r >>= 1;
                }
                while (ql < qr) {
                        if (ql & 1) {
                                st[ql] = merge(st[(ql << 1LL)], st[(ql << 1LL) | 1]);
                                ql++;
                        }
                        if (qr & 1) {
                                qr--;
                                st[qr] = merge(st[(qr << 1LL)], st[(qr << 1LL) | 1]);
                        }
                        ql >>= 1;
                        qr >>= 1;
                }
        }

        void push(int v) {
                for (int i = logn - 1; i > 0; i--) {
                        int u = (v >> i);
                        st[(u << 1LL)].x += sp[u];
                        if ((u << 1LL) < maxn) sp[(u << 1LL)] += sp[u];
                        st[(u << 1LL) | 1].x += sp[u];
                        if ((u << 1LL) | 1 < maxn) sp[(u << 1LL) | 1] += sp[u];
                        sp[u] = 0;
                        st[u] = merge(st[(u << 1LL)], st[(u << 1LL) | 1]);
                }
        }

        Node get(int l, int r) {
                l += maxn, r += maxn;
                push(l);
                push(r);
                Node res;
                while (l < r) {
                        if (l & 1) {
                                res = merge(res, st[l++]);
                        }
                        if (r & 1) {
                                res = merge(res, st[--r]);
                        }
                        l >>= 1;
                        r >>= 1;
                }
                return res;
        }
};