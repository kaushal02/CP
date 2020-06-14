/*
_DSU _offline

O(n * log(n) + (q + m) * (α(n) + log(n)))
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long

#define cout(d) cout << fixed << setprecision(d)
template <typename T> inline bool Max(T &a, T b) { return (a<b ? a=b,1:0);}
template <typename T> inline bool Min(T &a, T b) { return (a>b ? a=b,1:0);}

const double eps = 1e-12, pi = acosl(-1);
const int inf = 1e16, mod = 1e9 + 7, N = 2e6 + 10;

#define pq(c) priority_queue<c,vector<c>,compare<c>>
template<class T> struct compare {
	bool operator()(const T& l, const T& r) const {
		return l.second.second < r.second.second;
	}
};

struct dsu {
	int k;
	vector <int> par, sz, wei, id;
	typedef pair <int, pair <int, int>> myStruct;
	pq(myStruct) wt_q;
	dsu(int n, stack <int> *w): k(0), par(n), sz(n, 1), wei(n, 0), id(n, 0) {
		for (int i = 0; i < n; i++) {
			wt_upd(i, w[i].top());
			par[i] = i;
		}
	}
	int root(int a) { 
		if (par[a] == a) {
			return a;
		}
		return par[a] = root(par[a]);
	}
	void merge(int a, int b) {
		a = root(a);
		b = root(b);
		if (a == b) return;
		if (sz[a] < sz[b]) swap(a, b);
		sz[a] += sz[b];
		par[b] = a;
		wt_upd(a, wei[b]);
	}
	void wt_upd(int a, int wt_chng) {
		wei[a] += wt_chng;
		id[a] = ++k;
		wt_q.push({a, {k, wei[a]}});
	}
	int weight() {
		while (true) {
			auto tmp = wt_q.top();
			if (tmp.first != root(tmp.first) or tmp.second.first < id[tmp.first]) {
				wt_q.pop();
			} else {
				break;
			}
		}
		return wt_q.top().second.second;
	}
};

signed main() {
	int n, m, q; cin >> n >> m >> q;
	stack <int> w[n];
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		w[i].push(x);
	}
	vector <pair <int, int>> e(m);
	for (int i = 0; i < m; i++) {
		cin >> e[i].first >> e[i].second;
	}
	vector <bool> use(m, true);
	vector <pair <int, int>> qu(q);
	for (int i = 0; i < q; i++) {
		string typ; cin >> typ;
		if (typ == "D") {
			int k; cin >> k;
			use[k - 1] = false;
			qu[i] = {1, k - 1};
		} else {
			int a, x; cin >> a >> x;
			w[a - 1].top() -= x;
			w[a - 1].push(x);
			qu[i] = {2, a - 1};
		}
	}

	dsu d(n, w);
	for (int i = 0; i < n; i++) {
		w[i].pop();
	}
	for (int i = 0; i < m; i++) {
		if (use[i]) {
			d.merge(e[i].first - 1, e[i].second - 1);
		}
	}
	vector <int> ans(q);
	for (int i = q; i--; ) {
		ans[i] = d.weight();
		if (qu[i].first == 1) {
			int tmp = qu[i].second;
			d.merge(e[tmp].first - 1, e[tmp].second - 1);
		} else {
			int tmp = qu[i].second;
			d.wt_upd(d.root(tmp), w[tmp].top());
			w[tmp].pop();
		}
	}
	for (int i = 0; i < q; i++) {
		cout << ans[i] << '\n';
	}
    return 0;
}
