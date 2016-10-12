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
