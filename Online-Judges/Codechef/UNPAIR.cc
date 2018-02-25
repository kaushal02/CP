/*
_MST

O(input size)
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
 
#define case(ans) "Case #" << _t << ": " << ans << "\n"
#define cout(d) cout << fixed << setprecision(d)
#define err(x) cerr << #x << " = " << x << '\n'
 
#define TTi template<typename T> inline
 
const ll inf = 1e16, mod = 1e9 + 7;
const double eps = 1e-16;
const int N = 1e2 + 10;
 
int n, a[N][N], par[N];
bool vis[N];
inline void mst_prim() { // O(n^2)
    mem(par, -1);
    mem(vis, false);
    bool error = false;
    
    vi key(n,INT_MAX); // modify
    par[0] = key[0] = 0;
    
    ll ans(0);
    rep(i,n) {
        int mi(INT_MAX), k(-1); // modify
        rep(j,n) {
            if(!vis[j] and key[j] < mi) // modify
                mi = key[j], k = j;
        }
        if(k == -1) {
            error = true;
            break;
        }
        vis[k] = true;
        ans += key[k] << 1;
        rep(j,n) {
            // 1st condition changes, third toggles
            if(!vis[j] and a[k][j] != 0 and a[k][j] < key[j])
                par[j] = k, key[j] = a[k][j];
        }
    }
    if(error) ans = -1;
    if(n == 1) ans = a[0][0] - !a[0][0];
    
    cout << ans << '\n';
}
 
int main() {
    int q; cin >> q;
    while(q--) {
        cin >> n;
        rep(i,n)rep(j,n) cin >> a[i][j];
        mst_prim();
    }
    return 0;
}
//--------------------------------------------------------------//
/*
_DSU _MST

O(n^2 * logn)
*/
// Time erodes gratitude more quickly than it does beauty!
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;

#define X first
#define Y second
#define rep(i,n) for(ll i=0; i<(n); i++)
#define rep1(i,a,b) for(ll i=a; i<=(b); i++)
#define rep2(i,b,a) for(ll i=b; i>=(a); i--)
#define mem(a,val) memset(a, (val), sizeof a)
#define mp make_pair
#define pb push_back
#define all(c) (c).begin(), (c).end()
#define uni(c) c.resize(distance(c.begin(), unique(all(c))))
#define fix(c,sz_val...) c.clear();c.resize(sz_val);
#define tr(c,it,ctype...) for(ctype::iterator it = c.begin(); it != c.end(); ++it)
#define io ios_base::sync_with_stdio(false);cin.tie(NULL)
#define IO(input_file_name) ifstream cin(input_file_name);ofstream cout("output.txt")
#define print(ans) cout<<"Case #"<<_t<<": "<<ans<<"\n"
const int mod = 1e9 + 7;

struct node {
    int x, y, val;
    node(int _x, int _y, int _v):
        x(_x), y(_y), val(_v) {}
};
bool comp(node l, node r) {
    return l.val < r.val;
}

struct dsu
{
    vi par;
    dsu(int n): par(n) {rep(i,n) par[i] = i;}
    void adopt(int a, int b) { par[dad(b)] = dad(a);}
    int dad(int a) { return a == par[a] ? a : par[a] = dad(par[a]);}
    bool dogla(int a, int b) { return dad(a) != dad(b);}
};

typedef vector< vector<pii> > vvp;
ll mst_kruskal(vvp& g)
{
    vector<node> temp;
    int n = g.size();
    rep(i,n)
        rep(j,g[i].size())
            temp.pb(node(i,g[i][j].X,g[i][j].Y));
    sort(all(temp), comp);
    dsu d(n);
    
    ll ans(0);
    int edgeid(0), k(0), m(temp.size());
    while(edgeid < n-1 && k < m)
    {
        if(d.dogla(temp[k].x,temp[k].y))
        {
            edgeid++;
            ans += temp[k].val;
            d.adopt(temp[k].x, temp[k].y);
        }
        k++;
    }
    return edgeid == n-1 ? 2LL*ans : -1;
}

void f()
{
    int w;
    int n;cin>>n;
    if(n == 1)
    {
        cin >> w;
        cout << w - (w == 0) << endl;
        return;
    }
    vvp g(n);
    rep(i,n)rep(j,n)
    {
        cin>>w;
        if(w == 0 || i == j) continue;
        g[i].pb(mp(j, w));
        g[j].pb(mp(i, w));
    }
    cout << mst_kruskal(g) << endl;
}

int main()
{
    io;
    int t;cin>>t;rep(i,t)f();
    return 0;
}