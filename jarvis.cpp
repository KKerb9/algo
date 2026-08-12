int maxn = 2e4 + 100;
int n;
vector<pt> a(maxn);
vector<int> used(maxn), ans(maxn);
int next(int x, int f) {
    int mn = -1;
    for (int i = 0; i < n; ++i)
        if (!used[i] || (i == f && i != x)) {
            if (mn == -1) {
                mn = i;
            } else {
                pt p1 = a[i] - a[x];
                pt p2 = a[mn] - a[x];
                if (p1 % p2 > 0) {
                    mn = i;
                } else if (p1 % p2 == 0) {
                    if (p1.len2() < p2.len2())
                        mn = i;
                }
            }
        }
 
    return mn;
}

    cin >> n;
 
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    int cnt = 1;
    while (true) {
        int l = -1;
        for (int i = 0; i < n; ++i)
            if (!used[i]) {
                if (l == -1)
                    l = i;
                else {
                    if (a[i].y < a[l].y || (a[i].y == a[l].y && a[i].x < a[l].x))
                        l = i;
                }
            }
        if (l == -1)
            break;
        used[l] = 1;
        int f = l;
        while (true) {
            ans[l] = cnt;
            int nxt = next(l, f);
            if (nxt == f || nxt == -1)
                break;
            used[nxt] = 1;
 
            l = nxt;
        }
        cnt++;
    }
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << '\n';
    }
 
