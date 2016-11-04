/*
_dij
Finding k'th best path using simple dijkstra. It takes O(nlogmk * k).
https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&category=24&problem=1283
O(n * min(nlogm, n + qlogm)) per test case
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
const int N = 1e2 + 10, K = 2; // Only changing this value is enough to solve the problem for K'th best path

vi a[N][N];
int n, did[N];
vector<pii> t[N];
inline void print(int u, int v) {
    if(a[u][v].size() < K) cout << "?\n";
    else cout << a[u][v].back() << '\n';
}
inline void dij(int s) {
    int d, v;
    priority_queue<pii> q;
    q.emplace(0,s);
    while(!q.empty()) {
        tie(d,v) = q.top(); q.pop();
        if(a[s][v].empty() or (a[s][v].size() < K and a[s][v].back() < -d)) {
            a[s][v].eb(-d);
            for(pii ch: t[v]) {
                if(a[s][ch.X].size() < K) {
                    q.emplace(d - ch.Y, ch.X);
                }
            }
        }
    }
}
int main() {
//    freopen("this.txt", "r", stdin);
    int setnum = 0;
    while(cin >> n) {
        int m; cin >> m;
        rep(i,n) {
            did[i] = 0;
            t[i].clear();
            rep(j,n) a[i][j].clear();
        }
        rep(i,m) {
            int x, y, z; cin >> x >> y >> z;
            t[x].eb(y,z);
            t[y].eb(x,z);
        }
        
        cout << "Set #" << ++setnum << '\n';
        int q; cin >> q;
        while(q--) {
            int x, y; cin >> x >> y;
            if(did[x]) print(x,y);
            else if(did[y]) print(y,x);
            else {
                dij(x); did[x] = 1;
                print(x,y);
            }
        }
    }
    return 0;
}
