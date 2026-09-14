#include "tmp.cpp"

void solve() {
        int n; cin >> n;
        int N = (1 << n);
        vi p(N);
        for (int i = 0; i < N; i++) cin >> p[i];
        vi f = p;
        for (int i = 0; i < n; i++) {
                for (int mask = 0; mask < N; mask++) {
                        if (mask & (1 << i)) f[mask] -= f[mask ^ (1 << i)];
                }
        }
        for (auto& el : f) cout << el << ' ';
        cout << '\n';
}