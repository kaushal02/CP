/*
_sieve
Modified sieve to get primes in a range

O((n-m) * log(n))
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

template <typename T>
inline void out(T n) {
    register char d[20],i=0;
    if(n < 0){putchar('-'); n = -n;}
    do{ d[i++] = (n%10)|0x30 ; n = n/10;} while(n);
    while(i) putchar(d[--i]);
    putchar('\n');
}

bool a[N];
int main() {
    int q; cin >> q;
    while(q--) {
        ll m, n;
        cin >> m >> n;
        if(m == 1) m++;
        mem(a, true);
        for(ll i = 2; i * i <= n; i++) {
            ll k = max(m / i, 2LL);
            while(i * k < m) k++;
            while(i * k <= n) a[-m + i * k++] = false;
        }
        rep(i,n-m+1) if(a[i]) out(i + m);
        putchar('\n');
    }
    return 0;
}
