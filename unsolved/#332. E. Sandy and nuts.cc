/*
_bitmask _DP
Traversing all submasks of a mask.
[CodeForces] http://codeforces.com/problemset/problem/599/E

O(3^n)
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
const int N = 15;

ll dp[1<<N][N];
int n, t[N][N], st[N][N], dp1[1<<N], dp2[1<<N][N];

inline bool lcaok(int m) {
    if(dp1[m] + 1) return dp1[m];
    dp1[m] = 1;
    rep(i,n) if(m>>i&1) {
        rep(j,n) if(st[i][j]) {
            dp1[m] &= (m>>j&1);
        }
    }
    return dp1[m];
}
inline bool treeok(int m, int r) {
    if(dp2[m][r] + 1) return dp2[m][r];
    dp2[m][r] = 1;
    rep(i,n) if(m>>i&1) {
        rep(j,n) if(t[i][j]) {
            dp2[m][r] &= ((m>>j&1) or (j==r));
        }
    }
    return dp2[m][r];
}
inline ll f(int m, int r) {
    assert(m>>r&1);
    if(dp[m][r] + 1) return dp[m][r];
    ll &ans = dp[m][r];
    ans = 0;
    
    int sm = 1<<r ^ m;
    if(!sm) {
        return ans = 1;
    }
    int bit = 0;
    while((1<<bit) <= sm) bit++; bit--;
    for(int subm = sm; subm; subm = (sm & (subm - 1))) {
        if(subm>>bit&1) {
            int restm = m ^ subm;
            if(lcaok(subm) and lcaok(1<<r ^ restm)) {
                int edges = 0, lcas = 0, nr;
                rep(i,n) if(subm>>i&1) {
                    if(t[r][i]) {
                        edges++;
                        nr = i;
                    }
                    if(st[r][i]) {
                        lcas++;
                    }
                }
                
                if(edges > 1 or lcas > 1) {
                    continue;
                }
                else if(edges == 1) {
                    if(treeok(subm, r) and treeok(1<<r ^ restm, r)) {
                        ans += f(subm, nr) * f(restm, r);
                    }
                }
                else if(edges == 0) {
                    if(treeok(subm, r) and treeok(1<<r ^ restm, r)) {
                        rep(i,n) if(subm>>i&1) {
                            ans += f(subm, i) * f(restm, r);
                        }
                    }
                }
            }
        }
    }
    return ans;
}

int main() {
    mem(dp, -1); mem(dp1, -1); mem(dp2, -1);
    int m, q; cin >> n >> m >> q;
    rep(i,m) {
        int x, y; cin >> x >> y;
        t[x-1][y-1] = t[y-1][x-1] = 1;
    }
    rep(i,q) {
        int x, y, z; cin >> x >> y >> z;
        st[z-1][x-1] = st[z-1][y-1] = 1;
    }
    cout << f((1<<n)-1, 0) << '\n';
}