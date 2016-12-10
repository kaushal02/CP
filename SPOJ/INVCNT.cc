/*
_bit _compression
O(nlogn) per test case
*/
// g++ -std=c++11 -O2 
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;

#define X first
#define Y second
#define mp make_pair
#define pb push_back
#define all(c) begin(c), end(c)
#define con(i,a,b) a<=i and i<=b
#define uni(c) c.resize(distance(c.begin(), unique(all(c))))

#define rep(i,n) for(ll i=0, _n=(n); i<_n; i++)
#define rep1(i,n) for(ll i=1, _n=(n); i<=_n; i++)

#define cout(d) cout << fixed << setprecision(d)
#define err(x) cerr << #x << " = " << x << "\n"

const ll inf = 1e16, mod = 1e9 + 7;
const double eps = 1e-16;
const int N = 2e5 + 10;
template<class T>
struct bit {
    T *bt; int n;
    bit(int _n) {
        n=_n;
        bt=(T*)calloc(n+1,sizeof(T));
    }
    void add(int u, T v=1) {
        u++;
        while(u<=n) {
            bt[u]=(bt[u]+v)%mod;
            u+=u&-u;
        }
    }
    T sumh(int u) {
        T ans=0; u++;
        while(u) {
            ans=(ans+bt[u])%mod;
            u^=u&-u;
        }
        return ans;
    }
};
int a[N];
int main() {
    int q; cin >> q;
    while(q--) {
        int n; cin >> n;
        rep(i,n) cin >> a[i];
        
        vi c(a, a+n); sort(all(c)); uni(c);
        map<int,int> id;
        int k(0); for(auto x: c) id[x]=k++;
        
        rep(i,n) a[i]=id[a[i]];
        bit<int> b(k);
        ll ans(0);
        rep(i,n) {
            ans+=i-b.sumh(a[i]);
            b.add(a[i]);
        }
        cout << ans << '\n';
    }
    return 0;
}
