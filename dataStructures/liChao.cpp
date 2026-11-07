#include "tmp.cpp"

namespace LiChaoMassMin {

struct Line {
        ll k, b;
        ll l, r;

        Line() : k(0), b(1e18), l(-1e18), r(1e18) {}
        Line(ll _k, ll _b, ll _l, ll _r) : k(_k), b(_b), l(_l), r(_r) {}

        ll operator()(ll x) const {
                if (x < l) return INFLL;
                if (x > r) return INFLL;
                return k * x + b;
        }
};

struct Node {
        int l;
        int r;
        Line cur;

        Node() {
                l = -1;
                r = -1;
                cur = Line();
        }
        Node(int _l, int _r, const Line _cur) {
                l = _l;
                r = _r;
                cur = _cur;
        }
};

ve<Node> nodes;

void update(int v, ll l, ll r, Line p) {
        ll mid = (r + l) / 2;
        bool dl = p(l) < nodes[v].cur(l);
        bool dm = p(mid) < nodes[v].cur(mid);
        if (dm) {
                swap(p, nodes[v].cur);
        }
        if (r - l == 1LL) {
                return;
        }
        if (dm == dl) {
                if (nodes[v].r == -1) {
                        nodes[v].r = nodes.size();
                        nodes.push_back(*new Node());
                }
                update(nodes[v].r, mid, r, p);
        } else {
                if (nodes[v].l == -1) {
                        nodes[v].l = nodes.size();
                        nodes.push_back(*new Node());
                }
                update(nodes[v].l, l, mid, p);
        }
}

void updateSeg(int ql, int qr, int v, int l, int r, Line p) {
        if (qr <= l || r <= ql) return;
        if (ql <= l && r <= qr) {
                // cerr << l << ' ' << r << " [" << ql << ' ' << qr << "] " << p.k << ' ' << p.b << '\n';
                return update(v, l, r, p);
        }
        int mid = (r + l) / 2;
        if (nodes[v].l == -1) {
                nodes[v].l = nodes.size();
                nodes.push_back(*new Node());
        }
        if (nodes[v].r == -1) {
                nodes[v].r = nodes.size();
                nodes.push_back(*new Node());
        }
        updateSeg(ql, qr, nodes[v].l, l, mid, p);
        updateSeg(ql, qr, nodes[v].r, mid, r, p);
}

ll get(int v, ll l, ll r, ll x) {
        if (r - l == 1LL) return nodes[v].cur(x);
        ll mid = (r + l) / 2;
        ll res = nodes[v].cur(x);
        // cerr << l << ' ' << r << " [" << nodes[v].cur.k << ' ' << nodes[v].cur.b << "]\n";
        if (x < mid && nodes[v].l != -1) {
                res = min(res, get(nodes[v].l, l, mid, x));
        } else if (x >= mid && nodes[v].r != -1) {
                res = min(res, get(nodes[v].r, mid, r, x));
        }
        return res;
}

void solve() {
        nodes.clear();
        nodes.push_back(Node());
        int q; cin >> q;
        int p = 0;
        while (q--) {
                int t; cin >> t;
                if (t == 1) {
                        int a, b, l, r; cin >> a >> b >> l >> r;
                        int k1 = a + p;
                        int b1 = b + p;
                        Line cur(k1, b1, l, r);
                        updateSeg(l, r + 1, 0, -INF, INF, cur);
                } else {
                        int x; cin >> x;
                        auto res = get(0, -INF, INF, x);
                        if (res == INFLL) res = -1;
                        cout << res << '\n';
                        p = ((res % MOD) + MOD) % MOD;
                }
        }
}

} // namespace LiChaoMassMin

namespace LiChaoMax {

struct Line {
        int k, b;

        Line() : k(0), b(-INFLL) {}
        Line(int _k, int _b) : k(_k), b(_b) {}

        int operator() (int x) const {
                return k * x + b;
        }
};

struct Node {
        int l, r;
        Line cur;
        
        Node() : l(-1), r(-1) {}
        Node(int _l, int _r, Line &_cur) : l(_l), r(_r), cur(_cur) {}
};

ve<Node> nodes;

void update(int v, int l, int r, Line p) {
        int mid = (r + l) / 2;
        bool dl = p(l) > nodes[v].cur(l);
        bool dm = p(mid) > nodes[v].cur(mid);
        if (dm) swap(nodes[v].cur, p);
        if (r - l == 1) {
                return;
        }
        if (dl == dm) {
                if (nodes[v].r == -1) {
                        nodes[v].r = nodes.size();
                        nodes.push_back(Node());
                }
                update(nodes[v].r, mid, r, p);
        } else {
                if (nodes[v].l == -1) {
                        nodes[v].l = nodes.size();
                        nodes.push_back(Node());
                }
                update(nodes[v].l, l, mid, p);
        }
}

int get(int v, int l, int r, int x) {
        if (r - l == 1) return nodes[v].cur(x);
        int mid = (r + l) / 2;
        int res = nodes[v].cur(x);
        if (x < mid && nodes[v].l != -1) {
                fchmax(res, get(nodes[v].l, l, mid, x));
        } else if (x >= mid && nodes[v].r != -1) {
                fchmax(res, get(nodes[v].r, mid, r, x));
        }
        return res;
}

} // namespace LiChaoMax

