// point2d template
int half(pt& p) {
    if ((p.y) > 0 || (p.y) == 0 && (p.x) >= 0) {
        return 0;
    }
    return 1;
}
bool comp(pt& l, pt& r) {
    if (half(l) < half(r))
        return 1;
    if (half(l) > half(r))
        return 0;
    if ((l % r) == 0) {
        return l.len2() < r.len2();
    }
    return (l % r) > 0;
}
    for (int i = 0; i < n; ++i)
        cin >> a[i].second >> a[i].first;
    sort(a.begin(), a.end());
    vector<pt> p;
    pt b = pt(a[0].second, a[0].first);
    for (int i = 1; i < n; ++i) {
        pt j = pt(a[i].second, a[i].first);
        j = j - b;
        p.push_back(j);
    }
    sort(p.begin(), p.end(), comp);
    vector<pt> ans;
    pt g = pt(0, 0);
    ans.push_back(g);
    ans.push_back(p[0]);
    for (int i = 1; i < n - 1; ++i) {
        while (ans.size() >= 2) {
            pt p1 = p[i] - ans.back();
            pt p2 = ans.back() - ans[(int)ans.size() - 2];
            if ((p1 % p2) >= 0)
                ans.pop_back();
            else
                break;
        }
        ans.push_back(p[i]);
    }
    cout << ans.size() << '\n';
    for (int i = 0; i < ans.size(); ++i) {
        ans[i] = ans[i] + b;
    }
