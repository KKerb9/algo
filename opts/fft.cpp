#include "tmp.cpp"

using cd = complex<double>;
using vcd = vector<cd>;
const double PI = acos(-1.0);

void fft(vcd &a, vcd &res, int start, int step, int n, int l, bool inv=false) {
        if (n == 1) {
                res[l] = a[start];
                return;
        }
        int m = n / 2;
        cd wi(1);
        ld angle = 2 * PI / n * (inv ? -1 : 1);
        cd w(cosl(angle), sinl(angle));
        fft(a, res, start, step * 2, n / 2, l, inv);
        fft(a, res, start + step, step * 2, n / 2, l + m, inv);
        for (int i = l; i < l + m; i++) {
                cd v0 = res[i];
                cd v1 = res[i + m];
                res[i] = v0 + wi * v1;
                res[i + m] = v0 - wi * v1;
                if (inv) {
                        res[i] /= 2;
                        res[i + m] /= 2;
                }
                wi *= w;
        }
}

void solve() {
        int n, m; cin >> n >> m;
        vi a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        vb has(m + 1);
        for (auto el : a) has[el] = true;
        int sz = 1;
        while (sz < 2 * (m + 1)) sz <<= 1;
        vcd start(sz);
        start[0] = 1;
        for (int i = 0; i < n; i++) {
                start[a[i]] = 1;
        }
        vcd r1(sz);
        fft(start, r1, 0, 1, sz, 0);
        for (int i = 0; i < sz; i++) start[i] = r1[i] * r1[i];
        fft(start, r1, 0, 1, sz, 0, true);
        vi res;
        for (int i = 1; i <= m; i++) {
                if (!has[i] && llround(r1[i].real())) {
                        cout << "NO\n";
                        return;
                }
                if (llround(r1[i].real()) == 2) res.push_back(i);
        }
        cout << "YES\n";
        cout << res.size() << '\n';
        for (auto el : res) cout << el << ' ';
        cout << '\n';
}

// Точная целочисленная свёртка, пока |ответ| <~ 1e14 / log n (для больших -- разбивать на 15 бит)
ve<ll> convFFT(const ve<ll> &a, const ve<ll> &b) {
        int need = a.size() + b.size() - 1, n = 1;
        while (n < need) n <<= 1;
        ve<cd> fa(all(a)), fb(all(b));
        fa.resize(n), fb.resize(n);
        fft(fa, false);
        fft(fb, false);
        for (int i = 0; i < n; i++) fa[i] *= fb[i];
        fft(fa, true);
        ve<ll> res(need);
        for (int i = 0; i < need; i++) res[i] = llround(fa[i].real());
        return res;
}
