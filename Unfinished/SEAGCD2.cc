/*
_bitset

https://www.codechef.com/problems/SEAGCD2

Observe that any integer other than unity occurs at most once. Find all the
subsets of [2..m] which can occur. Then for each of these subsets of size i, the
answer increases by P(n,n-i).

issue: for m=60, number of subsets is more than 8e6. Hence the solution suffers
MLE and TLE for n>60.

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
const int inf=1e16, mod=1e9+7, N=2e5+10, M=101;
typedef bitset<M> boolean;

namespace std {
    template<size_t N> struct less<bitset<N>>:
    binary_function <bitset<N>,bitset<N>,bool> {
        bool operator()(const bitset<N> &L, const bitset<N> &R) const {
            rep(i,N) if(L[i]^R[i]) return R[i];
            return false; // same
        }
    };
}

int n, m;
int fac[N], inv[N];
boolean u[M], pf[M];
vector<boolean> cnt[2];

inline void Add(int &x, int y) {
    if((x+=y)>=mod) x-=mod;
}
inline int pwr(int a, int n) {
    int ans=1;
    while(n) {
        if(n&1) ans=ans*a%mod;
        if(n>>=1) a=a*a%mod;
    }
    return ans;
}
inline void init(int N) {
    fac[0]=1; rep1(i,N) fac[i]=fac[i-1]*i%mod;
    inv[N]=pwr(fac[N],mod-2);
    for(int i=N; i>=1; i--) inv[i-1]=inv[i]*i%mod;
}


#undef int
int main() {
#define int long long

    init(N-1);
    rep(i,M) u[i].set(i);
    rep(i,M) for(int j=2; j<=i; j++) if(__gcd(i,j)>1) pf[i].set(j);
    
    cases {
        cin >> n >> m;
        cnt[0].clear();
        cnt[1].clear();
        cnt[0].pb(boolean());
        for(int i=2; i<=m; i++) {
            for(boolean b: cnt[0]) if((b&pf[i]).none()) cnt[1].pb(b|u[i]);
            cnt[0].insert(cnt[0].end(), all(cnt[1]));
            cnt[1].clear();
        }
        int ans=0;
        for(boolean b: cnt[0]) if(b.count()<=n) {
            Add(ans, fac[n]*inv[n-b.count()]%mod);
        }
        cout << ans << '\n';
    }

    return 0;
}
