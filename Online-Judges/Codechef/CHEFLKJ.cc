/*
_BIT _sqrt_decomposition

O((q + n) * sqrt(n))
*/
#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second
#define rep(i,n) for(int i = 0, _n = (n); i < _n; i++)
#define rep1(i,a,b) for(int i = a, _b = (b); i <= _b; i++)
const int mod = 1e9 + 7, N = 1e5 + 6, k = 1e3;
 
template<class T>
struct bit {
    T *bt; int n;
    bit() {}
    bit(int n_):n(n_) { bt=(T*)calloc(n+1,sizeof(T));}
    void cons(int n_) { n = n_; bt=(T*)calloc(n+1,sizeof(T));}
    void reset() {memset(bt,0,sizeof(T)*(n+1));}
    void add(int u,T v=1) {u++;while(u<=n)bt[u]+=v,u+=u&-u;} // arr[u] += v
    T sum(int l,int r) {
        T ans=0;r++;
        while(r)ans+=bt[r],r^=r&-r;
        while(l)ans-=bt[l],l^=l&-l;
        return ans;
    } // arr[l]+..+arr[r]
};
 
int a[N];
unordered_map<int,int> c, id;
bit<int> b[200];
 
int main() {
    int n, q; cin >> n >> q;
    rep(i,n) cin >> a[i], c[a[i]]++;
    rep(i,200) b[i].cons(n);
    
    int p(0);
    for(auto x: c) if(x.Y >= k) {
        id[x.X] = p;
        rep(i,n) if(a[i] == x.X) b[p].add(i);
        p++;
    }
    
    int type, x, y, l, r, f, req;
    rep(i,q) {
        cin >> type;
        if(type == 1) {
            cin >> x >> y; x--;
            
            if(id.find(a[x]) != id.end()) b[id[a[x]]].add(x,-1);
            c[a[x]]--;
            a[x] = y;
            c[a[x]]++;
            if(id.find(a[x]) != id.end()) b[id[a[x]]].add(x);
            
            if(id.find(y) == id.end() and c[y] >= k) {
                id[y] = p;
                rep(j,n) if(a[j] == y) b[p].add(j);
                p++;
            }
        }
        else {
            cin >> l >> r; l--, r--;
            if(r - l + 1 < 2 * k) {
                unordered_map<int,int> my;
                rep1(j,l,r) my[a[j]]++;
                
                f = 0; req = (r-l+1)/2;
                for(auto x: my) if(x.Y > req) f = 1;
            }
            else {
                f = 0; req = (r-l+1)/2;
                rep(j,p) if(b[j].sum(l,r) > req) f = 1;
            }
            if(f) cout << "Yes\n";
            else cout << "No\n";
        }
    }
    return 0;
} 

/**********************************************************************************************************/

/*
_segment_tree

O((n + q*log(n)) * log(n))
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
#define rep(i,n) for(int i = 0, _n = (n); i < _n; i++)
#define rep1(i,a,b) for(int i = a, _b = (b); i <= _b; i++)
#define rep2(i,b,a) for(int i = b, _a = (a); i >= _a; i--)
#define mem(a,val) memset(a, (val), sizeof a)
#define mp make_pair
#define mt make_tuple // remember tie & ignore
#define eb emplace_back
#define all(c) (c).begin(), (c).end()
#define uni(c) c.resize(distance(c.begin(), unique(all(c))))
#define tr(c,it) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)
#define cases int __t; cin >> __t; rep1(_t,1,__t)
#define case(ans) "Case #" << _t << ": " << ans << "\n"
#define cout(d) cout << fixed << setprecision(d)
#define err(x) cerr << #x << " = " << x << '\n'
const int mod = 1e9 + 7;
 
struct nod {
    int dom, len;
    unordered_map<int,int> occ;
    nod() {}
    nod(int x): dom(x), len(1) { occ.clear(), occ[x]++;}
};
const int N = 2e5 + 5;
int n, arr[N];
nod tree[N << 1];
inline nod combine(nod a, nod b) {
    // put the logic
    nod ans;
    for(auto x: a.occ) ans.occ[x.X] += x.Y;
    for(auto x: b.occ) ans.occ[x.X] += x.Y;
    ans.len = a.len + b.len;
    if(ans.occ[a.dom] > ans.len/2) ans.dom = a.dom;
    else if(ans.occ[b.dom] > ans.len/2) ans.dom = b.dom;
    else ans.dom = -1;
    return ans;
}
inline void build() {
    for(int i = n; i--; )
        tree[n + i] = nod(arr[i]);
    for(int i = n; --i; )
        tree[i] = combine(tree[i << 1], tree[i << 1 | 1]); 
}
inline void update(int pos, int value) {
    tree[n + pos] = nod(value); // tree[n + pos] = combine(tree[n + pos], nod(value));
    for(int i = n + pos; i >>= 1; ) {
        tree[i].occ[arr[pos]]--;
        tree[i].occ[value]++;
        if(tree[i].occ[tree[i].dom] > tree[i].len/2) continue;
        if(tree[i].occ[value] > tree[i].len/2) tree[i].dom = value;
        else tree[i].dom = -1;
    }
}
vi cand;
inline void query(int l, int r) {
    for(l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
        if(l & 1) cand.eb(l++);
        if(r & 1) cand.eb(--r);
    }
}
int main() {
    int q; cin >> n >> q;
    rep(i,n) cin >> arr[i];
    build();
    
    int type, x, y, l, r, req, f, cnt, val;
    rep(i,q) {
        cin >> type;
        if(type == 1) {
            cin >> x >> y; x--;
            update(x, y);
            arr[x] = y;
        }
        else {
            cin >> l >> r; l--, r--;
            cand.clear();
            query(l,r);
            req = (r - l + 1) / 2;
            f = 0;
            for(int x: cand) {
                cnt = 0;
                val = tree[x].dom;
                for(int y: cand) cnt += tree[y].occ[val];
                if(cnt > req) f = 1;
            }
            if(f) cout << "Yes\n";
            else cout << "No\n";
        }
    }
    return 0;
}
