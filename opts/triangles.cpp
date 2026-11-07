#include "tmp.cpp"

// Простой неориентированный граф, вершины [0, n). Сортирует списки смежности.
int countTriangles(vector<vector<int>> &g) {
        int n = g.size();
        vector<int> deg(n);
        for (int i = 0; i < n; i++) deg[i] = g[i].size();
        vector<pii> ord(n);
        vector<int> p(n);
        for (int i = 0; i < n; i++) {
                ord[i] = {deg[i], i};
        }
        sort(all(ord));
        for (int i = 0; i < n; i++) p[ord[i].second] = i;
        int ans = 0;
        for (int k = 0; k < n; k++) {
                sort(all(g[k]), [&](int i, int j) {
                        return p[i] < p[j];
                });
        }
        for (const auto& [d, v] : ord) {
                vector<bool> is_n(n);
                for (const auto u : g[v]) is_n[u] = true;
                for (const auto u : g[v]) {
                        if (p[v] < p[u]) break;
                        for (const auto w : g[u]) {
                                if (p[w] > p[u]) break;
                                if (is_n[w]) ans++;
                        }
                }
        }
        return ans;
}
