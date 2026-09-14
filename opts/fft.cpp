#include "tmp.cpp"

using cd = complex<ld>;
using vcd = vector<cd>;
const ld PI = acosl(-1);

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
        string a, b; cin >> a >> b;
        int n1 = a.length();
        int n2 = b.length();
        if (a[0] == '0' || b[0] == '0') {
                cout << 0 << '\n';
                return;
        }
        bool f1 = a[0] == '-';
        bool f2 = b[0] == '-';
        vcd A, B;
        for (int i = n1 - 1; i >= (int)f1; i--) A.push_back(a[i] - '0');
        for (int i = n2 - 1; i >= (int)f2; i--) B.push_back(b[i] - '0');
        n1 -= f1;
        n2 -= f2;
        int n = n1 + n2;
        while (n1 < n) {
                A.push_back(0);
                n1++;
        }
        while (n > n2) {
                B.push_back(0);
                n2++;
        }
        while (__builtin_popcount(n) > 1) {
                A.push_back(0);
                B.push_back(0);
                n++;
        }
        vcd r1(n), r2(n);
        fft(A, r1, 0, 1, n, 0);
        fft(B, r2, 0, 1, n, 0);
        vcd r(n);
        for (int i = 0; i < n; i++) {
                r[i] = r1[i] * r2[i];
        }
        fft(r, A, 0, 1, n, 0, true);
        if (f1 ^ f2) {
                cout << '-';
        }
        ll nakop = 0;
        vi ans;
        ans.reserve(n);
        for (int i = 0; i < n; i++) {
                nakop += llround(A[i].real());
                ans.push_back(nakop % 10);
                nakop /= 10;
        }
        while (nakop) {
                cout << nakop % 10;
                nakop /= 10;
        }
        int ind = (int)ans.size() - 1;
        while (ans[ind] == 0) ind--;
        for (; ind >= 0; ind--) cout << ans[ind];
        cout << '\n';
}
