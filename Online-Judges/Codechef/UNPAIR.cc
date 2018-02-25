/*
_MST

O(input size)
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
const int N = 1e2 + 10;
 
int n, a[N][N], par[N];
bool vis[N];
inline void mst_prim() { // O(n^2)
    mem(par, -1);
    mem(vis, false);
    bool error = false;
    
    vi key(n,INT_MAX); // modify
    par[0] = key[0] = 0;
    
    ll ans(0);
    rep(i,n) {
        int mi(INT_MAX), k(-1); // modify
        rep(j,n) {
            if(!vis[j] and key[j] < mi) // modify
                mi = key[j], k = j;
        }
        if(k == -1) {
            error = true;
            break;
        }
        vis[k] = true;
        ans += key[k] << 1;
        rep(j,n) {
            // 1st condition changes, third toggles
            if(!vis[j] and a[k][j] != 0 and a[k][j] < key[j])
                par[j] = k, key[j] = a[k][j];
        }
    }
    if(error) ans = -1;
    if(n == 1) ans = a[0][0] - !a[0][0];
    
    cout << ans << '\n';
}
 
int main() {
    int q; cin >> q;
    while(q--) {
        cin >> n;
        rep(i,n)rep(j,n) cin >> a[i][j];
        mst_prim();
    }
    return 0;
}