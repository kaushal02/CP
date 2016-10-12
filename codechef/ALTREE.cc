/*
bitmask ; graph
O(n^2 * 2^n)
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,a) for(ll i=0;i<a;++i)
ll inf = 0x7f7f7f7f7f7f;
ll n, m, a[20][20][2];
ll dp[1<<20][20][2];
 
inline ll solve(ll mask, ll in, bool cl){
	if(dp[mask][in][cl] + 1) return dp[mask][in][cl];
    ll smask = 1<<in^mask;
    if(!smask) return 0;
    ll &res = dp[mask][in][cl];
    res = inf;
    rep(i,n) {
    	if(smask>>i&1) {
    		if(a[i][in][cl]) {
            	res = min(res, solve(smask, i, !cl) + a[i][in][cl]);
    		}
    	}
    }
    return res;
}
 
int main() {
    cin >> n >> m;
    ll u, v, co;
    char c;
    rep(i,n)rep(j,n)rep(k,2) a[i][j][k] = inf;
    rep(i,m) {
        cin >> u >> v >> co >> c;
        assert(c == 'B' or c == 'W');
		a[u-1][v-1][c == 'W'] = min(a[u-1][v-1][c == 'W'], co);
        a[v-1][u-1][c == 'W'] = min(a[u-1][v-1][c == 'W'], co);
    }
    rep(i,n)rep(j,n)rep(k,2) if(a[i][j][k] == inf) a[i][j][k] = 0;
 
    memset(dp, -1, sizeof dp);
    ll ans(inf);
    rep(i,n) {
        ans = min(ans, solve((1<<n)-1,i,0));
        ans = min(ans, solve((1<<n)-1,i,1));
    }
    if(ans == inf) ans = -1;
    rep(i,1<<n)rep(j,n)rep(k,2) assert(dp[i][j][k] >= -1 and dp[i][j][k] <= inf);
    cout << ans << '\n';
    return 0;
} 
