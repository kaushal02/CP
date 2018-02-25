/*
_fast_matrix_multiply

Constructed base matrix b = [[1 1 1]' [1 0 0]' [0 0 1]'] and bv = [b(0) b(-1) 1]' such that b^n * bv == [b(n) b(n-1) 1]'
Then observe that (b^n + b^m) * bv == [b(n+m) b(n+m-1) 1]'
Hence we can get b(n+m) from matrices of b(n) and b(m). No need of recursive relationships like F(n+m) = F(n+1)F(m) + F(n)F(m-1).
https://www.hackerrank.com/contests/sears-dots-arrows/challenges/modified-fibonacci-1

O(n * SZ^3)
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
#define name(x) #x

ll mod = 1e9 + 7;

inline ll add(ll a, ll b){
    ll ans = a + b;
    if(ans >= mod) return ans - mod;
    return ans;
}
inline ll mul(ll a , ll b){
    ll ans = a * b;
    if(ans >= mod) return ans % mod;
    return ans;
}
const int SZ = 3;
struct matrix {
    ll a[SZ][SZ];
    matrix() { mem(a, 0);}
    inline void id() { rep(i,SZ)rep(j,SZ) a[i][j] = (i == j);}
    inline matrix operator+( matrix &m)  {
        matrix ans;
        rep(i,SZ)rep(j,SZ) ans.a[i][j] = add(a[i][j], m.a[i][j]);
        return ans;
    }
    inline matrix operator*(const matrix &m) const {
        matrix ans;
        rep(i,SZ)rep(j,SZ)rep(k,SZ) ans.a[i][j] = add(ans.a[i][j], mul(a[i][k], m.a[k][j]));
        return ans;
    }
};
inline ostream& operator<<(ostream &cout, matrix &m) {
    rep(i,SZ) {
        cout << "| ";
        rep(j,SZ) cout << m.a[i][j] << " ";
        cout << "|\n";
    }
    cout << '\n';
    return cout;
}
inline matrix pwr(matrix a, ll n){
    assert(n >= 0);
    matrix ans;
    ans.id();
    while(n) {
        if(n & 1) ans = ans * a;
        a = a * a;
        n >>= 1;
    }
    return ans;
}

int main() {
    // ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n >> mod;
    int a[n]; rep(i,n) cin >> a[i];
    matrix ans, ans1, b, I;
    b.a[0][0] = b.a[0][1] = b.a[0][2] = b.a[1][0] = b.a[2][2] = 1;
    I.id();
    rep(i,n) {
        ans1 = (ans1 + I) * pwr(b, a[i]);
        ans = ans + ans1;
    }
    cout << (ans.a[0][0] - ans.a[0][1] + ans.a[0][2] + mod) % mod;
    return 0;
}
