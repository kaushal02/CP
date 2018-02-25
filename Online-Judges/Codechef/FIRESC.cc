/*
_DSU

O((n + m) * α(n)) per query
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
    dsu(int n): par(n), sz(n) { rep(i,n) par[i] = i, sz[i] = 1;}
    int root(int a) { return a == par[a] ? a : par[a] = root(par[a]);}
    void merge(int a, int b) {
        a = root(a);
        b = root(b);
        if(a == b) return;
        if(sz[a] < sz[b]) swap(a,b);
        
        sz[a] += sz[b];
        par[b] = a;
    }
};

int main() {
    int q; cin >> q;
    while(q--) {
        int n, m; cin >> n >> m;
        dsu d(n);
        rep(i,m) {
            int x, y; cin >> x >> y;
            d.merge(x-1, y-1);
        }
        int cnt(0), ways(1);
        rep(i,n) if(d.root(i) == i) {
            cnt++;
            ways = (ll)ways * d.sz[i] % mod;
        }
        cout << cnt << " " << ways << "\n";
    }
    return 0;
}