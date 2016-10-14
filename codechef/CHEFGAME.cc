/*
_mst

O(∑(n^2*d))
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

const ll inf = 1e17, mod = 747474747;
const double eps = 1e-16;
const int N = 6666 + 10;

bool vis[N];
ll n, a[N][N], par[N];
inline ll mst_prim() {
    // O(n^2) maximum spanning tree
    mem(par, -1);
    mem(vis, false);
    bool error = false;
    
    vll key(n,-1);
    par[0] = 0;
    key[0] = 1;
    
    ll ans(1); // weight of MST
    rep(i,n) {
        ll ma(-1), k(-1);
        rep(j,n) {
            if(!vis[j] and key[j] > ma)
                ma = key[j], k = j;
        }
        if(k == -1) {
            error = true;
            break;
        }
        vis[k] = true;
        ans = max(key[k], 1LL) % mod * ans % mod; // modify
        rep(j,n) {
            if(!vis[j] and a[k][j] > key[j])
                par[j] = k, key[j] = a[k][j];
        }
     }
    assert(!error);
    return ans;
}

inline ll sqr(ll x) { return x * x;}

int d, p[N][5];
void MAIN() {
    int q; cin >> q;
    while(q--) {
        cin >> n >> d;
        rep(i,n)rep(j,d) cin >> p[i][j];
        rep(i,n)rep(j,n) {
            a[i][j] = 0;
            rep(k,d) a[i][j] += sqr(p[i][k] - p[j][k]);
        }
        cout << mst_prim() << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    
    clock_t start = clock();
    srand(time(NULL));
    MAIN();
    clock_t end = clock();
    double time = (double) (end - start) / CLOCKS_PER_SEC;
#ifdef LOCAL
    fprintf(stderr, "Total running time: %.3lf s\n", time);
#endif
    return 0;
}
