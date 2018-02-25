/*
_BIT
Similar to SPOJ/DQUERY

O((n+q)*logn)
*/

// g++ -std=c++11 -O3 -fmax-errors=1
#include <bits/stdc++.h>
using namespace std;
#define int ll
typedef long long ll;
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

#define rep(i,n) for(ll i=0, _n=(n); i<_n; i++)
#define rep1(i,n) for(ll i=1, _n=(n); i<=_n; i++)
#define cout(d) cout << fixed << setprecision(d)
#define err(x) cerr << #x << " = " << x << "\n"

#define cases int _t_; cin >> _t_; rep1(_t,_t_)
#define coutt cout << "Case " << _t << ": "
#define io ios_base::sync_with_stdio (false); cin.tie(NULL);

const dbl eps=1e-12, pi=acosl(-1);
const ll inf=1e16, mod=1e9+7;
const int N=2e6+10;

struct node {
    int l, r, i;
    bool operator<(node a) {
        return r<a.r;
    }
} b[N];

int bt[N], nb;
inline int get(int x) {
    int sum=0; x++;
    for(int i=x; i>0; i^=i&-i)
        sum+=bt[i];
    return sum;
}
inline void updh(int x, int val) {
    x++;
    for(int i=x; i<=nb; i+=i&-i)
        bt[i]+=val;
}
inline void upd(int x, int X, int val) {
    if(x>X) return;
    X++;
    updh(X, -val);
    updh(x, val);
}

int a[N], ans[N];

#undef int
int main() {
#define int ll

	int n; cin >> n;
    rep(i,n) cin >> a[i];
    int q; cin >> q;
    rep(i,q) cin >> b[i].l >> b[i].r, b[i].i=i;
    sort(b,b+q);
	int j=0;

    nb=n+2;
    map<int,pii> pos;
    rep(i,n) pos[a[i]]={-1,-1};
    rep(i,n) {
        auto it=pos.find(a[i]);
        upd(it->Y.X+1, i, 1);
        upd(it->Y.Y+1, it->Y.X, -1);
        it->Y={i, it->Y.X};
        while(j<q and b[j].r-1==i) {
            ans[b[j].i] = get(b[j].l-1);
            j++;
        }
    }
    rep(i,q) cout << ans[i] << '\n';
    return 0;
}
