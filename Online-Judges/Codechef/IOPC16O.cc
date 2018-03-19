/*
2D _subarray

worst case: O(m^2*n^2) per testcase
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
#define coutt cout << "Case " << _t << ": "
#define io ios_base::sync_with_stdio(false); cin.tie(NULL);

const dbl eps=1e-12, pi=acosl(-1);
const int inf=1e16, mod=1e9+7, N=2e6+10;

#undef int
int main() {
#define int long long

    cases {
        int n, m; cin >> n >> m;
        int a[n][m]; rep(i,n)rep(j,m) cin >> a[i][j];
        int ans=0;
        rep(j1,m) {
            int b[n]={}, w=0;
            for(int j2=j1; j2<m; j2++) {
                w++;
                rep(i,n) b[i]=__gcd(b[i],a[i][j2]);
                rep(i1,n) {
                    int g=0, h=0;
                    for(int i2=i1; i2<n; i2++) {
                        h++;
                        g=__gcd(g,b[i2]);
                        if(ans>=g*w*n) break;
                        ans = max(ans, g*w*h);
                    }
                }
            }
        }
        cout << ans << '\n';
    }

    return 0;
}
