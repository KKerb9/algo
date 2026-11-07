set< pair<int, int> > q;
int d[maxn];

while (q.size()) {
    v = q.begin()->second;
    q.erase(q.begin());

    for (auto e : g[v]) {
        int u = e.first, w = e.second;
        if (w < d[u]) {
            q.erase({d[u], u});
            d[u] = w;
            q.insert({d[u], u});
        }
    }
}
const int maxn = 1e5, inf = 1e9;
bool used[maxn];
vector< pair<int, int> > g[maxn];
int min_edge[maxn] = {inf}, best_edge[maxn];
min_edge[0] = 0;

// ...

for (int i = 0; i < n; i++) {
    int v = -1;
    for (int u = 0; u < n; u++)
        if (!used[u] && (v == -1 || min_edge[u] < min_edge[v]))
            v = u;

    used[v] = 1;
    if (v != 0)
        cout << v << " " << best_edge[v] << endl;

    for (auto e : g[v]) {
        int u = e.first, w = e.second;
        if (w < min_edge[u]) {
            min_edge[u] = w;
            best_edge[u] = v;
        }
    }
}
