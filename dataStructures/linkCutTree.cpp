#include "tmp.cpp"
#include "splayTree.cpp"

class LinkCutTree {
public:
        int n;
        ve<Node *> nodes;

        LinkCutTree() : n(0) {}

        LinkCutTree(int _n) : n(_n) {
                nodes.resize(n);
                for (int i = 0; i < n; i++) {
                        nodes[i] = new Node(i);
                }
        }

        int addNode() {
                int id = nodes.size();
                nodes.push_back(new Node(id));
                return id;
        }

        void makeRoot(Node *v) {
                if (!v) return;
                expose(v);
                v->reverse();
        }

        void expose(Node *v) {
                Node *u = v;
                Node *lst = nullptr;
                while (u != nullptr) {
                        splay(u);
                        u->push();
                        u->r = lst;
                        u->pull();
                        lst = u;
                        u = u->p;
                }
                splay(v);
        }
        
        bool link(int a, int b) {
                Node *v = nodes[a];
                Node *u = nodes[b];
                makeRoot(v);
                expose(u);
                if (v->p != nullptr) {
                        return false;
                }
                v->p = u;
                // u->pull();
                return true;
        }

        bool cut(int a, int b) {
                Node *v = nodes[a];
                Node *u = nodes[b];
                expose(u);
                splay(v);
                if (v->p != u) {
                        swap(u, v);
                        expose(u);
                        splay(v);
                        if (v->p != u) {
                                return false;
                        }
                }
                Node *lst = v->p;
                v->p = nullptr;
                if (lst) lst->pull();
                return true;
        }

        Node * getL(Node *v) {
                v->push();
                if (!v->l) return v;
                return getL(v->l);
        }

        int getRoot(int a) {
                Node *v = nodes[a];
                expose(v);
                return getL(v)->x;
        }

        int pathLen(int a, int b) {
                if (getRoot(a) != getRoot(b)) return -1;
                Node *u = nodes[a];
                Node *v = nodes[b];
                makeRoot(u);
                expose(v);
                return v->sz - 1;
        }
};