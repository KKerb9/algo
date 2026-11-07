#pragma once
#include "tmp.cpp"





struct Sieve {  // линейное решето: lp, простые, phi, mu
        vi lp, primes, phi, mu;

        Sieve(int n) : lp(n + 1), phi(n + 1), mu(n + 1) {
                phi[1] = mu[1] = 1;
                for (int i = 2; i <= n; i++) {
                        if (!lp[i]) {
                                lp[i] = i;
                                phi[i] = i - 1;
                                mu[i] = -1;
                                primes.push_back(i);
                        }
                        for (int p : primes) {
                                if (p > lp[i] || (ll)i * p > n) break;
                                lp[i * p] = p;
                                if (i % p == 0) {
                                        phi[i * p] = phi[i] * p;
                                        mu[i * p] = 0;
                                } else {
                                        phi[i * p] = phi[i] * (p - 1);
                                        mu[i * p] = -mu[i];
                                }
                        }
                }
        }
};

ll phiFunc(ll n) {  // O(sqrt n)
        ll res = n;
        for (ll p = 2; p * p <= n; p++) {
                if (n % p) continue;
                while (n % p == 0) n /= p;
                res -= res / p;
        }
        if (n > 1) res -= res / n;
        return res;
}
