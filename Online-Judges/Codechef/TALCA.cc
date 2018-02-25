/*
_LCA

O(n + q*log(n))
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
const ll mod = 1e9 + 7, inf = 1e16, N = 2e6 + 10;
const double eps = 1e-15;
 
vi t[N];
int n, h[N], lca[25][N];
inline void dfs(int v, int p) {
    lca[0][v] = p; // lca[i][v] is (1<<i)'th ancestor of v, or root
    rep1(i,1,20) lca[i][v] = lca[i - 1][lca[i - 1][v]];
    for(int ch: t[v]) if(ch != p) h[ch] = h[v] + 1, dfs(ch, v);
}
inline int get_lca(int u, int v) {
    if(h[u] < h[v]) swap(u,v);
    
    int x = h[u] - h[v];
    rep(i,20) {
        if(x & 1) u = lca[i][u];
        x >>= 1;
    }
    if(u == v) return u;
    
    rep2(i,18,0) if(lca[i][u] != lca[i][v]) u = lca[i][u], v = lca[i][v];
    return lca[0][u];
}
inline int deeper(int x, int y) {
    return h[x] > h[y] ? x:y;
}
 
int main() {
    cin >> n;
    int u, v, r;
    rep(i,n-1) {
        cin >> u >> v;
        t[u].eb(v);
        t[v].eb(u);
    }
    dfs(1,1);
    
    int q, l1, l2; cin >> q;
    while(q--) {
        cin >> r >> u >> v;
        l1 = get_lca(u,r);
        l2 = get_lca(v,r);
        r = get_lca(u,v);
        cout << deeper(deeper(l1, l2), r) << '\n';
    }
    return 0;
}
