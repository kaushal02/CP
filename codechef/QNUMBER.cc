/*
_factorization _factor _prime
Used the fact that n can have at most x = f(n) different prime factors where n <= p1 * p2 * .. * px, pi being i'th prime.

O(NlogN + sqrt(n) + q*f(n))
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
const ll mod = 1e9 + 7, inf = 1e16, N = 2e6 + 10;
const double eps = 1e-16;
 
int np(0), prime[N];
bool isprime[N];
void primes(int N) {
    memset(isprime, true, sizeof isprime);
    isprime[0] = isprime[1] = false;
	rep1(i,2,N-1) {
		if(isprime[i]) prime[++np] = i;
		rep1(j,1,np) {
			if(i * prime[j] > N) break;
			isprime[i * prime[j]] = false;
			if(i % prime[j] == 0) break;
		}
	}
}
 
void MAIN() {
	primes(N-1);
	ll n, q; cin >> n >> q;
    
	ll tot(1);
	vector<pll> div;
    for(int i = 1; prime[i] <= n / prime[i]; ++i) {
        if(n % prime[i] == 0) {
            int temp = 0;
            while(n % prime[i] == 0) {
                temp++, n /= prime[i];
            }
            div.eb(prime[i], temp);
            tot *= 1 + temp;
        }
	}
    if(n != 1) {
    	div.eb(n, 1);
    	tot *= 2;
    }

    ll type, x;
    while(q--) {
    	cin >> type >> x;
    	if(type == 1) {
    		ll ans(1);
    		for(auto pr: div) {
    			ll temp = 0;
    			while(x % pr.X == 0) {
    				temp++, x /= pr.X;
    			}
    			ans *= 1 + min(temp, pr.Y);
    		}
    		cout << ans << '\n';
    	}
    	else {
    		ll ans(1);
    		for(auto pr: div) {
    			ll temp = 0;
    			while(x % pr.X == 0) {
    				temp++, x /= pr.X;
    			}
    			ans *= max(0ll, pr.Y - temp + 1);
    		}
    		if(x != 1) ans = 0;
 
    		if(type == 2) cout << ans << '\n';
    		else if(type == 3) cout << tot - ans << '\n';
    		else assert(0);
    	}
    }
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
