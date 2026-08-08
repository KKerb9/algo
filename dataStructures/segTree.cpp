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
                // for (int v : path) {
                //         if (pref + st[v].x > k) {
                //                 return st[v].ind;
                //         }
                //         pref += st[v].x;
                // }
                return -1;
        }
};

struct SegTreeMass {
        // NOTE: push внутри вершины
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
                // for (int v : path) {
                //         if (pref + st[v].x > k) {
                //                 return st[v].ind;
                //         }
                //         pref += st[v].x;
                // }
                return -1;
        }
};
