/*
_cycle
Elegant linear solution to minimize the total cost of rearrangement
Contest codex 16.0 by NIT, Rourkela
https://www.hackerrank.com/contests/codex-16-0/challenges/final-lineup
O(n)
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
const int N = 1e6 + 10;
template <typename T = int>
inline void in(T&p) {
    p=0;register bool negative=false; register char ch=0;
    while(ch<0x30 or ch>0x39) {if(ch=='-') negative=true; ch=getchar();}
    while(ch>=0x30 and ch<=0x39) {p=(p<<1)+(p<<3)+(ch&15); ch=getchar();}
    if(negative) p=-p;
}

ll n, u[N], x[N], y[N], px[N], py[N], vis[N];
int main() {
    in(n);
    rep1(i,1,n) in(u[i]);
    rep1(i,1,n) in(x[i]), px[x[i]] = i;
    rep1(i,1,n) in(y[i]), py[y[i]] = i;
    
    ll mini(mod);
    rep1(i,1,n) mini = min(mini, u[i]);
    
    ll ans(0);
    rep1(i,1,n) if(!vis[i]) {
        ll mi(mod), sum(0), cnt(0), j(i);
        while(!vis[j]) {
            vis[j] = 1;
            
            mi = min(mi, u[j]);
            sum += u[j];
            cnt++;
            
            j = x[py[j]];
        }
        assert(j == i);
        ans += sum + min((cnt - 2) * mi, (cnt + 1) * mini + mi);
    }
    cout << ans << '\n';
    return 0;
}
