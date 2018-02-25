/*
_direction _dij

O(n^2 * log(n))
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
#define rep(i,n) for(int i = 0, _n = (n); i < _n; i++)
#define rep1(i,a,b) for(int i = a, _b = (b); i <= _b; i++)
#define rep2(i,b,a) for(int i = b, _a = (a); i >= _a; i--)
#define mem(a,val) memset(a, (val), sizeof a)
#define mp make_pair
#define mt make_tuple // remember tie & ignore
#define eb emplace_back
#define all(c) (c).begin(), (c).end()
#define uni(c) c.resize(distance(c.begin(), unique(all(c))))
#define tr(c,it) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)
#define cases int __t; cin >> __t; rep1(_t,1,__t)
#define case(ans) "Case #" << _t << ": " << ans << "\n"
#define cout(d) cout << fixed << setprecision(d)
#define err(x) cerr << #x << " = " << x << '\n'
const int mod = 1e9 + 7;
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
 
int n, m, a[25][25];
int vis[25][25];
vi way[25][25], ans;
 
#define pq(ctype...) priority_queue < ctype, vector < ctype >, compare < ctype > >
template <class T >
struct compare {
    bool operator()(const T& l, const T& r) const {
        return get<2>(l) > get<2>(r); // Put the logic
    }
};
inline void findway(int x, int y) {
    if(a[x][y] != 1) return;
    mem(vis, -1);
    pq(tuple<int,int,int>) q;
    q.emplace(x,y,0);
    
    vi temp;
    int i,j,st,ii,jj;
    while(!q.empty()) {
        tie(i,j,st) = q.top(); q.pop();
        if(vis[i][j] !=  -1) continue;
        vis[i][j] = st;
        if(a[i][j] == 2) {
            while(i!=x or j!=y) {
                rep(dir,4) {
                    ii = i + dx[dir];
                    jj = j + dy[dir];
                    if(vis[ii][jj] < vis[i][j] and vis[ii][jj] + 1) {
                        temp.eb((dir + 2) % 4);
                        i = ii, j = jj;
                    }
                }
            }
            reverse(all(temp));
            way[x][y] = temp;
            return;
        }
        
        rep(dir,4) {
            ii = i + dx[dir];
            jj = j + dy[dir];
            if(vis[ii][jj] == -1 and a[ii][jj]) q.emplace(ii,jj,st+1);
        }
    }
}
 
inline void go(int &i, int &j) {
    int ii, jj;
    for(int dir: ans) {
        ii = i + dx[dir];
        jj = j + dy[dir];
        if(a[ii][jj]) i = ii, j = jj;
    }
}
 
int main() {
    string s;
    cin >> n >> m;
    rep(i,n) {
        cin >> s;
        rep(j,m) switch(s[j]) {
            case '*': a[i][j] = 0; break;
            case '.': a[i][j] = 1; break;
            case 'C': a[i][j] = 2; break;
            default: assert(false);
        }
    }
    
    rep(i,n)rep(j,m) findway(i,j);
    int ii, jj;
    mem(vis, 0);
    rep(i,n)rep(j,m) {
        if(a[i][j] != 1) continue;
        ii = i, jj = j;
        go(ii,jj);
        ans.insert(ans.end(), all(way[ii][jj]));
    }
    
    for(int x: ans) switch(x) {
        case 0: cout << 'R'; break;
        case 1: cout << 'D'; break;
        case 2: cout << 'L'; break;
        case 3: cout << 'U'; break;
        default: assert(false);
    }
    return 0;
}
