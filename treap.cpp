#include "tmp.cpp"

mt19937 rng(1543);

uniform_int_distribution<int> dist(1, (1 << 30));

class Node {
public:
        Node *l, *r;
        int sz;
        int y;
        int x;
        int summ;
        bool reversed;
        
        Node() {
                summ = 0;
                reversed = false;
                y = dist(rng);
                sz = 1;
                x = 0;
                l = nullptr;
                r = nullptr;
        }

        Node(int _x) {
                reversed = false;
                y = dist(rng);
                sz = 1;
                summ = _x;
                x = _x;
                l = nullptr;
                r = nullptr;
        }

        void push() {
                if (reversed) {
                        if (l) l->reverse();
                        if (r) r->reverse();
                        reversed = false;
                }
        }

        void pull() {
                summ = x;
                if (l) summ += l->summ;
                if (r) summ += r->summ;
                sz = 1;
                if (l) sz += l->sz;
                if (r) sz += r->sz;
        }

        void reverse() {
                reversed ^= 1;
                swap(l, r);
        }
};

int _size(Node *t) {
        return (t) ? t->sz : 0;
}

int _summ(Node *t) {
        return (t) ? t->summ : 0;
}

namespace Pivo {

pr<Node*, Node*> split(Node *t, int k) {  // <= >
        if (!t) return {nullptr, nullptr};
        t->push();
        if (_size(t) <= k) return {t, nullptr};
        if (k == 0) return {nullptr, t};
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
        if (t1->y >= t2->y) {
                t1->r = merge(t1->r, t2);
                t1->pull();
                return t1;
        } else {
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

void remove(int pos) {
        auto [t1, t2] = split(root, pos);
        auto [t11, t12] = split(t2, 1);
        root = merge(t1, t12);
        delete t11;
}

int getSumm(int l, int r) {
        auto [t1, t2] = split(root, r);
        auto [t11, t12] = split(t1, l);
        if (!t12) return 0;
        int res = t12->summ;
        root = merge(merge(t11, t12), t2);
        return res;
}

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
