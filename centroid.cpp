#include "tmp.cpp"

ve<vi> g;
vi P;
vi sz;
vi removed;

void sizes(int v, int p) {
    sz[v] = 1;
    for (auto u : g[v]) {
        if (u != p && !removed[u]) {
            sizes(u, v);
            sz[v] += sz[u];
        }
    }
}

int find(int v, int p, int n) {
    for (auto u : g[v]) {
        if (u != p && !removed[u] && sz[u] > n / 2) {
            return find(u, v, n);
        }
    }
    return v;
}

ve<map<int, int>> dist;
vi a;

void update(int v, int p, int c, int d) {
    if (dist[c][a[v]] == 0 || dist[c][a[v]] > d) {
        dist[c][a[v]] = d;
    }
    for (auto u : g[v]) {
        if (!removed[u] && u != p) {
            update(u, v, c, d + 1);
        }
    }
}

void decompose(int v, int p) {
    sizes(v, -1);
    int c = find(v, -1, sz[v]);
    P[c] = p;
    removed[c] = true;

    update(c, -1, c, 0);

    for (auto u : g[c]) {
        if (!removed[u]) decompose(u, c);
    }
}

ve<vi> up;
vi tin, tout, dp;
const int LOGN = 30;
int T = 0;

void dfs(int v, int p, int d) {
    tin[v] = T++;
    for (int l = 1; l < LOGN; l++) {
        up[v][l] = up[up[v][l - 1]][l - 1];
    }
    dp[v] = d;
    for (auto u : g[v]) {
        if (u == p) continue;
        up[u][0] = v;
        dfs(u, v, d + 1);
    }
    tout[v] = T;
}

bool is_pred(int v, int u) {
    return tin[v] <= tin[u] && tout[v] >= tout[u];
}

int count_dist(int v, int u) {
    if (is_pred(v, u)) return dp[u] - dp[v];
    if (is_pred(u, v)) return dp[v] - dp[u];
    int ast = v;
    for (int l = LOGN - 1; l >= 0; l--) {
        if (!is_pred(up[v][l], u)) {
            v = up[v][l];
        }
    }
    return dp[ast] + dp[u] - dp[up[v][0]] * 2;
}

int get(int v, int c) {
    // cerr << v << ' ' << c << '\n';
    if (a[v] == c) return 0;
    int res = INF;
    int sv = v;
    // cerr << 0 << '\n';
    while (v != -1) {
        // cerr << 1 << '\n';
        int cd = count_dist(v, sv);
        // cerr << 2 << '\n';
        if (dist[v][c] != 0 || a[v] == c) {
            res = min(res, dist[v][c] + cd);
        }
        // cout << v << ' ' << cd << ' ' << res << '\n';
        // cerr << 3 << '\n';
        v = P[v];
    }
    return (res == INF) ? -1 : res;
}