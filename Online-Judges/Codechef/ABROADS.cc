/*
_DSU _offline

O((n + (q + m) * α(n)) * log(n))
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
#define sz(c) (ll)c.size()
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
const int N = 5e5 + 10;

ll n, m, q, ans[N];
bool toadd[N];
pii e[N];
pair<char,pll> query[N];
stack<ll> w[N];

struct dsu {
    vi par;
    map<ll,ll> weights, weight_count;
    map<ll,ll>:: iterator it;
    dsu(int n): par(n) { rep(i,n) par[i] = i, weights[i] = w[i].top(), ++weight_count[w[i].top()];}
    void merge(int a, int b) {
        it = weight_count.find(weights[dad(a)]);
        --(it->Y);
        it = weight_count.find(weights[dad(b)]);
        --(it->Y);
        
        weights[dad(a)] += weights[dad(b)];
        weights.erase(dad(b));
        
        ++weight_count[weights[dad(a)]];
        
        par[dad(b)] = dad(a);
    }
    int dad(int a) { return a == par[a] ? a : par[a] = dad(par[a]);}
    bool diff(int a, int b) { return dad(a) != dad(b);}
    ll dia() {
        while(!weight_count.rbegin()->Y) {
            it = weight_count.end();
            weight_count.erase(--it);
        }
        return weight_count.rbegin()->X;
    }
    void adjust(int a, ll old_w) {
        it = weight_count.find(weights[dad(a)]);
        --(it->Y);
        
        weights[dad(a)] += w[a].top() - old_w;
        ++weight_count[weights[dad(a)]];
    }
};

int main() {
    string s;
    ll x, y;
    
    cin >> n >> m >> q;
    rep(i,n) cin >> x, w[i].push(x);
    rep(i,m) cin >> e[i].X >> e[i].Y, e[i].X--, e[i].Y--;
    mem(toadd, true);
    rep(i,q) {
        cin >> s;
        query[i].X = s[0];
        if(s[0] == 'P') {
            cin >> x >> y; x--;
            query[i].Y = mp(x,y);
            w[x].push(y);
        }
        else {
            cin >> x; x--;
            query[i].Y = mp(x,0);
            toadd[x] = false;
        }
    }
    
    dsu d(n);
    rep(i,m) if(toadd[i]) {
        if(d.diff(e[i].X, e[i].Y))
            d.merge(e[i].X, e[i].Y);
    }

    ans[q-1] = d.dia();
    rep2(i,q-1,1) {
        if(query[i].X == 'P') {
            x = query[i].Y.X;
            y = query[i].Y.Y;
            w[x].pop();
            d.adjust(x,y);
        }
        else {
            x = query[i].Y.X;
            if(d.diff(e[x].X, e[x].Y))
                d.merge(e[x].X, e[x].Y);
        }
        ans[i-1] = d.dia();
    }
    
    rep(i,q) cout << ans[i] << '\n';
    return 0;
}
