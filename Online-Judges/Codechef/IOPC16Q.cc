/*
_subarray

Lets say we want to minimize the sum abs(ai-p) for an array a[]. We need the
optimal pivot p. If array size is 2, any number between a[0] and a[1] can be p.
Similarly, if array size is 4, any number between a[1] and a[2] can be p.
Conclude that a[n/2] can be pivot for array a[0..n-1]

Conclude this reduced statement: Find a pair (i,j) where i<j, such that
taking ai and aj as x and y, the answer is minimum. Report the answer.
This is O(n^2). Then notice that you can actually iterate over the last index
till which numbers converge to the first pivot. This is O(n).

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
        int n; cin >> n;
        vi a(n); rep(i,n) cin >> a[i];
        sort(all(a));
        vi b(n); rep(i,n) b[i] = (i ? b[i-1]:0) + a[i];
        
        int ans=inf;
        rep(i,n) ans = min(ans, a[i>>1]*(i%2==0)
                                + a[i+n>>1]*(i%2==n%2)
                                - b[i>>1]
                                + b[i] - b[i>>1]
                                - b[i+n>>1] + b[i]
                                + b[n-1] - b[i+n>>1]);
        cout << (n<3 ? 0:ans) << '\n';
    }

    return 0;
}
