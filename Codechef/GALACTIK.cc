/*
_dsu

O((m + n) * α(n))
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

struct dsu {
    vi par, sz;
    dsu(int n): par(n), sz(n,1) { rep(i,n) par[i] = i;}
    int root(int a) { return a == par[a] ? a : par[a] = root(par[a]);}
    void merge(int a, int b) {
        a = root(a);
        b = root(b);
        if(a == b) return;
        if(sz[a] < sz[b]) swap(a,b);
        
        sz[a] += sz[b];
        par[b] = a;
    }
};
template <typename T = int>
inline void in(T&p) {
    p=0;register bool negative=false; register char ch=0;
    while(ch<0x30 or ch>0x39) {if(ch=='-') negative=true; ch=getchar();}
    while(ch>=0x30 and ch<=0x39) {p=(p<<1)+(p<<3)+(ch&15); ch=getchar();}
    if(negative) p=-p;}

int n, a[N], b[N];
void MAIN() {
    int m, x, y;
    in(n), in(m);
    dsu d(n);
    rep(i,m) {
        in(x), in(y);
        d.merge(x-1,y-1);
    }
    rep(i,n) in(a[i]);
    
    rep(i,n) b[i] = mod;
    rep(i,n) if(a[i] >= 0) {
        b[d.root(i)] = min(b[d.root(i)], a[i]);
    }
    
    ll sum(0), mi(mod), cnt(0);
    rep(i,n) {
        if(d.root(i) == i) {
            if(b[i] < mod) {
                sum += b[i];
                mi = min(mi, (ll)b[i]);
            }
            else {
                mi = -1;
            }
            cnt++;
        }
    }
    assert(cnt > 0);
    
    if(cnt == 1) cout << 0;
    else if(mi < 0) cout << -1;
    else cout << sum + mi * (cnt - 2);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    
    clock_t start = clock();
    srand(time(NULL));
    MAIN();
    clock_t end = clock();
    double time = (double) (end - start) / CLOCKS_PER_SEC;
#ifdef LOCAL
    fprintf(stderr, "Total running time: %.3lf s\n", time);
#endif
    return 0;
}
