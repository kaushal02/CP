/*
_dsu

Pre definition of dsu, and late initialization.
d[i] stores the graph ignoring all edges of color i, dt is the total graph
O(q*c)
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
const int N = 1e5 + 10;

template <typename T = int>
inline void in(T&p) {
    p=0;register bool negative=false; register char ch=0;
    while(ch<0x30 or ch>0x39) {if(ch=='-') negative=true; ch=getchar();}
    while(ch>=0x30 and ch<=0x39) {p=(p<<1)+(p<<3)+(ch&15); ch=getchar();}
    if(negative) p=-p;
}
template <typename T>
inline void out(T n) {
    register char d[20],i=0;
    if(n < 0){putchar('-'); n = -n;}
    do{ d[i++] = (n%10)|0x30 ; n = n/10;} while(n);
    while(i) putchar(d[--i]);
    putchar('\n');
}

struct dsu {
    vi par, sz;
    dsu() {};
    dsu(int n): par(n), sz(n) { rep(i,n) par[i] = i, sz[i] = 1;}
    void cons(int n) { rep(i,n) par.eb(i), sz.eb(1);}
    int root(int a) { return a == par[a] ? a : par[a] = root(par[a]);}
    void merge(int a, int b) {
        a = root(a);
        b = root(b);
        if(a == b) return;
        if(sz[a] < sz[b]) swap(a,b);
        
        sz[a] += sz[b];
        par[b] = a;
    }
    bool dif(int a, int b) { return root(a) != root(b);}
};

int main() {
    int n, m, c; in(n), in(m), in(c);
    
    dsu d[c], dt(n); rep(i,c) d[i].cons(n);
    rep(i,m) {
        int u, v, w; in(u), in(v), in(w);
        rep(j,c) if(j+1 != w) d[j].merge(u-1,v-1);
        dt.merge(u-1,v-1);
    }
    int q; cin >> q;
    while(q--) {
        int u, v; in(u), in(v);
        int ans(0); rep(i,c) if(d[i].dif(u-1,v-1) and !dt.dif(u-1,v-1)) ans++;
        out(ans);
    }
    return 0;
}
