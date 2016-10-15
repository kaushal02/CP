/*
_graph
potential candidate for _01bfs

https://a2oj.com/p?ID=28
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
#define eb push_back // tie, ignore, get<i>(a)
#define mem(a,val) memset(a, (val), sizeof a)
#define uni(c) c.resize(distance(c.begin(), unique(all(c))))

#define rep(i,n) for(int i = 0, _n = (n); i < _n; i++)
#define rep1(i,a,b) for(ll i = a, _b = (b); i <= _b; i++)
#define rep2(i,b,a) for(ll i = b, _a = (a); i >= _a; i--)

#define cout(d) cout << fixed << setprecision(d)
#define err(x) cerr << #x << " = " << x << '\n'

const ll inf = 1e16, mod = 1e9 + 7;
const double eps = 1e-16;
const int N = 26*26*26;

inline int h(string &s) {
    return 676 * (s[0] - 'A') + 26 * (s[1] - 'A') + (s[2] - 'A');
}

vi t[N][2];
int in, fi, vis[N], dp[N];
inline void bfs() {
    int v, dis;
    queue<pii> q;
    q.push(mp(fi,0));
    while(!q.empty()) {
		v = q.front().X;
		dis = q.front().Y;
		q.pop();
        if(vis[v] < dis) continue;
        vis[v] = dis;
        rep(k,2) {
            rep(i,t[v][k].size()) {
                int ch = t[v][k][i];
                if(vis[ch] > dis + 1) {
                    q.push(mp(ch, dis + 1));
                    vis[ch] = dis + 1;
                }
            }
        }
    }
}

int dfs(int v) {
    if(dp[v] + 1) return dp[v];
    
    int &ans = dp[v];
    ans = 0x1010101;
    rep(k,2) {
        rep(i,t[v][k].size()) {
            int ch = t[v][k][i];
            if(vis[ch] == vis[v] - 1)
				ans = min(ans, k + dfs(ch));
        }
    }
    return ans;
}

int main() {
    string s1, s2;
    int q; cin >> q;
    
    while(q--) {
        rep(i,N)rep(j,2) t[i][j].clear();
		mem(vis, 1);
		mem(dp, -1);
		
		int m; cin >> m;
        while(m--) {
            cin >> s1 >> s2;
            t[h(s1)][1].eb(h(s2));
            t[h(s2)][1].eb(h(s1));
        }
        
        cin >> m >> s1;
        in = h(s1);
        while(m--) {
            cin >> s2;
            t[h(s1)][0].eb(h(s2));
            s1 = s2;
        }
        fi = h(s2);
        
        bfs();
        dp[fi] = 0; dfs(in);
        cout << dp[in] << '\n';
    }
    return 0;
}
