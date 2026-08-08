#include "tmp.cpp"

struct DST {
        struct Node {
                int x;
                Node() : x(INF) {}
                Node(int _x) : x(_x) {}
        };

        Node merge(const Node &l, const Node &r) {
                return (l.x <= r.x) ? l : r;
        }

        int maxn, logn;
        ve<ve<Node>> dst;

        DST() {}
        DST(vi &a, int lg) : maxn(a.size()), logn(lg) {
                dst.resize(logn, ve<Node>(maxn + 1));
                int h = 32 - __builtin_clz(maxn);
                for (int d = 0; d < h; d++) {
                        int len = (1LL << d);
                        for (int mid = len; mid < maxn + len; mid += 2 * len) {
                                if (mid <= maxn) dst[d][mid] = Node();
                                for (int i = mid + 1; i <= min(mid + len, maxn); i++) {
                                        dst[d][i] = merge(dst[d][i - 1], Node(a[i - 1]));
                                }
                                for (int i = min(maxn - 1, mid - 1); i >= mid - len; i--) {
                                        dst[d][i] = merge(dst[d][i + 1], Node(a[i]));
                                }
                        }
                }
        }

        Node get(int l, int r) {  // [l, r)
                int fbit = 31 - __builtin_clz(r ^ l);
                return merge(dst[fbit][l], dst[fbit][r]);
        }
};