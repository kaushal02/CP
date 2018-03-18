/*
_sweep

{xi,di} is valid for all numbers in the range [xi*di, xi*(di+1))
Since Sergey touched at max K pairs, it means at least N-K pairs still satisfy.
It means that a line sweep where at least N-K ranges are active gives possible
values of A.
Boundary case: when K==N, all possible values of A satisfy, which is 10^100 + 1.

O(nlogn)
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
        int n, k; cin >> n >> k;
        vector<pii> a(2*n); rep(i,n) {
            int x, y; cin >> x >> y;
            a[i<<1] = {x*y, -i-1};
            a[i<<1|1] = {x*(y+1)-1, i+1};
        }
        sort(all(a));
        k = n-k;
        n <<= 1;
        if(!k) {
            cout << "226732711\n";
            continue;
        }
        int i=0, px=0, c=0, ans=0;
        while(i<n) {
            if(c>=k) ans += a[i].X-px-1;
            px = a[i].X;
            while(i<n and a[i].X==px and a[i].Y<0) {
                c++; i++;
            }
            if(c>=k) ans++;
            while(i<n and a[i].X==px and a[i].Y>0) {
                c--; i++;
            }
        }
        cout << ans%mod << '\n';
    }

    return 0;
}
