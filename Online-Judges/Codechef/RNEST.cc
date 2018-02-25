/*
_line_sweep

O(n*log(n))
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
#define sz(c) c.size()
#define rep(i,n) for(int i = 0, _n = (n); i < _n; i++)
#define rep1(i,a,b) for(int i = a, _b = (b); i <= _b; i++)
#define rep2(i,b,a) for(int i = b, _a = (a); i >= _a; i--)
#define mem(a,val) memset(a, (val), sizeof a)
#define mp make_pair
#define eb emplace_back // tie, ignore, get<i>(a)
#define all(c) (c).begin(), (c).end()
#define uni(c) c.resize(distance(c.begin(), unique(all(c))))
#define tr(c,it) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)
#define case(ans) "Case #" << _t << ": " << ans << "\n"
#define cout(d) cout << fixed << setprecision(d)
#define err(x) cerr << #x << " = " << x << '\n'
const int mod = 1e9 + 7, N = 1e5 + 10;
 
struct room {
    int w, s, e, n, i;
} a[N];
int par[N];

int main() {
    int n; cin >> n;
    vector<pii> west, east;
    rep(i,n) {
        a[i].i = i;
        scanf("%d%d%d%d", &a[i].w, &a[i].s, &a[i].e, &a[i].n);
        west.eb(a[i].w, i);
        east.eb(a[i].e, i);
    }
    sort(all(west));
    sort(all(east));
    
    map<int,int> yc;
    map<int,int>::iterator it;
    int wit(0), eit(0), c;
    while(wit < n) {
        if(west[wit].X < east[eit].X) {
            c = west[wit].Y;
            it = yc.lower_bound(a[c].s);
            par[c] = (it == yc.end() ? -1:it->Y);
            yc[a[c].s] = par[c];
            yc[a[c].n] = c;
            wit++;
        }
        else {
            c = east[eit].Y;
            yc.erase(a[c].n);
            yc.erase(a[c].s);
            eit++;
        }
    }
    rep(i,n) cout << par[i] << '\n';
    return 0;
}