/*
_MO
https://www.hackerrank.com/contests/sears-dots-arrows/challenges/connection-queries
Observation: every time the query is processed, it needs to be assured that add() are done before rem()
O(q*sqrt(n))
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

int n, K, a[N], segs, vis[N];
typedef pair<pii,int> node;

inline void add(int i) {
    assert(!vis[i]);
    vis[i] = 1;
    if(vis[i-1] and vis[i+1]) segs--;
    if(!vis[i-1] and !vis[i+1]) segs++;
}
inline void rem(int i) {
    assert(vis[i]);
    vis[i] = 0;
    if(vis[i-1] and vis[i+1]) segs++;
    if(!vis[i-1] and !vis[i+1]) segs--;
}

int main() {
    int q; cin >> n >> q; // Number of queries
    rep1(i,1,n) cin >> a[i];
    K = q / sqrt(n);
    vector<node> qu(q);
    rep(i,q) {
        int l, r; cin >> l >> r;
        qu[i] = {{l,r},i};
    }
    sort(all(qu), [](node l, node r) {
        if(l.X.X / K == r.X.X / K) return l.X.Y < r.X.Y;
        else return l.X.X < r.X.X;});
    
    vi ans(q, 0);
    int curl(1), curr(0), l, r;
    rep(i,q) {
        l = qu[i].X.X;
        r = qu[i].X.Y;
        while(curl > l)
            add(a[--curl]);
        while(curr < r)
            add(a[++curr]);
        while(curl < l)
            rem(a[curl++]);
        while(curr > r)
            rem(a[curr--]);
        
        ans[qu[i].Y] = segs;
    }
    rep(i,q) cout << ans[i] << '\n';
    return 0;
}
