#include "tmp.cpp"

const int k = 320;

struct Qu {
        int l, r, ind;
};

// Пример Mo: композиция перестановок на [l, r), ответ -- сумма (j + 1) * b[j].
void MO() {
        int n, m; cin >> n >> m;
        vector<vector<int>> a(n, vector<int>(m));
        for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                        cin >> a[i][j];
                }
        }
        int q; cin >> q;
        int sz = n / k + 1;
        vector<vector<Qu>> bls(sz);
        for (int i = 0; i < q; i++) {
                int l, r; cin >> l >> r; l--;
                Qu cur; cur.ind = i; cur.l = l; cur.r = r;
                bls[l / k].push_back(cur);
        }
        for (int i = 0; i < sz; i++) {
                if (i % 2) {
                        sort(all(bls[i]), [&](Qu l, Qu r) {
                                if (l.r == r.r) return l.l < r.l;
                                return l.r > r.r;
                        });
                } else {
                        sort(all(bls[i]), [&](Qu l, Qu r) {
                                if (l.r == r.r) return l.l < r.l;
                                return l.r < r.r;
                        });
                }
        }
        int l = 0, r = 0;
        vector<int> b(m);
        iota(all(b), 1);
        vector<int> ans(q);
        int curans = 0;
        for (int i = 0; i < sz; i++) {
                for (auto e : bls[i]) {
                        int tl = e.l;
                        int tr = e.r;
                        while (l > tl) {
                                l--;
                                vector<int> wb = b;
                                curans = 0;
                                for (int j = 0; j < m; j++) {
                                        b[j] = wb[a[l][j] - 1];
                                        curans += (j + 1) * b[j];
                                }
                        }
                        while (r < tr) {
                                vector<int> wb = b;
                                curans = 0;
                                for (int j = 0; j < m; j++) {
                                        b[j] = a[r][wb[j] - 1];
                                        curans += (j + 1) * b[j];
                                }
                                r++;
                        }
                        while (l < tl) {
                                vector<int> wb = b;
                                curans = 0;
                                for (int j = 0; j < m; j++) {
                                        b[a[l][j] - 1] = wb[j];
                                }
                                for (int j = 0; j < m; j++) {
                                        curans += b[j] * (j + 1);
                                }
                                l++;
                        }
                        while (r > tr) {
                                r--;
                                vector<int> wb = b;
                                vector<int> inds(m);
                                for (int j = 0; j < m; j++) {
                                        inds[a[r][j] - 1] = j + 1;
                                }
                                curans = 0;
                                for (int j = 0; j < m; j++) {
                                        b[j] = inds[wb[j] - 1];
                                        curans += (j + 1) * b[j];
                                }
                        }
                        ans[e.ind] = curans;
                }
        }
        for (auto el : ans) cout << el << '\n';
}
