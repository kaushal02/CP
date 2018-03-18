/*
_dfs _sieve _DP

O(n*m*logm) per testcase
*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
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

#define rep(i,n) for(int i=0, _n=(n); i<_n; i++)
#define rep1(i,n) for(int i=1, _n=(n); i<=_n; i++)
#define cout(d) cout << fixed << setprecision(d)
#define err(x) cerr << #x << " = " << x << "\n"

#define cases int _t_; cin >> _t_; rep1(_t,_t_)
#define coutt cout << "Case " << _t << ": "
#define io ios_base::sync_with_stdio(false); cin.tie(NULL);

const dbl eps=1e-12, pi=acosl(-1);
const int inf=1e16, mod=1e9+7, N=550, M=20020;

vi t[N];
int n, m, a[N][M], b[N][M];
inline void dfs(int v, int p) {
    rep1(i,m) a[v][i] = 1;
    for(int ch: t[v]) if(ch != p) {
        dfs(ch, v);
        rep1(i,m) a[v][i] = a[v][i]*b[ch][i]%mod;
    }
    for(int i=m; i; i--) {
        b[v][i] = 0;
        for(int j=1; i*j<=m; j++) b[v][i] += a[v][i*j];
        b[v][i] %= mod;
    }
}

#undef int
int main() {
#define int long long

    cases {
        cin >> n >> m;
        rep(i,N) t[i].clear();
        rep(i,n-1) {
            int u, v; cin >> u >> v;
            t[u].pb(v); t[v].pb(u);
        }
        dfs(1,1);
        cout << b[1][1] << '\n';
    }

    return 0;
}
