// Time erodes gratitude more quickly than it does beauty!
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;

#define X first
#define Y second
#define rep(i,n) for(int i=0, _n=(n); i<_n; i++)
#define rep1(i,a,b) for(int i=a,_b=(b); i<=_b; i++)
#define rep2(i,b,a) for(int i=b,_a=(a); i>=_a; i--)
#define mem(a,val) memset(a, (val), sizeof a)
#define mp make_pair
#define mt make_tuple
#define eb emplace_back
#define all(c) (c).begin(), (c).end()
#define uni(c) c.resize(distance(c.begin(), unique(all(c))))
#define fix(c,sz_val...) c.clear();c.resize(sz_val);
#define tr(c,it) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)
#define cases int t;cin>>t;rep1(_t,1,t)
#define case(ans) "Case #"<<_t<<": "<<ans<<"\n"
#define cout(d) cout<<fixed<<setprecision(d)
#define IO(i, o) ifstream cin(i);ofstream fout(o)
#define io ios_base::sync_with_stdio(false);cin.tie(NULL);
#define err(x) cerr << #x << " = " << x << '\n'
const int mod = 1e9 + 7;
int n, x, par[1010], vis[1010], ans, ans1;
vector<vi> g;

inline void cycle(int i) {
    int temp = 0, var = i;
    while(temp < n) {
        temp++;
        var = par[var];
        if(var == i) {
            ans = max(ans, temp);
            return;
        }
    }
}

inline void special(int u, int v) {
    int tempu = 1, tempv = 1;
    int ver, hei;
    
    queue<pii> q;
    q.emplace(u, 1);
    while(!q.empty()) {
        tie(ver, hei) = q.front();
        q.pop();
        
        if(ver == v) continue;
        vis[ver] = 1;
        if(g[ver].empty()) tempu = max(tempu, hei);
        
        for(auto child: g[ver])
            q.emplace(child, hei + 1);
    }
    q.emplace(v, 1);
    while(!q.empty()) {
        tie(ver, hei) = q.front();
        q.pop();
        
        if(ver == u) continue;
        vis[ver] = 1;
        if(g[ver].empty()) tempv = max(tempv, hei);
        
        for(auto child: g[ver])
            q.emplace(child, hei + 1);
    }
    
    ans1 += (tempu + tempv);
}

int main()
{
    IO("C-small-attempt3.in", "C-small-attempt3.out");
    cases {
        ans = 0;
        ans1 = 0;
        cin >> n;
        fix(g, n);
        mem(par, -1);
        rep(i,n) {
            cin >> x; x--;
            par[i] = x;
            g[x].eb(i);
        }
        
        rep(i,n) cycle(i);
        
        mem(vis, 0);
        rep(i,n) if(!vis[i] and par[par[i]] == i) special(i, par[i]);
        
        ans = max(ans, ans1);
        assert(ans > 1);
        fout << case(ans);
    }
    return 0;
}