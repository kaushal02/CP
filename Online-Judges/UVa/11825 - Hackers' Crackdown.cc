/*
_bitmask _DP
Traversing all submasks of a mask

O(3^n) per test case
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

#define cout(d) cout << fixed << setprecision(d)
#define err(x) cerr << #x << " = " << x << '\n'

const ll inf = 1e16, mod = 1e9 + 7;
const double eps = 1e-16;
const int N = 18;

int n, a[N], ones[N], dp[1<<N], dp1[1<<N];
int main() {
    int mb;
    rep(i,N) ones[i] = (1<<i+1) - 1;
    
    int casenum = 0;
    cin >> n; casenum++;
    while(n) {
        rep(i,n) {
            a[i] = 1<<i;
            int m; cin >> m;
            while(m--) {
                int x; cin >> x;
                a[i] |= 1<<x;
            }
        }
        
        mb = 0;
        mem(dp, 0);
        mem(dp1, 0);
        rep(i,1<<n) {
            rep(j,n)if(i>>j&1) dp1[i] |= a[j];
            dp1[i] = !(dp1[i] ^ ones[n-1]);
            if(!i) continue;
            int mask = 1<<mb ^ i;
            for(int smask = mask; ; smask = (mask & (smask - 1))) {
                dp[i] = max(dp[i], dp1[1<<mb ^ smask] + dp[mask ^ smask]);
                if(!smask) break;
            }
            if(i == ones[mb]) mb++;
        }
        cout << "Case " << casenum << ": " << dp[ones[n-1]] << '\n';
        
        cin >> n; casenum++;
    }
}
