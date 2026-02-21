#include "tmp.cpp"

struct Node {
        Node() {}
};

struct SegTree {
        ve<Node> st;
        int maxn;

        SegTree() {}
        SegTree(int n) : maxn(n) {
                st.resize(4 * maxn);
        }
        SegTree(const vi& a) : maxn(a.size()) {
                st.resize(4 * maxn);
                build(a, 0, 0, maxn);
        }

        Node merge(const Node &l, const Node &r) {}

        void build(const vi& a, int v, int l, int r) {
                if (r - l == 1) {
                        // st[v] = Node(a[l]);
                        return;
                }
                int mid = (r + l) / 2;
                build(a, 2 * v + 1, l, mid);
                build(a, 2 * v + 2, mid, r);
                st[v] = merge(st[2 * v + 1], st[2 * v + 2]);
        }

        void update(int i, const Node& x, int v, int l, int r) {
                if (r - l == 1) {
                        st[v] = x;
                        return;
                }
                int mid = (r + l) / 2;
                if (i < mid) update(i, x, 2 * v + 1, l, mid);
                else update(i, x, 2 * v + 2, mid, r);
                st[v] = merge(st[2 * v + 1], st[2 * v + 2]);
        }

        void update(int i, int x) {
                update(i, Node(), 0, 0, maxn);
        }

        Node get(int ql, int qr, int v, int l, int r) {
                if (qr <= l || r <= ql) return Node();
                if (ql <= l && r <= qr) return st[v];
                int mid = (r + l) / 2;
                return merge(get(ql, qr, 2 * v + 1, l, mid), get(ql, qr, 2 * v + 2, mid, r));
        }

        Node get(int ql, int qr) {
                return get(ql, qr, 0, 0, maxn);
        }

        void buildPath(vi& path, int ql, int qr, int v, int l, int r) {
                if (qr <= l || r <= ql) return;
                if (ql <= l && r <= qr) {
                        path.push_back(v);
                        return;
                }
                int mid = (r + l) / 2;
                buildPath(path, ql, qr, 2 * v + 1, l, mid);
                buildPath(path, ql, qr, 2 * v + 2, mid, r);
        }

        // k behind
        int findKth(int ql, int qr, int k) {
                vi path;
                buildPath(path, ql, qr, 0, 0, maxn);
                int pref = 0;
                for (int v : path) {
                        if (pref + st[v].x > k) {
                                return st[v].ind;
                        }
                        pref += st[v].x;
                }
                return -1;
        }
};

struct SegTreeMass {
        ve<Node> st;
        int maxn;

        SegTreeMass() {}
        SegTreeMass(int n) : maxn(n) {
                st.resize(4 * maxn);
        }
        SegTreeMass(const vi& a) : maxn(a.size()) {
                st.resize(4 * maxn);
                build(a, 0, 0, maxn);
        }

        Node merge(const Node &l, const Node &r) {}
        
        void push(int v) {}

        void build(const vi& a, int v, int l, int r) {
                if (r - l == 1) {
                        // st[v] = Node(a[l]);
                        return;
                }
                int mid = (r + l) / 2;
                build(a, 2 * v + 1, l, mid);
                build(a, 2 * v + 2, mid, r);
                st[v] = merge(st[2 * v + 1], st[2 * v + 2]);
        }

        void update(int ql, int qr, const Node& x, int v, int l, int r) {
                if (qr <= l || r <= ql) return;
                if (ql <= l && r <= qr) {
                        st[v] = x;
                        return;
                }
                int mid = (r + l) / 2;
                push(v);
                update(ql, qr, x, 2 * v + 1, l, mid);
                update(ql, qr, x, 2 * v + 2, mid, r);
                st[v] = merge(st[2 * v + 1], st[2 * v + 2]);
        }

        void update(int ql, int qr, int x) {
                update(ql, qr, Node(), 0, 0, maxn);  // don`t forget set push in Node()
        }

        Node get(int ql, int qr, int v, int l, int r) {
                if (qr <= l || r <= ql) return Node();
                if (ql <= l && r <= qr) return st[v];
                int mid = (r + l) / 2;
                push(v);
                return merge(get(ql, qr, 2 * v + 1, l, mid), get(ql, qr, 2 * v + 2, mid, r));
        }

        Node get(int ql, int qr) {
                return get(ql, qr, 0, 0, maxn);
        }

        void buildPath(vi& path, int ql, int qr, int v, int l, int r) {
                if (qr <= l || r <= ql) return;
                if (ql <= l && r <= qr) {
                        path.push_back(v);
                        return;
                }
                int mid = (r + l) / 2;
                push(v);
                buildPath(path, ql, qr, 2 * v + 1, l, mid);
                buildPath(path, ql, qr, 2 * v + 2, mid, r);
        }

        // k behind
        int findKth(int ql, int qr, int k) {
                vi path;
                buildPath(path, ql, qr, 0, 0, maxn);
                int pref = 0;
                for (int v : path) {
                        if (pref + st[v].x > k) {
                                return st[v].ind;
                        }
                        pref += st[v].x;
                }
                return -1;
        }
};

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