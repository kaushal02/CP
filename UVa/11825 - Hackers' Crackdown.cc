/*
_bitmask
Traversing all submasks of a mask

O(n * 3 ^ n) per test case
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

int n, a[N], dp[1<<N];
inline int f(int mask) {
    if(dp[mask] + 1) return dp[mask];
    int &ans = dp[mask];
    ans = 0;
    
    int mb = 0; while(!(mask>>mb&1)) mb++;
    mask ^= 1<<mb;
    if(!mask) return ans = !a[mb];
    
    for(int smask = mask; ; smask = (mask & (smask - 1))) {
        int temp = a[mb];
        rep(i,n) if(smask>>i&1) temp &= a[i];
        ans = max(ans, !temp + f(mask ^ smask));
        
        if(!smask) break;
    }
    return ans;
}

int main() {
    int casenum = 0;
    
    cin >> n;
    casenum++;
    while(n) {
        mem(dp, -1);
        dp[0] = 0;
        rep(i,n) {
            a[i] = 1<<i;
            int m; cin >> m;
            while(m--) {
                int x; cin >> x;
                a[i] |= 1<<x;
            }
            a[i] ^= (1<<n) - 1;
        }
        cout << "Case " << casenum << ": " << f((1<<n)-1) << '\n';
        
        cin >> n;
        casenum++;
    }
}
