#include "tmp.cpp"

void xoraboba(vll &a, vll &b, vll &res, int l, int r) {
	if (r - l == 1) {
		res[l] = a[l] * b[l];
		return;
	}
        int mid = (r - l) / 2;
	for (int i = l; i < l + mid; i++) {
                ll x = a[i];
                ll y = a[i + mid];
		a[i] = x + y;
		a[i + mid] = x - y;
                x = b[i];
                y = b[i + mid];
		b[i] = x + y;
		b[i + mid] = x - y;
	}
	xoraboba(a, b, res, l, l + mid);
	xoraboba(a, b, res, l + mid, r);
	for (int i = l; i < l + mid; i++) {
                ll x = res[i];
                ll y = res[i + mid];
		res[i] = (x + y) / 2;
		res[i + mid] = (x - y) / 2;
	}
}