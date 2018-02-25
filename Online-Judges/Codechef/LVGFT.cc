/*
multiple _segment_tree
_tree_flatten
_ancestor

O(n + m*log n) per testcase
*/
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
const int N=2e5+10;
 
int n, par[N], isBank[N], st[N], nd[N], h[N], T, a[N];
 
#define node pii
node t1[N<<1], t2[N<<1];
inline node merge(node a, node b) {
    vi v={a.X, a.Y, b.X, b.Y};
    sort(all(v)); uni(v);
    int x=v.back(); v.pop_back();
    if(v.empty()) return {x,0};
    else return {x,v.back()};
}
inline void build(node t[]) {
    for(int i=n; i--; ) t[n+i]={a[i],0};
    for(int i=n; --i; ) t[i]=merge(t[i<<1], t[i<<1|1]);
}
inline void upd(int p, node v, node t[]) {
    t[n+p]=v; // t[n+p]=merge(t[n+p],node(v));
    for(int i=n+p; i>>=1; ) t[i]=merge(t[i<<1], t[i<<1|1]);
}
inline node get(int l, int r, node t[]) {
    node lt={0,0}, rt={0,0}; // identity
    for(l+=n,r+=n+1; l<r; l>>=1,r>>=1) {
        if(l&1) lt=merge(lt, t[l++]);
        if(r&1) rt=merge(t[--r], rt);
    }
    return merge(lt,rt);
}
 
int anc[N<<1];
inline void merge1(int &a, int b) {
    if(h[a]<h[b]) a=b;
}
inline void upd1(int l, int r, int v) {
    for(l+=n, r+=n+1; l<r; l>>=1, r>>=1) {
        if(l&1) merge1(anc[l++], v);
        if(r&1) merge1(anc[--r], v);
    }
}
inline int get1(int p) {
    int res=0;
    for(p+=n; p; p>>=1) merge1(res, anc[p]);
    return res;
}
 
vi tr[N];
void dfs(int v) {
    a[T]=v;
    st[v]=T++;
    vi vec;
    for(int ch: tr[v]) if(ch!=par[v]) {
        vec.pb(ch);
        par[ch] = v;
        h[ch] = h[v] + 1;
        dfs(ch);
    }
    nd[v]=T;
    tr[v]=vec;
}
 
inline int ancestor(int v) {
    int p=get1(st[v]);
    int l=0, r=(int)tr[p].size()-1, m;
    while(l<r) {
        m=(l+r+1)/2;
        if(st[tr[p][m]] < st[v]) l=m;
        else if(st[tr[p][m]] > st[v]) r=m-1;
        else return tr[p][m];
    }
    if(l>r) return 1;
    return tr[p][l];
}
 
void solve() {
    T=0; h[1]=1;
    int x, y, z, m;
    scanf("%d%d", &n, &m);
    rep1(i,n) tr[i].clear(), isBank[i]=0;
    rep(i,(n<<1|1)) t1[i]=t2[i]={0,anc[i]=0};
    rep(i,n-1) {
        scanf("%d%d", &x, &y);
        tr[x].pb(y);
        tr[y].pb(x);
    }
    dfs(1); build(t1);
 
    pii p, q;
    while(m--) {
        cin >> x >> y;
        if(x==1) {
            if(!isBank[y]) {
                isBank[y]=1;
                upd1(st[y], nd[y]-1, y);
                upd(st[y], get(st[y], nd[y]-1, t1), t2);
            }
        }
        if(x==2) {
            if(isBank[y]) printf("%d\n", n-1);
            else {
                y=ancestor(y);
                z=merge(get(st[y], nd[y]-1, t2), merge(get(0, st[y]-1, t1), get(nd[y], n-1, t1))).Y;
                if(!z) z--; printf("%d\n", z);
            }
        }
    }
}
 
// MAIN
int main() {
    cases solve();
}
