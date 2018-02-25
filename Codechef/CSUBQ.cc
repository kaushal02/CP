/*
left mid right segment tree
_segment_tree

O((n+q)*log n)
*/

// g++ -std=c++11 -O2 -fmax-errors=1
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
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
 
#define rep(i,n) for(ll i=0, _n=(n); i<_n; i++)
#define rep1(i,n) for(ll i=1, _n=(n); i<=_n; i++)
#define cout(d) cout << fixed << setprecision(d)
#define err(x) cerr << #x << " = " << x << "\n"
 
#define cases int _t_; cin >> _t_; rep1(_t,_t_)
#define coutt cout << "Case " << _t << ": "
#define io ios_base::sync_with_stdio (false); cin.tie(NULL);
 
const dbl eps=1e-12, pi=acosl(-1);
const ll inf=1e16, mod=1e9+7;
const int N=5e5+10;
 
int n, L, R;
struct node {
    ll v;
    int n, a[4], fl;
    node() { fl=1;}
    ll val() { return (fl ? 0:v);}
    void set(int x) {
        v=0; n=1; fl=0;
        if(x<L) a[0]=a[1]=a[2]=a[3]=1;
        else if(x>R) a[0]=a[1]=a[2]=a[3]=0;
        else a[0]=a[3]=0, v=a[1]=a[2]=1;
    }
    void merge(node l, node r) {
        fl=0;
        if(l.fl and r.fl) fl=1;
        else if(l.fl) *this=r;
        else if(r.fl) *this=l;
        else {
            n = l.n + r.n;
            ll arX = l.a[2] - l.a[3];
            ll blY = r.a[1] - r.a[0];
            v = l.v + r.v + arX*r.a[0] + arX*blY + l.a[3]*blY;
            a[0] = l.a[0] + (l.a[0]==l.n ? r.a[0]:0);
            a[1] = l.a[1] + (l.a[1]==l.n ? r.a[1]:0);
            a[2] = r.a[2] + (r.a[2]==r.n ? l.a[2]:0);
            a[3] = r.a[3] + (r.a[3]==r.n ? l.a[3]:0);
        }
    }
} t[N<<1];
 
inline void build() {
    for(int i=n;i--;) t[n+i].set(0);
    for(int i=n;--i;) t[i].merge(t[i<<1], t[i<<1|1]);
}
inline void upd(int p, int v) {
    t[n+p].set(v);
    for(int i=n+p;i>>=1;) t[i].merge(t[i<<1], t[i<<1|1]);
}
inline node get(int l, int r) {
    node lt, rt;
    for(l+=n,r+=n+1; l<r; l>>=1,r>>=1) {
        if(l&1) lt.merge(lt, t[l++]);
        if(r&1) rt.merge(t[--r], rt);
    }
    lt.merge(lt,rt);
    return lt;
}
 
int main() {
    int q, t, x, y;
    scanf("%d%d%d%d", &n, &q, &L, &R);
    build(); while(q--) {
        scanf("%d%d%d", &t, &x, &y);
        if(t==1) upd(x-1, y);
        else printf("%lld\n", get(x-1,y-1).val());
    }
    return 0;
}
