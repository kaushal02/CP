/*
_BIT _tree_flatten _segment_tree
https://www.hackerrank.com/contests/ode-de-code-5-0-div1/challenges/sheldon-and-his-quirks

O(n+m+q*log(n+m))
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;

#define X first
#define Y second
#define sz(c) (int)c.size()
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
const int mod = 1e9 + 7, lim = 1e6 + 10;

vi ch[lim];
vector<pll> edge[lim];
map<int,int> id;
int par[lim], root[lim], wei[lim], hei[lim];

vi etree[lim];
int first[lim], last[lim];

typedef pll nod;
vector<nod> tree[lim];
inline nod combine(nod a, nod b) {
    return min(a, b);// Put the logic
}
inline void build(int id) {
    int n = sz(etree[id]);
    tree[id].reserve(n << 1);
    for(int i = n; i--; )
        tree[id][n + i] = {hei[etree[id][i]], etree[id][i]};
    for(int i = n; --i; )
        tree[id][i] = combine(tree[id][i << 1], tree[id][i << 1 | 1]);
}
inline nod query(int l, int r, int id) {
    if(l > r) swap(l, r);
    int n = sz(etree[id]);
    nod ansl(tree[id][n + l]), ansr(tree[id][n + r]);
    for(l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
        if(l & 1) ansl = combine(ansl, tree[id][l++]);
        if(r & 1) ansr = combine(tree[id][--r], ansr);
    }
    return combine(ansl, ansr);
}
inline void place(int v, int id) {
    first[v] = sz(etree[id]);
    for(int x: ch[v]) etree[id].eb(v), place(x, id);
    last[v] = sz(etree[id]);
    etree[id].eb(v);
}
template<class T>
struct bit {
    T *bt; int n;
    bit() {}
    bit(int n_):n(n_) { bt=(T*)calloc(n+1,sizeof(T));}
    void cons(int n_) { n = n_; bt=(T*)calloc(n+1,sizeof(T));}
    void reset() {memset(bt,0,sizeof(T)*(n+1));}
    void add(int u,T v=1) {u++;while(u<=n)bt[u]+=v,u+=u&-u;} // arr[u] += v
    T sum(int l,int r) {
        if(l > r) swap(l, r);
        T ans=0;r++;
        while(r)ans+=bt[r],r^=r&-r;
        while(l)ans-=bt[l],l^=l&-l;
        return ans;
    } // arr[l]+..+arr[r]
};
bit<ll> b[lim];
inline void add(int id) {
    b[id].cons(sz(etree[id]) + 1);
    rep(i,sz(etree[id])) {
        if(first[etree[id][i]] == i) b[id].add(i, wei[etree[id][i]]);
        if(last[etree[id][i]] == i) b[id].add(i+1, -wei[etree[id][i]]);
    }
}
inline void init(int v) {
    int treeid = id[v];
    place(v, treeid);
    build(treeid);
    add(treeid);
}
inline void rooting(int v, int anc) {
    vi temp;
    for(auto x: edge[v]) if(x.X != anc) {
        hei[x.X] = hei[v] + 1;
        root[x.X] = root[v];
        wei[x.X] = x.Y;
        par[x.X] = v;
        temp.eb(x.X);
        
        rooting(x.X, v);
    }
    ch[v] = temp;
}

int main() {
    int n, m; cin >> n >> m;
    rep(i,lim) par[i] = i, root[i] = i;
    
    ll u, v, w;
    rep(i,m) {
        cin >> u >> v >> w;
        edge[u].eb(v, w);
        edge[v].eb(u, w);
    }
    w = 0; rep1(i,1,n) if(par[i] == i) id[i] = ++w, rooting(i, i), init(i);
    
    int q, lca, treeid; cin >>  q;
    while(q--) {
        cin >> u >> v;
        if(root[u] != root[v]) { cout << -1 << '\n'; continue;}
        treeid = id[root[u]]; assert(treeid);
        cout << b[treeid].sum(0, first[u]) + b[treeid].sum(0, first[v])\
            - 2LL * b[treeid].sum(0, first[query(first[u], first[v], treeid).Y]) << '\n';
    }
    return 0;
}