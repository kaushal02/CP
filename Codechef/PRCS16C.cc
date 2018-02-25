/*
_bitmask _graph _dij

O((m + n) * 2^p)
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
const int mod = 1e9 + 7, N = 1e5 + 10;
const ll inf = 1e12;
 
int n, m, p, k, s, e;
int id[10], cost[10], paid[10], vis[N], d[10][N];
vi g[N];
inline ll solve(int mask) {
    rep(i,p) paid[i] = (mask>>i&1);
    mem(vis, 0);
    
    int v;
    bool f = false;
    queue<int> q;
    q.emplace(s);
    while(!q.empty()) {
        v = q.front(), q.pop();
        if(vis[v]) continue; vis[v] = 1;
        if(v == e) { f = true; break;}
        
        rep(i,p) if(!paid[i] and d[i][v] <= k) continue;
        for(int x: g[v]) if(!vis[x]) q.emplace(x);
    }
    
    if(f) {
        ll ans(0);
        rep(i,p) if(paid[i]) ans += cost[i];
        return ans;
    }
    return inf;
}
 
inline void pre(int iD) {
    mem(d[iD], -1);
    
    int v, x;
    queue<pii> q;
    q.emplace(id[iD], 0);
    while(!q.empty()) {
        tie(v, x) = q.front(), q.pop();
        if(d[iD][v] + 1) continue;
        d[iD][v] = x;
        for(int ch: g[v]) if(d[iD][ch] == -1) q.emplace(ch, x + 1);
    }
}
 
int main() {
    cin >> n >> m >> p >> k;
    rep(i,p) cin >> id[i];
    rep(i,p) cin >> cost[i];
    rep(i,m) cin >> s >> e, g[s].eb(e), g[e].eb(s);
    cin >> s >> e;
    
    ll ans(inf);
    rep(i,p) pre(i);
    rep(i,1<<p) ans = min(ans, solve(i));
    cout << ans;
    return 0;
}
