#include "tmp.cpp"

struct BoruvkaDSU {
        vi sz;
        vi root;
        vi roots;
        vi coord_in_roots;
        int n;
        int c;
        ve<vi> comp_vs;

        BoruvkaDSU() {}
        BoruvkaDSU(int _n) : n(_n) {
                root.resize(n);
                comp_vs.resize(n);
                for (int i = 0; i < n; i++) comp_vs[i].push_back(i);
                iota(all(root), 0);
                roots = root;
                coord_in_roots = roots;
                c = n;
                sz.resize(n, 1);
        }

        int getRoot(int v) {
                if (root[v] == v) return v;
                return root[v] = getRoot(root[v]);
        }

        bool unite(int a, int b) {
                a = getRoot(a);
                b = getRoot(b);
                if (a == b) return false;
                if (sz[a] < sz[b]) swap(a, b);
                sz[a] += sz[b];
                root[b] = a;
                coord_in_roots[roots[c - 1]] = coord_in_roots[b];
                swap(roots[coord_in_roots[b]], roots[c - 1]);
                c--;
                roots.pop_back();
                for (auto el : comp_vs[b]) comp_vs[a].push_back(el);
                return true;
        }
};

// find_edge(snm, i) -> pii {u, v}: минимальное по весу ребро из компоненты i наружу.
// i -- корень, её вершины -- snm.comp_vs[i], принадлежность -- snm.getRoot(v).
// Если ребра нет, вернуть {-1, -1}. find_edge не должна объединять компоненты.
// Все рёбра фазы выбираются до объединений. Временные изменения поисковой структуры
// внутри find_edge нужно отменить перед возвратом (как удаление компоненты из Фенвика).
// Возвращает рёбра минимального остовного леса; для связного графа -- n - 1 ребро.
// O(log n) фаз; стоимость зависит от find_edge. Читать comp_vs только для корней.
template<typename FindEdge>
vii boruvka(int n, FindEdge find_edge) {
        vii res;
        BoruvkaDSU snm(n);
        while (snm.c > 1) {
                vii minEdge(snm.c, {-1, -1});
                int gI = 0;
                for (int i : snm.roots) {
                        minEdge[gI] = find_edge(snm, i);
                        gI++;
                }
                int c = snm.c;
                for (int i = 0; i < (int)minEdge.size(); i++) {
                        auto [u, v] = minEdge[i];
                        if (u == -1) continue;
                        if (!snm.unite(u, v)) continue;
                        res.emplace_back(u, v);
                }
                if (snm.c == c) break;
        }
        return res;
}
