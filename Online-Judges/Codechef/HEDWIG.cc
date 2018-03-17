/*
_HLD _dfs
Merging smaller child into bigger

O(nlogn)
*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long double dbl;
typedef pair<int,int> pii;
typedef vector<int> vi;
 
#define X first
#define Y second
#define mp make_pair
#define pb push_back
#define all(c) begin(c), end(c)
#define mem(c,v) memset(c, v, sizeof c)
#define uni(c) c.resize(distance(c.begin(), unique(all(c))))
 
#define rep(i,n) for(int i=0, _n=(n); i<_n; i++)
#define rep1(i,n) for(int i=1, _n=(n); i<=_n; i++)
#define cout(d) cout << fixed << setprecision(d)
#define err(x) cerr << #x << " = " << x << "\n"
 
#define cases int _t_; cin >> _t_; rep1(_t,_t_)
#define coutt cout << "Case " << _t << ": "
#define io ios_base::sync_with_stdio(false); cin.tie(NULL);
 
const dbl eps=1e-12, pi=acosl(-1);
const int inf=1e16, mod=1e9+7, N=2e5+10;
 
vi t[N];
map<int,int> my[N];
map<int,set<int>> myr[N];
int n, col[N], lucky[N], ans[N];
inline void dfs(int v, int p) {
    my[v][col[v]]++;
    myr[v][1].insert(col[v]);
    for(int ch: t[v]) if(ch != p) {
        dfs(ch, v);
        if(my[ch].size() > my[v].size()) {
            swap(my[v], my[ch]);
            swap(myr[v], myr[ch]);
        }
        for(pii foo: my[ch]) {
            int prevcount = ((my[v].find(foo.X)==my[v].end()) ? 0:my[v][foo.X]);
            myr[v][prevcount + foo.Y].insert(foo.X);
            myr[v][prevcount].erase(foo.X);
            my[v][foo.X] += foo.Y;
        }
    }
    ans[v]=myr[v][lucky[v]].size();
}
 
 
#undef int
int main() {
#define int long long
 
    cin >> n;
    rep1(i,n) cin >> col[i];
    rep1(i,n) cin >> lucky[i];
    rep(i,n-1) {
        int u, v; cin >> u >> v;
        t[u].pb(v); t[v].pb(u);
    }
    dfs(1,1);
    rep1(i,n) cout << ans[i] << ' ';
    return 0;
}
 