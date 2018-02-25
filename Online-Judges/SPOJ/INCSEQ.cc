/*
_BIT _DP

O(n*k*logn)
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
#define rep1(i,n) for(ll i=1; _n=(n); i<=_n; i++)

#define cout(d) cout << fixed << setprecision(d)
#define err(x) cerr << #x << " = " << x << "\n"

const ll inf = 1e16, mod = 5e6;
const double eps = 1e-16;
const int N = 1e4 + 10;

template<class T>
struct bit {
    T *bt; int n;
    void cbit(int _n) {
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

pii a[N];
int main() {
    int n, k; scanf("%d%d", &n, &k);
    rep(i,n) scanf("%d", &a[i].X);
    rep(i,n) a[i].Y = i;
    sort(a, a+n);
    bit<int> b[k]; rep(i,k) b[i].cbit(n);
    int i(0);
    while(i<n) {
        int v=a[i].X, j(i);
        while(j<n and a[j].X==a[i].X) j++;
        for(int l=k-1; l>=0; l--) {
            for(int p=i; p<j; p++) {
                b[l].add(a[p].Y, l?b[l-1].sumh(a[p].Y-1):1);
            }
        }
        i=j;
    }
    cout << b[k-1].sumh(n-1);
    return 0;
}
