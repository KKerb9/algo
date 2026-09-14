// КХТ на максимум


#include "tmp.cpp"

struct Line {
        int k, b;
        int operator()(int x) const {
                return k * x + b;
        }
        Line(int _k, int _b) : k(_k), b(_b) {}
        Line() : k(0), b(0) {}
};

void cht() {
        auto cross = [ & ](const Line& l1, const Line& l2) -> int {
                if (l1.k == l2.k) return -INF;
                if (l2.b < l1.b) {
                        return (l2.b - l1.b) / (l1.k - l2.k);
                }
                return (l2.b - l1.b + (l1.k - l2.k - 1)) / (l1.k - l2.k);
        };

        auto add = [ & ](ve<Line>& cht, vi &curPts, const Line& l) -> void {
                while (!cht.empty()) {
                        int x = cross(l, cht.back());
                        if (x <= curPts.back()) {
                                curPts.pop_back();
                                cht.pop_back();
                        } else {
                                break;
                        }
                }
                if (!cht.empty()) curPts.push_back(cross(l, cht.back()));
                else curPts.push_back(-INF);
                cht.push_back(l);
        };

        auto get = [ & ](ve<Line>& cht, vi &curPts, int x) -> pii {
                int ind = upper_bound(all(curPts), x) - curPts.begin() - 1;
                return {cht[ind](x), cht[ind].k};
        };
}