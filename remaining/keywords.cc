//1
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

#define LOCAL 1
int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    |
    return 0;
}
/**............................................................................**/

//2
// Time erodes gratitude more quickly than it does beauty!
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;

#define X first
#define Y second
#define rep(i,n) for(ll i=0; i<(n); i=add(i,1))
#define rep1(i,a,b) for(ll i=a; i<=(b); i=add(i,1))
#define rep2(i,b,a) for(ll i=b; i>=(a); i=sub(i,1))
#define mem(a,val) memset(a, (val), sizeof a)
#define mp make_pair
#define mt make_tuple
#define eb emplace_back
#define all(c) (c).begin(), (c).end()
#define uni(c) c.resize(distance(c.begin(), unique(all(c))))
#define fix(c,sz_val...) c.clear();c.resize(sz_val);
#define tr(c,it) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)
#define cases int t;cin>>t;rep1(_t,1,t)
#define case(ans) "Case #"<<_t<<": "<<ans<<"\n"
#define cout(d) cout<<fixed<<setprecision(d)
#define IO(input_file_name) ifstream cin(input_file_name);ofstream fout("output.txt")
#define io ios_base::sync_with_stdio(false);cin.tie(NULL);
#define err(x) cerr << #x << " = " << x << '\n'
const ll mod = 1000000007;
inline ll add(ll x, ll y) {
    if(!y) return x;
    return add(x ^ y, (x & y) << 1);
}
inline ll sub(ll x, ll y) {
    if(!y) return x;
    return sub(x ^ y, (~x & y) << 1);
}
inline ll mul(ll x, ll y, ll m = 2e18) {
    ll ans(0);
    while(y) {
        if(y & 1) ans = add(ans, x) % m;
        y >>= 1;
        x = add(x, x) % m;
    }
    return ans;
}
inline ll div(ll x, ll y) {
    ll ans(0);
    ll m(1), d(y);
    while(d <= x) {
        ans = add(ans, mul(x % d, m));
        m = d;
        d = mul(d, y);
    }
    return ans;
}
inline ll pwr(ll x, ll y, ll m = mod) {
    ll ans(1);
    while(y) {
        if(y & 1) ans = mul(ans, x, m);
        y >>= 1;
        x = mul(x, x, m);
    }
    return ans;
}

int main() {
    |
    return 0;
}
/**............................................................................**/

//c
#include <stdio.h>

int main() {
    |
    return 0;
}
/**............................................................................**/

//cpp
#include <bits/stdc++.h>
#define rep(i,n) for(int i=0; i<(n); i++)
using namespace std;

int main() {
    |
    return 0;
}
/**............................................................................**/

//in
template <typename T = int>
inline void in(T&p) {
    p=0;register bool negative=false; register char ch=0;
    while(ch<0x30 or ch>0x39) {if(ch=='-') negative=true; ch=getchar();}
    while(ch>=0x30 and ch<=0x39) {p=(p<<1)+(p<<3)+(ch&15); ch=getchar();}
    if(negative) p=-p;
}
|
/**............................................................................**/

//out
template <typename T>
inline void out(T n) {
    register char d[20],i=0;
    if(n < 0){putchar('-'); n = -n;}
    do{ d[i++] = (n%10)|0x30 ; n = n/10;} while(n);
    while(i) putchar(d[--i]);
    putchar('\n');
}
|
/**............................................................................**/

//rand
unsigned int x = 0x12A01, y = 0x341B1, z = 0xA324, w = 0x4320B;
unsigned int myrand() {
    // This RNG generates float in the range [0, 1], with a precision of 10 digits
    // It is nearly 6% faster than regular std::rand() function
    // Visit "https://en.wikipedia.org/wiki/Xorshift" for more details
    unsigned int t = x;
    t ^= t << 11;
    t ^= t >> 8;
    tie(x, y, z) = tie(y, z, w);
    w ^= w >> 19;
    w ^= t;
    return w;
}
|