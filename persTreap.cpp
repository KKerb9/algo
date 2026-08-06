#include <bits/extc++.h>

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
// #define int long long

#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2")
 
using namespace std;
using ll = long long;
template<typename T1, typename T2>
using pr = pair<T1, T2>;
using pii = pair<int, int>;
using ld = long double;
using ull = unsigned long long;
template<typename T>
using ve = vector<T>;
using vi = vector<int>;
using vii = vector<pii>;
using vll = vector<ll>;
using vb = vector<bool>;
using vc = vector<char>;
const int INF = 1e9 + 1;
const ll INFLL = 1e18 + 1;
const int MOD = 998244353;

inline void fchmin(int &a, int b) { a = min(a, b); }
inline void fchmax(int &a, int b) { a = max(a, b); }

template<typename T>
inline bool chmin(T &a, T b) {
        if (a > b) {
                a = b;
                return true;
        }
        return false;
}

template<typename T>
inline bool chmax(T &a, T b) {
        if (a < b) {
                a = b;
                return true;
        }
        return false;
}

// #include <ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
// using ordered_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

int reps = 1;

mt19937 rng(1543);

class Node {
public:
        Node *l, *r;
        int sz;
        int x;
        // int summ;
        // bool reversed;
        
        Node() {
                // summ = 0;
                // reversed = false;
                sz = 1;
                x = 0;
                l = nullptr;
                r = nullptr;
        }

        Node(int _x) {
                // reversed = false;
                sz = 1;
                // summ = _x;
                x = _x;
                l = nullptr;
                r = nullptr;
        }

        void push() {
                return;
                // if (reversed) {
                //         if (l) l->reverse();
                //         if (r) r->reverse();
                //         reversed = false;
                // }
        }

        void pull() {
                // summ = x;
                // if (l) summ += l->summ;
                // if (r) summ += r->summ;
                sz = 1;
                if (l) sz += l->sz;
                if (r) sz += r->sz;
        }

        // void reverse() {
        //         reversed ^= 1;
        //         swap(l, r);
        // }
};

int _size(Node *t) {
        return (t) ? t->sz : 0;
}

// int _summ(Node *t) {
//         return (t) ? t->summ : 0;
// }

namespace Pivo {

pr<Node*, Node*> split(Node *t, int k) {  // <= >
        if (!t) return {nullptr, nullptr};
        t->push();
        if (_size(t) <= k) return {t, nullptr};
        if (k == 0) return {nullptr, t};
        t = new Node(*t);
        if (_size(t->l) >= k) {
                auto [t1, t2] = split(t->l, k);
                t->l = t2;
                t->pull();
                return {t1, t};
        } else {
                auto [t1, t2] = split(t->r, k - _size(t->l) - 1);
                t->r = t1;
                t->pull();
                return {t, t2};
        }
}

Node * merge(Node *t1, Node *t2) {
        if (!t1) return t2;
        if (!t2) return t1;
        t1->push();
        t2->push();
        if (rand() % (_size(t1) + _size(t2)) < _size(t1)) {
                t1 = new Node(*t1);
                t1->r = merge(t1->r, t2);
                t1->pull();
                return t1;
        } else {
                t2 = new Node(*t2);
                t2->l = merge(t1, t2->l);
                t2->pull();
                return t2;
        }
}

Node *root = nullptr;

void insert(int x, int pos) {
        auto [t1, t2] = split(root, pos);
        root = merge(merge(t1, new Node(x)), t2);
}

void push_back(int x) {
        root = merge(root, new Node(x));
}

void remove(int pos) {
        auto [t1, t2] = split(root, pos);
        auto [t11, t12] = split(t2, 1);
        root = merge(t1, t12);
        delete t11;
}

int getF(Node *t) {
        while (t->l) {
                t = t->l;
        }
        return t->x;
}

// int getSumm(int l, int r) {
//         auto [t1, t2] = split(root, r);
//         auto [t11, t12] = split(t1, l);
//         if (!t12) return 0;
//         int res = t12->summ;
//         root = merge(merge(t11, t12), t2);
//         return res;
// }

// void assign(long long x, int l, int r) {
//         auto [t1, t2] = split(root, r);
//         auto [t11, t12] = split(t1, l);
//         t12->hasLower = false; t12->hasUpper = false;
//         t12->mn = x; t12->mx = x;
//         t12->summ = x * t12->sz; t12->cur = x;
//         t12->pushSet = true; t12->sp = x;
//         t12->fstel = x; t12->lstel = x;
//         t12->sp2 = 0;
//         t1 = merge(t11, t12);
//         root = merge(t1, t2);
// }

// void add(long long x, int l, int r) {
//         auto [t1, t2] = split(root, r);
//         auto [t11, t12] = split(t1, l);
//         t12->mn += x; t12->mx += x;
//         t12->summ += x * t12->sz; t12->cur += x;
//         t12->sp2 += x;
//         t12->fstel += x; t12->lstel += x;
//         root = merge(merge(t11, t12), t2);
// }

// int findLastG(Node* t, int x) {
//         if (t == nullptr) return -1;
//         push(t);
//         if (!t->r || t->r->mx <= x) {
//                 if (t->cur > x) return size(t->l);
//                 return findLastG(t->l, x);
//         }
//         int res = findLastG(t->r, x);
//         if (res == -1) return -1;
//         return size(t->l) + 1 + res;
// }

// int findLastL(Node* t, int x) {
//         if (t == nullptr) return -1;
//         push(t);
//         if (!t->r || t->r->mn >= x) {
//                 if (t->cur < x) return size(t->l);
//                 return findLastL(t->l, x);
//         }
//         int res = findLastL(t->r, x);
//         if (res == -1) return -1;
//         return size(t->l) + 1 + res;
// }

// int findLastHasLower(Node *t) {
//         if (t == nullptr) return -1;
//         push(t);
//         if (!t->r) {
//                 if (t->l && t->l->lstel < t->cur) {
//                         return size(t->l) - 1;
//                 }
//                 return findLastHasLower(t->l);
//         } else if (!t->r->hasLower) {
//                 if (t->cur < t->r->mx) return size(t->l);
//                 if (t->l && t->l->lstel < t->cur) return size(t->l) - 1;
//                 return findLastHasLower(t->l);
//         } else {
//                 return size(t->l) + 1 + findLastHasLower(t->r);
//         }
// }

// int findLastHasUpper(Node *t) {
//         if (t == nullptr) return -1;
//         push(t);
//         if (!t->r) {
//                 if (t->l && t->l->lstel > t->cur) {
//                         return size(t->l) - 1;
//                 }
//                 return findLastHasUpper(t->l);
//         } else if (!t->r->hasUpper) {
//                 if (t->cur > t->r->mn) {
//                         return size(t->l);
//                 }
//                 if (t->l && t->l->lstel > t->cur) {
//                         return size(t->l) - 1;
//                 }
//                 return findLastHasUpper(t->l);
//         } else {
//                 return size(t->l) + 1 + findLastHasUpper(t->r);
//         }
// }

// void next_permutation(int l, int r) {
//         auto [t1, t2] = split(root, r);
//         auto [t11, t] = split(t1, l);
//         int i = findLastHasLower(t);
//         if (i == -1) {
//                 reverse(t);
//         } else {
//                 auto [tmp, nt] = split(t, i);
//                 auto [ql, m] = split(nt, 1);
//                 int j = findLastG(m, ql->cur);
//                 auto [nm, suff] = split(m, j);
//                 auto [qr, nsuff] = split(suff, 1);
//                 nt = merge(nm, merge(ql, nsuff));
//                 reverse(nt);
//                 t = merge(tmp, merge(qr, nt));
//         }
//         root = merge(merge(t11, t), t2);
// }

// void prev_permutation(int l, int r) {
//         auto [t1, t2] = split(root, r);
//         auto [t11, t] = split(t1, l);
//         int i = findLastHasUpper(t);
//         if (i == -1) {
//                 reverse(t);
//         } else {
//                 auto [tmp, nt] = split(t, i);
//                 auto [ql, m] = split(nt, 1);
//                 int j = findLastL(m, ql->cur);
//                 auto [nm, suff] = split(m, j);
//                 auto [qr, nsuff] = split(suff, 1);
//                 nt = merge(nm, merge(ql, nsuff));
//                 reverse(nt);
//                 t = merge(tmp, merge(qr, nt));
//         }
//         root = merge(merge(t11, t), t2);
// }

} // namespace Pivo

using namespace Pivo;

void solve() {
        root = nullptr;
        int n; cin >> n;
        vi a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < a[n - 1]; i++) {
                push_back(i + a[n - 1]);
        }
        for (int i = a[n - 1]; i < 2 * n; i++) {
                push_back(i - a[n - 1]);
        }
        vi ans(n);
        cout << getF(root) << ' ';
        for (int i = n - 2; i >= 0; i--) {
                auto [t1, t2] = split(root, a[i]);
                auto [t21, t22] = split(t2, a[i]);
                auto tmp = t21;
                root = merge(t1, merge(t21, t22));
                auto [nt1, nt2] = split(root, 2 * n - a[i]);
                root = merge(tmp, nt1);
                cout << getF(root) << ' ';
        }
        cout << '\n';
}

signed main() {
        ios::sync_with_stdio(0);
        cin.tie(0);

        #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
        cin >> reps;
        #endif

        for (int i = 1; i <= reps; i++) {
                #ifdef LOCAL
                cout << "Test #" << i << " ================\n";
                #endif
                solve();
                #ifdef LOCAL
                cout << "End test ===============\n\n";
                #endif
        }
        #ifdef LOCAL
        cout << "Runtime is: " << clock() * 1.0 / CLOCKS_PER_SEC << endl;
        #endif
}
