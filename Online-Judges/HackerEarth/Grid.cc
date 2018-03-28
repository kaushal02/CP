/*
_01bfs _direction 

https://www.hackerearth.com/challenge/competitive/airtel-crack-the-code/algorithm/robot-in-grid-b7d391f7
The solution encounters TLE if strict inequality is used in line 53
credits while debugging: Vibhor
O(n*m)
*/
#include <bits/stdc++.h>
using namespace std;
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
const int inf=1e16, mod=1e9+7, N=1e3+10;
int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};
 
char s[N];
int n, m, si, sj, a[N][N], valid[N][N];
inline void bfs() {
    mem(a, -1);
    queue<pair<pii,int>> q;
    q.push({{si,sj}, a[si][sj]=0});
    while(!q.empty()) {
        int i, j, v;
        tie(i,j) = q.front().X;
        v = q.front().Y;
        q.pop();
        if(a[i][j]<v) continue;
        rep(d,4) {
            int ii=i+dx[d];
            int jj=j+dy[d];
            if(!valid[ii][jj]) continue;
            if(a[ii][jj]+1 and a[ii][jj] <= a[i][j]+1) continue;
            q.push({{ii,jj}, a[ii][jj]=a[i][j]+1});
        }
    }
}
 
int main() {
 
    int q; scanf("%d%d%d\n", &n, &m, &q);
    rep1(i,n) {
        scanf("%s\n", s);
        rep1(j,m) if(s[j-1]!='*') valid[i][j]=1;
    }
    scanf("%d%d\n", &si, &sj);
    bfs();
    while(q--) {
        int i, j; scanf("%d%d\n", &i, &j);
        printf("%d\n", a[i][j]);
    }
 
    return 0;
}