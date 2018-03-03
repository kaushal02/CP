/*
_segtree

O(100*n*logn)
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

int n, a[N];
vi t[N<<1];
inline vi merge(vi a, vi b) {
    int n=a.size(), m=b.size();
    int i=0, j=0, k=0;
    vi c(n+m);
    while(i<n and j<m) {
        if(a[i]<b[j]) c[k++]=a[i++];
        else c[k++]=b[j++];
    }
    while(i<n) c[k++]=a[i++];
    while(j<m) c[k++]=b[j++];

    n+=m; i=n-2;
    while(i-->0) {
        if(c[i]+c[i+1]>c[i+2]) break;
    }
    if(i<0) return c;
    return vi(c.begin()+i, c.end());
}
inline void build() {
    for(int i=n; i--; ) t[n+i]={a[i]};
    for(int i=n; --i; ) t[i]=merge(t[i<<1], t[i<<1|1]);
}
inline void upd(int p, int v) {
    t[n+p]={v};
    for(int i=n+p; i>>=1; ) t[i]=merge(t[i<<1], t[i<<1|1]);
}
inline int get(int l, int r) {
    vi lt, rt;
    for(l+=n,r+=n+1; l<r; l>>=1,r>>=1) {
        if(l&1) lt=merge(lt, t[l++]);
        if(r&1) rt=merge(t[--r], rt);
    }
    lt=merge(lt,rt);
    if(lt.size()<3 or lt[0]+lt[1]<=lt[2]) return 0;
    return lt[0]+lt[1]+lt[2];
}

#undef int
int main() {
#define int long long

    cin >> n;
    int q; cin >> q;
    rep(i,n) cin >> a[i];
    build(); while(q--) {
        int ty, x, y; cin >> ty >> x >> y;
        if(ty==1) upd(x-1, y);
        else if(ty==2) cout << get(x-1, y-1) << '\n';
        else assert(0);
    }

    return 0;
}
