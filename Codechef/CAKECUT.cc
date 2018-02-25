/*
_bitset _dp
O(n^2)
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
#define rep(i,n) for(int i = 0, _n = (n); i < _n; i++)
#define rep1(i,a,b) for(int i = a, _b = (b); i <= _b; i++)
#define rep2(i,b,a) for(int i = b, _a = (a); i >= _a; i--)
#define mem(a,val) memset(a, (val), sizeof a)
#define mp make_pair
#define mt make_tuple // remember tie & ignore
#define eb emplace_back
#define all(c) (c).begin(), (c).end()
#define uni(c) c.resize(distance(c.begin(), unique(all(c))))
#define tr(c,it) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)
#define cases int __t; cin >> __t; rep1(_t,1,__t)
#define case(ans) "Case #" << _t << ": " << ans << "\n"
#define cout(d) cout << fixed << setprecision(d)
#define err(x) cerr << #x << " = " << x << '\n'
const int mod = 1e9 + 7, N = 1515;
bitset<N> b[N], c;
int sum[N];
 
int main() {
    rep(i,N) if(i) sum[i] = sum[i-1] + i;
    
    int n, m;
    cin >> n >> m;
    rep(i,n) {
        cin >> b[i];
        rep(j,m) if(j) b[i][j] = b[i][j] ^ b[i][j-1];
    }
    
    ll ans(0);
    rep(i,n) {
        c.reset();
        rep2(j,i,0) {
            c ^= b[j];
            ans += sum[c.count()-1] + sum[m-c.count()];
        }
    }
    cout << ans;
    return 0;
}
