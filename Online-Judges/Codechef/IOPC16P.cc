/*
_subarray _segment_tree _offline
 
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
const int inf=1e14, mod=1e9+7, N=2e5+10;
 
inline int safeAdd(int a, int b) { return (a==-inf or b==-inf ? -inf:a+b);}
 
pii b[N];
pair<pii,pii> qu[N];
int n, q, a[N], ans[N];
struct node {
    int v, l, r, t;
    node() {v=l=r=t=-inf;}
    node(int n) {v=l=r=t=n;}
} t[N<<1];
inline node merge(node a, node b) {
    node ret;
    ret.v = max({a.v, b.v, safeAdd(a.r,b.l)});
    ret.l = max(a.l, safeAdd(a.t,b.l));
    ret.r = max(b.r, safeAdd(a.r,b.t));
    ret.t = safeAdd(a.t,b.t);
    return ret;
}
inline void upd(int p) {
    t[n+p]=node(a[p]);
    for(int i=n+p; i>>=1; ) t[i]=merge(t[i<<1], t[i<<1|1]);
}
inline int get(int l, int r) {
    node lt, rt; // identity
    for(l+=n,r+=n+1; l<r; l>>=1,r>>=1) {
        if(l&1) lt=merge(lt, t[l++]);
        if(r&1) rt=merge(t[--r], rt);
    }
    return merge(lt,rt).v;
}
 
#undef int
int main() {
#define int long long
 
    cin >> n >> q;
    rep(i,n) cin >> a[i], b[i]={a[i],i};
    rep(i,q) {
        int l, r, x; cin >> l >> r >> x;
        qu[i] = {{l-1,r-1}, {x,i}};
    }
    sort(qu, qu+q, [](pair<pii,pii> l, pair<pii,pii> r) {
        return l.Y.X < r.Y.X;
    });
    sort(b, b+n);
 
    int j=0; rep(i,q) {
        while(j<n and b[j].X<=qu[i].Y.X) upd(b[j++].Y);
        ans[qu[i].Y.Y] = get(qu[i].X.X, qu[i].X.Y);
    }
    rep(i,q) {
        if(ans[i]>-inf) cout << ans[i];
        else cout << "xx";
        cout << '\n';
    }
    return 0;
}