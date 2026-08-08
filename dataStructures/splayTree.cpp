#include "tmp.cpp"
#include "node.cpp"

namespace SplayTree {

void print_dfs(ve<Node *> &nodes, Node *v) {
        if (!v) return;
        v->push();
        print_dfs(nodes, v->l);
        nodes.push_back(v);
        print_dfs(nodes, v->r);
}

void print(Node *v, string s = "", bool f = true) {
        ve<Node *> nodes;
        print_dfs(nodes, v);
        if (f) cout << "{ ";
        for (auto el : nodes) {
                cout << el->x << ' ';
        }
        if (f) cout << "} " << s << "\n";
        else cout << '\n';
}

bool isRoot(Node* v) {
        return !v->p || (v->p->l != v && v->p->r != v);
}

// int chnum(Node* v) {
//         return v->p->ch[1] == v;
// }

void rotate(Node* v) {  // v -- нижний
        Node *u = v->p;
        if (u == nullptr) return;
        u->push();
        v->push();
        v->p = u->p;
        if (v->p != nullptr) {
                if (v->p->l == u) {
                        v->p->l = v;
                }
                if (v->p->r == u) {
                        v->p->r = v;
                }
        }
        if (v == u->l) {
                if (v->r) v->r->p = u;
                u->l = v->r;
                v->r = u;
        } else {
                if (v->l) v->l->p = u;
                u->r = v->l;
                v->l = u;
        }
        u->p = v;
        u->pull();
        v->pull();
}

void splay(Node *v) {
        if (v == nullptr) return;
        while (!isRoot(v)) {
                Node *u = v->p;
                if (isRoot(u)) {  // zig
                        rotate(v);
                        continue;
                }
                Node *g = u->p;
                if ((g->l == u) ^ (u->l == v)) {  // zig-zag
                        rotate(v);
                } else {
                        rotate(u);
                }
                rotate(v);
        }
}

Node * findKth(Node *t, int k) {  // without splay !!!
        if (!t) return nullptr;
        t->push();
        if (size(t->l) > k) {
                return findKth(t->l, k);
        } else if (size(t->l) == k) {
                return t;
        } else {
                return findKth(t->r, k - size(t->l) - 1);
        }
}

pr<Node *, Node *> split(Node *t, int k) { // {k els, ost}
        if (!t) return {nullptr, nullptr};
        if (k == 0) return {nullptr, t};
        Node *t1 = findKth(t, k - 1);
        splay(t1);
        Node *t2 = t1->r;
        if (t2) t2->p = nullptr;
        t1->r = nullptr;
        t1->pull();
        return {t1, t2};
}

Node * merge(Node *t1, Node *t2) { // <, >
        if (!t1) return t2;
        if (!t2) return t1;
        t1 = findKth(t1, t1->sz - 1);
        splay(t1);
        t1->r = t2;
        t2->p = t1;
        t1->push();
        t1->pull();
        return t1;
}

void insert(Node *&t, int x, int pos) {
        auto [t1, t2] = split(t, pos);
        t = new Node(x, t1, t2);
        t->pull();
}

void remove(Node *&t, int pos) {
        auto [t1, t2] = split(t, pos);
        auto [t21, t22] = split(t2, 1);
        t = merge(t1, t22);
        delete t21;
}

}  // namespace SplayTree

using namespace SplayTree;
