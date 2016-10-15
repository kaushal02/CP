/*
_graph _grid _01bfs

O(n*m)
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

string s[N];
int t[N][N][4], vis[N][N];
int main() {
    int n, m; cin >> n >> m;
    
    mem(t, -1);
    mem(vis, 1);
    
    rep1(i,0,n+1) s[0] += '#';
    rep1(i,1,n) {
        cin >> s[i];
        s[i] = '#' + s[i] + '#';
    }
    rep1(i,0,n+1) s[n+1] += '#';
    
    rep1(i,1,n) {
        int jj = 0;
        rep1(j,1,m+1) {
            if(s[i][j] == '#') {
                t[i][j][2] = jj;
                t[i][jj][0] = j;
                jj = j;
            }
        }
    }
    rep1(j,1,m) {
        int ii = 0;
        rep1(i,1,n+1) {
            if(s[i][j] == '#') {
                t[i][j][3] = ii;
                t[ii][j][1] = i;
                ii = i;
            }
        }
    }
    
    deque<pair<pii,pii>> q;
    q.push_back({{n,m+1},{0,2}});
    int x, y, st, d, xx, yy, stst, dd;
    while(!q.empty()) {
        tie(x,y) = q.front().X;
        tie(st,d) = q.front().Y;
        q.pop_front();
        
		if(vis[x][y] < st) continue;
        if(x == 1 and y == 0) {
            cout << st;
            return 0;
        }
        rep(dd,4) {
            xx = x, yy = y;
            if(dd & 1) xx = t[x][y][dd];
            else yy = t[x][y][dd];
            stst = st + (dd != d);
            if(xx < 0 or yy < 0 or xx > n or yy > m) continue;
            if(vis[xx][yy] > stst) {
                vis[xx][yy] = stst;
                if(stst == st) q.push_front({{xx,yy},{stst,dd}});
                else q.push_back({{xx,yy},{stst,dd}});
            }
        }
    }
    cout << -1;
    return 0;
}
