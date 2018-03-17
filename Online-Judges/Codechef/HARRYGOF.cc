/*
_segtree _offline

O((n+q)logn + qlogq)
*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long double dbl;
typedef pair<int,int> pii;
typedef vector<int> vi;
 
#define X first
#define Y second
#define mp make_pair
#define pb push_back
#define all(c) begin(c), end(c)
#define mem(c,v) memset(c, v, sizeof c)
#define uni(c) c.resize(distance(c.begin(), unique(all(c))))
 
#define rep(i,n) for(int i=0, _n=(n); i<_n; i++)
#define rep1(i,n) for(int i=1, _n=(n); i<=_n; i++)
#define cout(d) cout << fixed << setprecision(d)
#define err(x) cerr << #x << " = " << x << "\n"
 
#define cases int _t_; cin >> _t_; rep1(_t,_t_)
#define coutt cout << "Case " << _t << ": "
#define io ios_base::sync_with_stdio(false); cin.tie(NULL);
 
const dbl eps=1e-12, pi=acosl(-1);
const int inf=1e16, mod=1e9+7, N=2e6+10;
 
pii b[N];
int n, a[N];
int q, k, ans[N];
pair<pii,pii> qu[N];
struct node {
    int t, l, r, p;
    node(): t(0), l(0), r(0), p(1) {}
    node(int x): t(x), l(x), r(x), p(x) {}
} t[N<<1];
inline node merge(node a, node b) {
    node ret;
    ret.t = (a.t + b.t + a.r*b.l)%mod;
    ret.l = (a.l + a.p*b.l)%mod;
    ret.r = (a.r*b.p + b.r)%mod;
    ret.p = a.p*b.p%mod;
    return ret;
}
inline void build() {
    for(int i=n; i--; ) t[n+i]=node(a[i]);
    for(int i=n; --i; ) t[i]=merge(t[i<<1], t[i<<1|1]);
}
inline void upd(int p) {
    t[n+p]=node(k);
    for(int i=n+p; i>>=1; ) t[i]=merge(t[i<<1], t[i<<1|1]);
}
inline int get(int l, int r) {
    node lt, rt; // identity
    for(l+=n,r+=n+1; l<r; l>>=1,r>>=1) {
        if(l&1) lt=merge(lt, t[l++]);
        if(r&1) rt=merge(t[--r], rt);
    }
    return merge(lt,rt).t;
}
 
#undef int
int main() {
#define int long long
 
    cin >> n >> q >> k;
    rep(i,n) cin >> a[i], b[i] = {a[i],i};
    build(); rep(i,q) {
        int l, r, p;
        cin >> l >> r >> p;
        qu[i] = {{l,r},{p,i}};
    }
    sort(qu, qu+q, [](pair<pii,pii> l, pair<pii,pii> r) {
        return l.Y.X < r.Y.X;
    });
    sort(b, b+n, [](pii l, pii r) {
        return l.X < r.X;
    });
 
    int j=0; rep(i,q) {
        while(j<n and b[j].X<qu[i].Y.X) upd(b[j++].Y);
        ans[qu[i].Y.Y] = get(qu[i].X.X-1, qu[i].X.Y-1);
    }
    rep(i,q) cout << ans[i] << '\n';
    return 0;
} 