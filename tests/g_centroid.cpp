#include "common.h"
#include "graphs/centroid.cpp"

void check() {
        build();
        int n = g.size();
        size_t cnt = 0;
        for (auto &d : dist) cnt += d.size();
        for (int v = 0; v < n; v++) {
                CHECK_EQ(dist[v].at(a[v]), 0);
                vi d(n, -1);
                queue<int> q;
                d[v] = 0;
                q.push(v);
                while (!q.empty()) {
                        int u = q.front();
                        q.pop();
                        for (int w : g[u]) if (d[w] == -1) {
                                d[w] = d[u] + 1;
                                q.push(w);
                        }
                }
                for (int u = 0; u < n; u++) CHECK_EQ(count_dist(v, u), d[u]);
                for (int c = -1; c <= n; c++) {
                        int res = INF;
                        for (int u = 0; u < n; u++) if (a[u] == c) res = min(res, d[u]);
                        CHECK_EQ(get(v, c), res == INF ? -1 : res);
                }
        }
        size_t after = 0;
        for (auto &d : dist) after += d.size();
        CHECK_EQ(cnt, after);
}

signed main() {
        trng.seed(712367);
        g = {{1}, {0, 2}, {1}};
        a = {7, 7, 8};
        build();
        CHECK_EQ(get(2, 7), 1);
        check();
        for (int it = 0; it < 1500; it++) {
                int n = rnd(1, 40);
                g.assign(n, {});
                a.resize(n);
                for (int v = 1; v < n; v++) {
                        int p = it % 3 == 0 ? v - 1 : it % 3 == 1 ? 0 : rnd(0, v - 1);
                        g[v].push_back(p);
                        g[p].push_back(v);
                }
                for (int v = 0; v < n; v++) a[v] = it % 4 == 0 ? 0 : it % 4 == 1 ? v : rnd(-1, 5);
                for (auto &e : g) shuffle(all(e), trng);
                check();
        }
        cout << "OK: centroid, LCA, repeated builds, absent colors\n";
}
