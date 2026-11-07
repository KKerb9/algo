#include "tmp.cpp"

// z[i] = lcp(s, s[i..]), z[0] = 0
vi z_func(const string &s) {
        int n = s.length();
        vi z(n);
        int l = 0, r = 0;
        for (int i = 1; i < n; i++) {
                if (i < r) z[i] = min(r - i, z[i - l]);
                while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
                if (i + z[i] > r) l = i, r = i + z[i];
        }
        return z;
}

// p[i] = длина наибольшего собственного префикса-суффикса s[0..i]
vi pref_func(const string &s) {
        int n = s.length();
        vi p(n);
        for (int i = 1; i < n; i++) {
                int j = p[i - 1];
                while (j > 0 && s[j] != s[i]) j = p[j - 1];
                if (s[i] == s[j]) j++;
                p[i] = j;
        }
        return p;
}
