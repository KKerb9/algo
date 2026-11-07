#include "tmp.cpp"

// Заполнить g, вызвать build(); начальные значения вершин -- нули.
// Значение вершины v задаётся через tree.add(tin[v], x).
// Дерево непустое, корень 0; DFS рекурсивные, списки смежности сортируются.
ve<vi> g;
vi tin, tout;
int T = 0;

SegTree tree;

vi head, P, sz;
vi h;

void sizes(int v, int p) {
        sz[v] = 1;
        for (auto u : g[v]) {
                if (u == p) continue;
                h[u] = h[v] + 1;
                sizes(u, v);
                sz[v] += sz[u];
        }
}

void dfs_hld(int v, int p) {
        sort(all(g[v]), [&](int i, int j) {
                if (i == p) return false;
                if (j == p) return true;
                return sz[i] > sz[j];
        });
        tin[v] = T++;
        P[v] = p;
        for (auto u : g[v]) {
                if (u == p) continue;
                if (u == g[v][0]) {
                        head[u] = head[v];
                        dfs_hld(u, v);
                } else {
                        head[u] = u;
                        dfs_hld(u, v);
                }
        }
        tout[v] = T;
}

bool is_pred(int a, int b) {
        return tin[a] <= tin[b] && tout[a] >= tout[b];
}

// v -- предок u; путь включает u и не включает v. При u == v минимум INFLL.
ll get_path(int u, int v) {
        ll res = INFLL;
        while (!is_pred(head[u], v)) {
                res = min(res, tree.get(tin[head[u]], tin[u] + 1));
                u = P[head[u]];
        }
        res = min(res, tree.get(tin[v] + 1, tin[u] + 1));
        return res;
}

// Вычесть x на том же пути (v -- предок u, v не включается).
void update_path(int u, int v, ll x) {
        while (!is_pred(head[u], v)) {
                tree.update(tin[head[u]], tin[u] + 1, x);
                u = P[head[u]];
        }
        tree.update(tin[v] + 1, tin[u] + 1, x);
}

void build() {
        int n = g.size();
        h.assign(n, 0);
        head.assign(n, 0);
        P.assign(n, -1);
        sz.assign(n, 0);
        tin.assign(n, 0);
        tout.assign(n, 0);
        T = 0;
        sizes(0, -1);
        dfs_hld(0, -1);
        tree = SegTree(T);
}
