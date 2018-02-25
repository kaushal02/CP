/*
_dp _ncr
Involves calculating #ways to put exactly k types of balls in n numbered slots. n is fixed and k varies over [1,n]

O(N^2 + K)
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
#define sz(c) (ll)c.size()
#define rep(i,n) for(ll i = 0, _n = (n); i < _n; i++)
#define rep1(i,a,b) for(ll i = a, _b = (b); i <= _b; i++)
#define rep2(i,b,a) for(ll i = b, _a = (a); i >= _a; i--)
#define mem(a,val) memset(a, (val), sizeof a)
#define mp make_pair
#define eb emplace_back // tie, ignore, get<i>(a)
#define all(c) (c).begin(), (c).end()
#define uni(c) c.resize(distance(c.begin(), unique(all(c))))
#define case(ans) "Case #" << _t << ": " << ans << "\n"
#define cout(d) cout << fixed << setprecision(d)
#define err(x) cerr << #x << " = " << x << '\n'
const ll mod = 1e9 + 7, inf = 1e16;
const ll K = 1e6 + 10, N = 1e3 + 10;
const double eps = 1e-16;
 
ll fac[K], inv[K];
inline ll pwr(ll a, ll n, ll m = mod) {
    ll ans(1);
    while(n) {
        if(n & 1) ans = ans * a % m;
        n >>= 1;
        a = a * a % m;
    }
    return ans;
}
inline void init_ncr(int N) {
    fac[0] = 1;
    rep1(i,1,N) fac[i] = fac[i-1] * i % mod;
    inv[N] = pwr(fac[N], mod-2);
    rep2(i,N,1) inv[i-1] = inv[i] * i % mod;
}
inline ll ncr(ll n, ll r) {
    if(n < 0 or r < 0 or n < r) return 0;
    return fac[n] * (inv[r] * inv[n-r] % mod) % mod;
}
 
ll n, k;
ll a[N][N];
inline ll f(ll i) {
	if(i > n) return 0;
	ll x = a[i][n];
	return x * x % mod;
}
inline ll g(ll i) {
	ll x = ncr(k-1, i);
	return x * x % mod;
}
inline ll h(ll i) {
	ll x = ncr(k-2, i);
	return x * x % mod;
}
 
void MAIN() {
	cin >> n >> k;
	init_ncr(K-1);
	a[0][0] = 1;
	rep1(i,1,n)rep1(j,1,n) {
		a[i][j] = (a[i][j-1] + a[i-1][j-1]) * i % mod;
	}
	
	ll ans1(0), ans2(0);
	rep(i,k) {
		ans1 += g(i) * f(i) % mod;
		ans1 += g(i) * f(i+1) % mod;
	}
	ans1 %= mod;
	ans1 = ans1 * k % mod;
	rep(i,k-1) {
		ans2 += h(i) * f(i) % mod;
		ans2 += 2LL * h(i) * f(i+1) % mod;
		ans2 += h(i) * f(i+2) % mod;
	}
	ans2 %= mod;
	ans2 = ans2 * k % mod;
	ans2 = ans2 * (k - 1) % mod;
	
	cout << (ans1 + ans2) % mod << '\n';
}
 
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    
    clock_t start = clock();
    MAIN();
    clock_t end = clock();
    double time = (double) (end - start) / CLOCKS_PER_SEC;
#ifdef LOCAL
    fprintf(stderr, "Total running time: %.3lf s\n", time);
#endif
    return 0;
}
