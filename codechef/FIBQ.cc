/*
_matrix _segment_tree

O(n*K^3*log(M) + q*log(n))
K is the matrix dimension, M is the maximum power raised.
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
const int N = 1e5 + 10;

const int Nmat = 2;
TTi void mul(T a[Nmat][Nmat], T b[Nmat][Nmat]) {
    ll temp;
    register T c[Nmat][Nmat];
    rep(i,Nmat)rep(j,Nmat) { // modify
        temp = 0;
        rep(k,Nmat) temp += a[i][k] * b[k][j] % mod;
        c[i][j] = temp % mod;
    }
    rep(i,Nmat)rep(j,Nmat) a[i][j] = c[i][j];
}
TTi void pwr(T a[Nmat][Nmat], ll n) {
    assert(n >= 0);
    T temp[Nmat][Nmat];
    rep(i,Nmat)rep(j,Nmat) {
        temp[i][j] = a[i][j];
        a[i][j] = 0;
    }
    rep(i,Nmat) {
        a[i][i] = 1;
    }
    while(n) {
        if(n & 1) mul(a, temp);
        n >>= 1;
        mul(temp, temp);
    }
}
 
inline int fib(int n) {
    ll a[Nmat][Nmat] = {{1,1},{1,0}};
    pwr(a, n);
    return a[1][0];
}

struct nod {
    int l, c, r;
} tree[N << 1] = {};
int n, arr[N];
inline nod combine(nod a, nod b) {
    nod ans = {};
    ans.l = ((ll)(a.l + b.l) + (ll)a.l * b.l + (ll)a.c * b.c) % mod;
    ans.c = ((ll)(a.c + b.c) + (ll)a.l * b.c + (ll)a.c * b.r) % mod;
    ans.r = ((ll)(a.r + b.r) + (ll)a.c * b.c + (ll)a.r * b.r) % mod;
    return ans;
}
inline void build() {
    for(int i = n; i--; )
        tree[n + i] = {fib(arr[i] - 1), fib(arr[i]), fib(arr[i] + 1)};
    for(int i = n; --i; )
        tree[i] = combine(tree[i << 1], tree[i << 1 | 1]); 
}
inline void update(int pos, int value) {
    tree[n + pos] = {fib(value - 1), fib(value), fib(value + 1)}; // tree[n + pos] = combine(tree[n + pos], nod(value));
    for(int i = n + pos; i >>= 1; )
        tree[i] = combine(tree[i << 1], tree[i << 1 | 1]);
}
inline nod query(int l, int r) {
    nod ansl = {}, ansr = {};
    for(l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
        if(l & 1) ansl = combine(ansl, tree[l++]);
        if(r & 1) ansr = combine(tree[--r], ansr);
    }
    cout << combine(ansl, ansr).c << '\n';
}
int main() {
    int m;
    cin >> n >> m;
    rep(i,n) cin >> arr[i];
    build();
    char c;
    int x, y;
    rep(i,m) {
        cin >> c >> x >> y;
        if(c == 'C') update(x - 1, y);
        else if(c == 'Q') query(x - 1, y - 1);
        else assert(0);
    }
    return 0;
}
