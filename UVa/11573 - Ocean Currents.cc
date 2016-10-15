/*
_grid _01bfs _direction

O(q*n*m)
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
const int N = 1e3 + 10;

int dx[] = {-1,-1,0,1,1,1,0,-1};
int dy[] = {0,1,1,1,0,-1,-1,-1};

int n, m, ix, iy, fx, fy, d[N][N], vis[N][N];
inline void bfs01() {
    mem(vis, 1);
    deque<pair<pii,int>> q;
    q.push_front({{ix,iy},0});
    vis[ix][iy] = 0;
    int x, y, st, xx, yy, stst;
    while(!q.empty()) {
        tie(x,y) = q.front().X;
        st = q.front().Y;
        q.pop_front();
        
        if(x==fx and y==fy) {
            cout << vis[x][y] << '\n';
            return;
        }
        if(vis[x][y] < st) continue;
        rep(dir,8) {
            xx = x + dx[dir];
            yy = y + dy[dir];
            stst = st + (dir != d[x][y]);
            if(xx < 0 or xx >= n or yy < 0 or yy >= m) continue;
            if(vis[xx][yy] > stst) {
                vis[xx][yy] = stst;
                if(dir == d[x][y]) q.push_front({{xx,yy},stst});
                else q.push_back({{xx,yy},stst});
            }
        }
    }
    assert(0);
}
int main() {
    cin >> n >> m;
    rep(i,n) {
        string s; cin >> s;
        rep(j,m) d[i][j] = s[j] - '0';
    }
    int q; cin >> q;
    while(q--) {
        cin >> ix >> iy >> fx >> fy;
        ix--, iy--, fx--, fy--;
        bfs01();
    }
}
