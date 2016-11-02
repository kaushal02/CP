/*
_dfs _merge
Merging two maps into the bigger of the two and compression as in DSU.
https://www.hackerrank.com/contests/moodysuniversityhackathon/challenges/distinctly-colored-nodes-in-a-tree
O(n*log^2(n))
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;

#define X first
#define Y second
#define sz(c) (ll)c.size()
#define rep(i,n) for(ll i = 0, _n = (n); i < _n; i++)
#define rep1(i,a,b) for(ll i = a, _b = (b); i <= _b; i++)
#define rep2(i,b,a) for(ll i = b, _a = (a); i >= _a; i--)
#define mem(a,val) memset(a, (val), sizeof a)
#define mp make_pair
#define eb emplace_back // tie, ignore, get<i>(a)
#define all(c) (c).begin(), (c).end()
#define uni(c) c.resize(distance(c.begin(), unique(all(c))))
#define case(ans) "Case #" << _t << ": " << ans << "\n"
#define cout(d) cout << fixed << setprecision(d)
#define err(x) cerr << #x << " = " << x << '\n'
const ll mod = 1e9 + 7, inf = 1e16, N = 2e5 + 10;
const double eps = 1e-16;

vi t[N];
map<int,int> tot;
ll n, c[N], id[N], type, sum;
struct node {
    map<int,int> col;
    ll full = 0;
    inline void add(int c, int n = 1) {
        col[c] += n;
        if(col[c] == tot[c]) full++;
    }
    inline void contri() {
        sum += (type - full) * col.size();
    }
} tr[N];
inline void merge(int u, int v) {
    int a = id[u], b = id[v];
    if(tr[a].col.size() < tr[b].col.size()) swap(a, b), swap(u, v);
    for(auto x: tr[b].col) tr[a].add(x.X, x.Y);
    id[v] = id[b] = a;
}
inline void dfs(int v, int p) {
    tr[id[v] = v].add(c[v]);
	for(int ch: t[v]) {
		if(ch != p) {
			dfs(ch, v);
			merge(ch, v);
		}
	}
    if(v != p) tr[id[v]].contri();
}

int main() {
	cin >> n;
	rep1(i,1,n) {
        cin >> c[i];
        tot[c[i]]++;
	}
    type = tot.size();
	rep(i,n-1) {
		int x, y;
		cin >> x >> y;
		t[x].eb(y);
		t[y].eb(x);
	}
	dfs(1,1);
	cout << sum << '\n';
}
