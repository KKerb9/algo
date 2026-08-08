#include "tmp.cpp"

vi pts;
vi used;
vi up;
vi h;
ve<vi> g;

void dfs(int v, int p = -1) {
        up[v] = h[v];
        used[v] = true;
        int cnt = 0;
        for (auto u : g[v]) {
                if (u == v) continue;
                if (u == p && !cnt) {
                        cnt++;
                        continue;
                }
                if (used[u]) fchmin(up[v], h[u]);
                else {
                        h[u] = h[v] + 1;
                        dfs(u, v);
                        fchmin(up[v], up[u]);
                        if (up[u] >= h[v] && p != -1) {
                                pts.push_back(v);
                        }
                }
        }
        if (p == -1 && (int)g[v].size() > 1) {
                pts.push_back(v);
        }
}