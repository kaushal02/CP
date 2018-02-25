/*
_DSU _offline

O(n + q*log(q) + m*log(m))
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;

#define X first
#define Y second
#define mp make_pair
#define all(c) begin(c), end(c)
#define eb emplace_back // tie, ignore, get<i>(a)
#define mem(a,val) memset(a, (val), sizeof a)
#define uni(c) c.resize(distance(c.begin(), unique(all(c))))

#define rep(i,n) for(ll i = 0, _n = (n); i < _n; i++)
#define rep1(i,a,b) for(ll i = a, _b = (b); i <= _b; i++)
#define rep2(i,b,a) for(ll i = b, _a = (a); i >= _a; i--)

#define case(ans) "Case #" << _t << ": " << ans << "\n"
#define cout(d) cout << fixed << setprecision(d)
#define err(x) cerr << #x << " = " << x << '\n'

#define TTi template<typename T> inline

const ll inf = 1e16, mod = 1e9 + 7;
const double eps = 1e-16;
const int N = 1e5 + 10;

struct dsu {
    vi par, sz;
    ll tot;
    dsu(int n): par(n), sz(n), tot(0) { rep(i,n) par[i] = i, sz[i] = 1;}
    int root(int a) { return a == par[a] ? a : par[a] = root(par[a]);}
    void merge(int a, int b) {
        a = root(a);
        b = root(b);
        if(a == b) return;
        if(sz[a] < sz[b]) swap(a,b);
        
        tot += (ll)sz[a]*sz[b];
        sz[a] += sz[b];
        sz[b] = 0;
        par[b] = a;
    }
};

ll ans[N];
pii qu[N];
pair<int,pii> ed[N];
int main() {
    int n, m, q;
    cin >> n >> m >> q;
    
    int u, v, w;
    rep(i,m) {
        cin >> u >> v >> w;
        ed[i] = {w,{u,v}};
    }
    sort(ed, ed + m, greater<pair<int,pii>>());
    
    int r;
    rep(i,q) {
        cin >> r;
        qu[i] = {r,i};
    }
    sort(qu, qu + q, greater<pii>());
    
    dsu d(n+1);
    
    int j(0);
    rep(i,q) {
        while(j < m and ed[j].X >= qu[i].X)
            d.merge(ed[j].Y.X, ed[j].Y.Y), j++;
        ans[qu[i].Y] = d.tot;
    }
    rep(i,q) cout << ans[i] << ' ';
    return 0;
}
