

using ld = long double;

ld eps = 1e-7;

bool lt(ld a, ld b) {
    return b - a > eps;
}

bool eq(ld a, ld b) {
    return abs(a - b) < eps;
}

int sgn(ld a) {
    if (a > 0)
        return 1;
    if (a < 0)
        return -1;
    return 0;
}
template <typename T>
struct mpt {
    T x, y;
    mpt() {
        x = 0;
        y = 0;
    }

    mpt(T _x, T _y) {
        x = _x;
        y = _y;
    }

    mpt(mpt& a, mpt& b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }

    mpt operator+(const mpt& a) const {
        return mpt(x + a.x, y + a.y);
    }

    mpt operator-(const mpt& a) const {
        return mpt(x - a.x, y - a.y);
    }

    mpt operator*(const ld k) const {
        return mpt(x * k, y * k);
    }

    bool operator==(const mpt& a) const {
        return eq(x, a.x) && eq(y, a.y);
    }

    T operator*(const mpt& a) const {
        return x * a.x + y * a.y;
    }

    T operator%(const mpt& a) const {
        return x * a.y - y * a.x;
    }

    T len2() const {
        return x * x + y * y;
    }

    ld len() const {
        return sqrt(len2());
    }

    mpt turn90() const {
        return mpt(-y, x);
    }

    ld angle(mpt& a) const {
        mpt p1 = mpt(x, y);
        return atan2l(p1 % a, p1 * a);
    }

    mpt pol() const {
        mpt a = mpt(1, 0);
        return angle(a);
    }
};

using pt = mpt<int>;

template <typename T>
struct mln {
    T a, b, c;

    mln(T _a, T _b, T _c) {
        a = _a;
        b = _b;
        c = _c;
    }

    T g(const pt& p) const {
        return a * p.x + b * p.y + c;
    }

    pt nr() const {
        return pt(a, b);
    }

    pt pr() const {
        return pt(-b, a);
    }

    mln(pt& t, pt& q) {
        pt p = pt(t, q);
        a = p.y;
        b = -p.x;
        c = -a * q.x - b * q.y;
    }

    ld dist(const pt& p) const {
        pt n = nr();
        return abs(a * p.x + b * p.y + c) / n.len();
    }

    pt proj(const pt& p) const {
        pt n = nr();
        ld d = (ld)g(p) / (ld)n.len2();
        n = p - n * d;
        return n;
    }
};

using ln = mln<ld>;
template <typename T>
struct mcr {
    pt c;
    T r;
    T x, y;
    mcr(pt& _c, T _r) {
        c = _c;
        x = c.x;
        y = c.y;
        r = _r;
    }
    array<pt, 2> fln(const ln& l) const {
        pt inf = pt(1e9, 1e9);
        ld d = l.dist(c);
        if (lt(r, d))
            return {inf, inf};
        pt p = l.proj(c);
        pt v = l.pr();
        d = r * r - d * d;
        d = sqrt(d);
        d /= v.len();
        v = v * d;
        pt p1 = p + v;
        pt p2 = p - v;
        if (eq(l.dist(c), r))
            return {p1, inf};
        return {p1, p2};
    }

    array<pt, 2> fcr(const mcr& w) const {
        if (c == w.c) {
            if (r == w.r)
                return {pt(-1e9, -1e9), pt()};
            return {pt(1e9, 1e9), pt()};
        }
        ln l = ln(2 * (x - w.x), 2 * (y - w.y), r * r - w.r * w.r + w.x * w.x + w.y * w.y - x * x - y * y);
        return fln(l);
    }

    array<pt, 2> tang(pt& p) {
        pt v = pt(c, p);
        ld r1 = sqrtl(v.len2() - r * r);
        mcr w = mcr(p, r1);
        return fcr(w);
    }
};

using cr = mcr<ld>;
istream& operator>>(istream& is, pt& a) {
    is >> a.x >> a.y;
    return is;
}

ostream& operator<<(ostream& is, pt& a) {
    is << a.x << ' ' << a.y;
    return is;
}

vector<pt> a;

bool f(pt p, pt l, pt r) {
    return sgn(p % l) != sgn(p % r) || sgn(p % l) == 0 || sgn(p % r) == 0;
}

int32_t main() {
    int n, m, k;
    cin >> n >> m >> k;
    a.resize(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    while (m--) {
        pt p;
        cin >> p;
        int l = 1;
        int r = n - 1;
        if (f(p - a[0], a[l] - a[0], a[r] - a[0])) {
            while (r - l > 1) {
                int x = (l + r) / 2;
                if (f(p - a[0], a[l] - a[0], a[x] - a[0]))
                    r = x;
                else
                    l = x;
            }
            pt u = pt(a[l], a[l + 1]);
            pt v = pt(a[l], p);
            if (f(v, u, a[0] - a[l]) && f(p - a[l + 1], a[0] - a[l + 1], a[l] - a[l + 1]))
                k--;
        }
    }
    if (k <= 0) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
    return 0;
}
