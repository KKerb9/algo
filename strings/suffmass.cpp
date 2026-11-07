#include "tmp.cpp"

void solve() {
        ve<string> alph;
        char ty;
        int sz = 0;
        vi time;
        string text = "";
        while (cin >> ty) {
                string s; cin >> s;
                for (auto &c : s) {
                        if (c < 'a') c += 'a' - 'A';
                }
                if (ty == '?') {
                        alph.push_back(s);
                        time.push_back(sz);
                } else {
                        text += s;
                        sz += s.length();
                }
        }

        text.push_back('$');
        int n = text.length();
        vi p(n);
        iota(all(p), 0);
        vi c(n);
        sort(all(p), [ & ](int i, int j){
                return text[i] < text[j];
        });
        int cnt = 1;
        for (int i = 1; i < n; i++) {
                if (text[p[i]] == text[p[i - 1]]) {
                        c[p[i]] = c[p[i - 1]];
                } else {
                        c[p[i]] = cnt++;
                }
        }
        int shift = 1;
        vi cur(n);
        for (int k = 1; k < n; k *= 2) {
                sort(all(p), [ & ](int i, int j){
                        return c[i] < c[j] || (c[i] == c[j] && c[(i + shift) % n] < c[(j + shift) % n]);
                });
                cnt = 0;
                cur[p[0]] = cnt++;
                for (int i = 1; i < n; i++) {
                        if (c[p[i - 1]] != c[p[i]] || c[(p[i - 1] + shift) % n] != c[(p[i] + shift) % n]) {
                                cur[p[i]] = cnt++;
                        } else {
                                cur[p[i]] = cur[p[i - 1]];
                        }
                }
                swap(c, cur);
                shift *= 2;
        }
        const ull P = 103;
        ve<ull> degs(n + 1);
        degs[0] = 1;
        for (int i = 1; i <= n; i++) degs[i] = degs[i - 1] * P;
        ve<ull> hash(n + 1);
        for (int i = 0; i < n; i++) {
                hash[i + 1] = hash[i] * P + (text[i] - '$');
        }

        auto get = [ & ](int l, int r) -> ull {
                return hash[r] - hash[l] * degs[r - l];
        };

        ve<vi> spt(30, vi(n));
        for (int i = 0; i < n; i++) spt[0][i] = p[i];
        for (int l = 1; l < 30; l++) {
                int len = 1 << l;
                for (int i = 0; i <= n - len; i++) {
                        spt[l][i] = min(spt[l - 1][i], spt[l - 1][i + len / 2]);
                }
        }

        auto getMin = [ & ](int l, int r) -> int {
                int k = __lg(r - l);
                return min(spt[k][l], spt[k][r - (1 << k)]);
        };

        for (int i = 0; i < (int)alph.size(); i++) {
                ull curh = 0;
                for (auto c : alph[i]) {
                        curh = curh * P + c - '$';
                }
                int l = 0, r = n;
                while (r - l > 1) {
                        int mid = (r + l) / 2;
                        bool f = false;
                        for (int j = 0; j < (int)alph[i].length(); j++) {
                                if (p[mid] + j >= n) {
                                        l = mid;
                                        f = true;
                                        break;
                                }
                                if (text[p[mid] + j] < alph[i][j]) {
                                        l = mid;
                                        f = true;
                                        break;
                                } else if (text[p[mid] + j] > alph[i][j]) {
                                        r = mid;
                                        f = true;
                                        break;
                                }
                        }
                        if (!f) r = mid;
                }
                int tl = r - 1, tr = n;
                while (tr - tl > 1) {
                        int mid = (tr + tl) / 2;
                        bool f = false;
                        for (int j = 0; j < (int)alph[i].length(); j++) {
                                if (text[p[mid] + j] > alph[i][j]) {
                                        tr = mid;
                                        f = true;
                                        break;
                                }
                        }
                        if (!f) tl = mid;
                }
                if (tr == r) {
                        cout << "NO\n";
                } else {
                        cout << ((getMin(r, tr) + alph[i].length() <= time[i]) ? "YES\n" : "NO\n");
                }
        }
}

// O(n log n), индексы суффиксов без служебного символа
vi suffMassFast(string s) {
        s += char(1);  // +"$"
        int n = s.length();
        vi p(n), c(n);
        iota(all(p), 0);
        sort(all(p), [ & ](int i, int j){
                return s[i] < s[j];
        });
        int cnt = 1;
        for (int i = 1; i < n; i++) {
                if (s[p[i]] == s[p[i - 1]]) {
                        c[p[i]] = c[p[i - 1]];
                } else {
                        c[p[i]] = cnt++;
                }
        }
        vi cur(n);
        for (int shift = 1; shift < n && cnt < n; shift *= 2) {
                vi freq(n), pref(n);
                for (auto x : c) freq[x]++;
                for (int i = 1; i < n; i++) pref[i] = pref[i - 1] + freq[i - 1];
                // Сдвиг p на -shift даёт порядок по второй половине пары.
                for (int i = 0; i < n; i++) {
                        int pos = (p[i] - shift + n) % n;
                        cur[pref[c[pos]]++] = pos;
                }
                swap(p, cur);
                cnt = 0;
                cur[p[0]] = cnt++;
                for (int i = 1; i < n; i++) {
                        if (c[p[i - 1]] != c[p[i]] || c[(p[i - 1] + shift) % n] != c[(p[i] + shift) % n]) {
                                cur[p[i]] = cnt++;
                        } else {
                                cur[p[i]] = cur[p[i - 1]];
                        }
                }
                swap(c, cur);
        }
        p.erase(p.begin());
        return p;
}

// O(n), p = suffMassFast(s); lcp[i] = lcp(s[p[i]..], s[p[i + 1]..]), последний = 0.
vi kasai(const string& s, const vi& p) {
        int n = s.length(), k = 0;
        vi lcp(n), rank(n);
        for (int i = 0; i < n; i++) rank[p[i]] = i;
        for (int i = 0; i < n; i++, k ? k-- : 0) {
                if (rank[i] == n - 1) {
                        k = 0;
                        continue;
                }
                int j = p[rank[i] + 1];
                while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
                lcp[rank[i]] = k;
        }
        return lcp;
}
