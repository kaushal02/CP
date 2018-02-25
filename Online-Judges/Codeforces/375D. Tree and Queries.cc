/*
_dfs _HLD

O(m*sqrt(n) + n*log^2(n))
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

vi t[N];
vector<pii> qt[N];
int c[N], ans[N], a[N];
map<int,int> cnt[N];
map<int,set<int>> id[N];
inline void merge(int vp, int vq) {
    int p = a[vp], q = a[vq];
    if(cnt[p].size() < cnt[q].size()) {
        swap(p, q);
        swap(vp, vq);
    }
    for(auto x: cnt[q]) {
        id[p][cnt[p][x.X]].erase(x.X);
        cnt[p][x.X] += x.Y;
        id[p][cnt[p][x.X]].insert(x.X);
    }
    a[q] = p;
    a[vq] = p;
}
inline void dfs(int v, int p) {
    for(int ch: t[v]) {
        if(ch != p) {
            dfs(ch, v);
        }
    }
    a[v] = v;
    cnt[a[v]][c[v]] = 1;
    id[a[v]][1].insert(c[v]);
    
    for(int ch: t[v]) {
        if(ch != p) {
            merge(ch, v);
        }
    }
    
    for(auto y: qt[v]) {
        for(auto &x: id[a[v]]) {
            if(x.X >= y.X) {
                ans[y.Y] += x.Y.size();
            }
        }
    }
}

template <typename T = int>
inline void in(T&p) {
    p=0;register bool negative=false; register char ch=0;
    while(ch<0x30 or ch>0x39) {if(ch=='-') negative=true; ch=getchar();}
    while(ch>=0x30 and ch<=0x39) {p=(p<<1)+(p<<3)+(ch&15); ch=getchar();}
    if(negative) p=-p;
}
int main() {
    int n, m; in(n), in(m);
    rep1(i,1,n) in(c[i]);
    rep(i,n-1) {
        int x, y; in(x), in(y);
        t[x].eb(y); t[y].eb(x);
    }
    rep(i,m) {
        int v, k; in(v), in(k);
        qt[v].eb(k,i);
    }
    dfs(1,1);
    rep(i,m) cout << ans[i] << '\n';
    return 0;
}
