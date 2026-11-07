#include "tmp.cpp"
#include <bits/extc++.h>

// поиск индексов всех вхождений словаря в строку за n sqrt n
void solve() {
        string s; cin >> s;
        int n = s.length();
        int q; cin >> q;
        ve<pr<string, int>> qs(q);
        for (int i = 0; i < q; i++) {
                cin >> qs[i].first >> qs[i].second;
        }
        const int MAXN = 2e5 + 1;
	vi P(MAXN);
	vi suff(MAXN, -1);
        ve<vi> term(MAXN);
        vi head(MAXN);
	ve<vi> go(MAXN, vi(30));
        int V = 0;

	auto add = [ & ](const string &cs, int ind) -> void {
                int v = 0;
		for (int i = 0; i < (int)cs.length(); i++) {
                        int c = cs[i] - 'a';
                        if (!go[v][c]) {
                                go[v][c] = ++V;
                                P[V] = v;
                        }
                        v = go[v][c];
                }
                term[v].push_back(ind);
	};

        vi lens(q);

        int indIn = 0;
        __gnu_pbds::gp_hash_table<string, int> inds;

        for (int i = 0; i < q; i++) {
                int ind = inds[qs[i].first];
                if (ind == 0) {
                        inds[qs[i].first] = indIn;
                        ind = indIn++;
                        add(qs[i].first, ind);
                }
                lens[ind] = qs[i].first.length();
        }

	deque<pii> pq = {{0, 0}};
        suff[0] = 0;
	while (!pq.empty()) {
                auto [v, c] = pq.front();
                pq.pop_front();
		if (v > 0) {
			if (P[v] == 0) {
				suff[v] = 0;
			} else {
				suff[v] = go[suff[P[v]]][c];
                                if (term[suff[v]].empty()) head[v] = head[suff[v]];
                                else head[v] = suff[v];
			}
		}
		for (int nc = 0; nc < 30; nc++) {
                        if (!go[v][nc]) {
                                go[v][nc] = go[suff[v]][nc];
                        } else {
                                pq.emplace_back(go[v][nc], nc);
                        }
                }
	}

        __gnu_pbds::gp_hash_table<int, vi> ans;
        int v = 0;
        for (int i = 0; i < n; i++) {
                int c = s[i] - 'a';
                v = go[v][c];
                int u = v;
                while (u != 0) {
                        for (auto ind : term[u]) {
                                ans[ind].push_back(i - lens[ind] + 2);
                        }
                        u = head[u];
                }
        }

        for (int i = 0; i < q; i++) {
                // sort(all(ans[i]));
                int ind = inds[qs[i].first];
                if ((int)ans[ind].size() < qs[i].second) {
                        cout << -1 << '\n';
                } else {
                        cout << ans[ind][qs[i].second - 1] << '\n';
                }
        }
}