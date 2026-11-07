#include "tmp.cpp"

// дефолтный кун
void solve1() {
        int n, m; cin >> n >> m;
        ve<vi> g(n);
        for (int i = 0; i < n; i++) {
                int s; cin >> s;
                while (s) {
                        g[i].push_back(s - 1);
                        cin >> s;
                }
        }
        
        vi mt(m, -1);
        vi used(n);
        auto khun = [ & ](auto &&self, int v) -> bool {
                if (used[v]) return false;
                used[v] = 1;
                for (auto u : g[v]) {
                        if (mt[u] == -1) {
                                mt[u] = v;
                                return true;
                        } else {
                                if (self(self, mt[u])) {
                                        mt[u] = v;
                                        return true;
                                }
                        }
                }
                return false;
        };
        
        int ans = 0;
        for (int i = 0; i < n; i++) {
                if (khun(khun, i)) {
                        ans++;
                        used.assign(n, 0);
                }
        }

        cout << ans << '\n';
}

// покрытие DAG путями
void solve2() {
        int n, m; cin >> n >> m;
        ve<vi> g(n);
        for (int i = 0; i < m; i++) {
                int a, b; cin >> a >> b; a--; b--;
                if (a == b) continue;
                g[a].push_back(b);
                // g[b].push_back(a);
        }
        
        vi mt(n, -1);
        vi used(n);
        auto khun = [ & ](auto &&self, int v) -> bool {
                if (used[v]) return false;
                used[v] = 1;
                for (auto u : g[v]) {
                        if (mt[u] == -1) {
                                mt[u] = v;
                                return true;
                        } else {
                                if (self(self, mt[u])) {
                                        mt[u] = v;
                                        return true;
                                }
                        }
                }
                return false;
        };
        
        int ans = 0;
        for (int i = 0; i < n; i++) {
                if (khun(khun, i)) {
                        ans++;
                        used.assign(n, 0);
                }
        }

        cout << n - ans << '\n';
}