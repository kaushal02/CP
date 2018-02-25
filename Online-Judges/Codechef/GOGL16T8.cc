/*
_bitmask _fast_matrix_multiply

O(8^m * log n) per test
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;

#define X first
#define Y second
#define mp make_pair
#define all(c) begin(c), end(c)
#define con(i,a,b) a<=i and i<=b
#define uni(c) c.resize(distance(c.begin(), unique(all(c))))

#define rep(i,n) for(ll i=0, _n=(n); i<_n; i++)
#define rep1(i,n) for(ll i=1, _n=(n); i<=_n; i++)

#define cout(d) cout << fixed << setprecision(d)
#define err(x) cerr << #x << " = " << x << "\n"
#define TTi template <typename T> inline

const ll inf = 1e16, mod = 1e9 + 7;
const double eps = 1e-16;
const int N = 2e6 + 10;

const int M=1<<6;
TTi void mul(T a[M][M], T b[M][M]) {
    T c[M][M];
    rep(i,M)rep(j,M) {
        ll temp=0;
        rep(k,M) temp += a[i][k]*b[k][j]%mod;
        c[i][j]=temp%mod;
    }
    rep(i,M)rep(j,M) a[i][j]=c[i][j];
}

TTi void pwr(T a[M][M], ll n) {
    assert(n>=0);
    T temp[M][M];
    rep(i,M)rep(j,M) temp[i][j]=a[i][j], a[i][j]=i==j;
    while(n) {
        if(n&1) mul(a,temp);
        mul(temp,temp);
        n>>=1;
    }
}

int f[20], m;
inline int get(int x, int y) {
    if((x^y) != (x+y)) return 0;
    ll ans(1), j(0);
    rep(i,m) {
        if((x>>i&1)|(y>>i&1)) {
            ans = ans*f[i-j]%mod;
            j=i+1;
        }
    }
    return ans*f[m-j]%mod;
}

int main() {
    f[0] = f[1] = 1;
    for(int i = 2; i < 10; i++) f[i] = f[i-1] + f[i-2];

    int t; cin >> t;
    while(t--) {
        int n; cin >> m >> n;
        ll a[M][M]; memset(a, 0, sizeof a);
        rep(i,1<<m)rep(j,1<<m) a[i][j] = get(i,j);
        pwr(a,n); cout << a[0][0] << '\n';
    }
    return 0;
} 