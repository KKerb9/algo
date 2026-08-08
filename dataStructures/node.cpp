class Node {
public:
        Node *l, *r;
        Node *p;
        int sz;
        int x;
        int y;
        bool rev;
        int summ;

        Node() {
                l = nullptr;
                r = nullptr;
                p = nullptr;
                sz = 0;
                x = 0;
                rev = false;
        }

        Node(int x) : x(x), sz(1) {
                l = nullptr;
                r = nullptr;
                p = nullptr;
                rev = false;
        }

        Node(int x, Node *_l, Node *_r) : x(x), sz(1) {
                l = _l;
                r = _r;
                if (_l) _l->p = this;
                if (_r) _r->p = this;
                p = nullptr;
                rev = false;
        }

        void reverse() {
                rev ^= 1;
                swap(l, r);
        }

        void push() {
                if (rev) {
                        if (l) l->reverse();
                        if (r) r->reverse();
                        rev = false;
                }
        }

        void pull() {
                sz = 1;
                if (l) sz += l->sz;
                if (r) sz += r->sz;
        }
};

int size(Node *v) {
        return (v) ? v->sz : 0;
}
