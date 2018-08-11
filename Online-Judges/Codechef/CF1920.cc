/*
_fast_matrix_multiply

https://www.codechef.com/viewsolution/19637973

O(5^3 * log(i)) per testcase
*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
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
#define coutt cout << "Case #" << _t << ": "
#define io ios_base::sync_with_stdio(false); cin.tie(NULL);

template <typename T> inline bool Max(T &a, T b) { return (a<b ? a=b,1:0);}
template <typename T> inline bool Min(T &a, T b) { return (a>b ? a=b,1:0);}

const dbl eps=1e-12, pi=acosl(-1);
const int inf=1e16, mod=1e9+7, N=2e6+10;

const int M=5;
template<class T> void mul(T a[M][M], T b[M][M]) {
    T c[M][M];
    rep(i,M)rep(j,M) {
        int temp=0;
        rep(k,M) temp += a[i][k]*b[k][j]%mod;
        c[i][j]=temp%mod;
    }
    rep(i,M)rep(j,M) a[i][j]=c[i][j];
}
template<class T> void pwr(T a[M][M], int n) {
    assert(n>=0);
    T temp[M][M];
    rep(i,M)rep(j,M) temp[i][j]=a[i][j], a[i][j]=i==j;
    while(n) {
        if(n&1) mul(a,temp);
        mul(temp,temp);
        n>>=1;
    }
}

#undef int
int main() {
#define int long long

    cases {
        int a, b, x, y, i;
        cin >> a >> b >> x >> y >> i;
        a%=mod, b%=mod, x%=mod, y%=mod;
        int m0[M][M] = {{a+2, b-2*a-1, a-2*b, b, 2}};
        m0[1][0] = m0[2][1] = m0[3][2] = m0[4][4] = 1;
        rep(i,M)rep(j,M) m0[i][j] = (m0[i][j]%mod+mod)%mod;

        int v[M] = {0,0,y,x,1};
        v[1] = (a*v[2]+b*v[3]+4)%mod;
        v[0] = (a*v[1]+b*v[2]+9)%mod;

        int ans=0;
        if(i>3) {
            pwr(m0, i-3);
            rep(j,M) ans += m0[0][j]*v[j]%mod;
        }
        else {
            ans = v[3-i];
        }
        cout << ans%mod << '\n';
    }

    return 0;
}
