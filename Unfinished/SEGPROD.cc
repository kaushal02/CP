/*
[Codechef] https://www.codechef.com/NOV17/problems/SEGPROD
*/
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
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
 
#define rep(i,n) for(ll i=0, _n=(n); i<_n; i++)
#define rep1(i,n) for(ll i=1, _n=(n); i<=_n; i++)
#define cout(d) cout << fixed << setprecision(d)
#define err(x) cerr << #x << " = " << x << "\n"
 
#define cases int _t_; cin >> _t_; rep1(_t,_t_)
#define coutt cout << "Case " << _t << ": "
#define io ios_base::sync_with_stdio (false); cin.tie(NULL);
 
const dbl eps=1e-12, pi=acosl(-1);
const ll inf=1e16, mod=1e9+7;
const int N=1e6+10, M=10;
 
ll n, m, p, a[N], c[N][M], pw[M], pwt[M];
ll b[N], ib[N];
ll pr[M], ipr[M];
ll d[N][M], id[N][M];
 
ll eed, eex, eey;
inline void ee(ll a, ll b) { // a,b < 1e18
    // Gives solutions to ax + by = __gcd(a,b)
    if(!b) eed=a, eex=1, eey=0;
    else {
        ee(b, a%b);
        ll t=eex;
        eex=eey;
        eey=t - a/b*eey;
    }
}
inline ll inv(ll n, ll m) { // n,m < 1e18
    ee(n, m); assert(eed==1);
    eex%=m; return (eex<0 ? eex+m:eex);
}
inline void precalc() {
    ll i, q(p);
    for(m=0, i=2; i<=q/i; i++) if(q%i==0) {
        ll c=0, r=p;
        while(q%i==0) q/=i, r/=i, c++;
        pw[m]=c;
        pr[m]=i;
        ipr[m]=inv(i,r);
        m++;
    }
    if(q>1) {
        pw[m]=1;
        pr[m]=q;
        ipr[m]=inv(q,p/q);
        m++;
    }
 
    rep(i,n) {
        q=a[i]; rep(j,m) {
            c[i][j]=(i ? c[i-1][j]:0LL);
            d[i][j]=(i ? d[i-1][j]:1LL);
            id[i][j]=(i ? id[i-1][j]:1LL);
            while(q%pr[j]==0) {
                q/=pr[j];
                c[i][j]++;
                d[i][j]=d[i][j]*pr[j]%p;
                id[i][j]=id[i][j]*ipr[j]%p;
            }
        }
        b[i]=(i ? b[i-1]:1LL)*q%p;
        ib[i]=inv(b[i],p);
    }
}
 
inline int solve(int l, int r) {
    int fl=1; rep(j,m) {
        pwt[j]=c[r][j]-(l ? c[l-1][j]:0);
        if(pwt[j]<pw[j]) fl=0;
    }
    if(fl) return 0;
 
    ll ans=b[r]*(l ? ib[l-1]:1)%p;
    rep(j,m) ans=ans*(d[r][j]*(l ? id[l-1][j]:1)%p)%p;
    return ans;
}
 
int main() {
    ll t, q; scanf("%lld", &t);
    while(t--) {
        scanf("%lld%lld%lld", &n, &p, &q);
        rep(i,n) scanf("%lld", &a[i]);
        precalc();
        ll x=0, bp, bc, li, ri;
        scanf("%lld", &bc);
        rep(i,q) {
            if(i%64) {
                li = (li+x)%n;
                ri = (ri+x)%n;
            }
            else {
                bp = bc;
                scanf("%lld", &bc);
                li = (bp+x)%n;
                ri = (bc+x)%n;
            }
            if(li>ri) swap(li,ri);
            x = (solve(li,ri)+1)%p;
        }
        printf("%lld\n", x);
    }
    return 0;
}

//---------------------------------------------------------------------------//
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
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
 
#define rep(i,n) for(ll i=0, _n=(n); i<_n; i++)
#define rep1(i,n) for(ll i=1, _n=(n); i<=_n; i++)
#define cout(d) cout << fixed << setprecision(d)
#define err(x) cerr << #x << " = " << x << "\n"
 
#define cases int _t_; cin >> _t_; rep1(_t,_t_)
#define coutt cout << "Case " << _t << ": "
#define io ios_base::sync_with_stdio (false); cin.tie(NULL);
 
const dbl eps=1e-12, pi=acosl(-1);
const ll inf=1e16, mod=1e9+7;
const int N=1e6+10, M=10;
 
ll n, m, p, a[N], c[N][M], pw[M], pwt[M];
ll b[N], ib[N];
ll pr[M], ipr[M];
ll d[N][M], id[N][M];
 
ll eed, eex, eey;
inline void ee(ll a, ll b) { // a,b < 1e18
    // Gives solutions to ax + by = __gcd(a,b)
    if(!b) eed=a, eex=1, eey=0;
    else {
        ee(b, a%b);
        ll t=eex;
        eex=eey;
        eey=t - a/b*eey;
    }
}
inline ll inv(ll n, ll m) { // n,m < 1e18
    ee(n, m); assert(eed==1);
    eex%=m; return (eex<0 ? eex+m:eex);
}
inline void precalc() {
    ll i, q(p);
    for(m=0, i=2; i<=q/i; i++) if(q%i==0) {
        ll c=0, r=p;
        while(q%i==0) q/=i, r/=i, c++;
        pw[m]=c;
        pr[m]=i;
        ipr[m]=inv(i,r);
        m++;
    }
    if(q>1) pr[m]=q, pw[m]=1, m++;
 
    rep(i,n) {
        q=a[i]; rep(j,m) {
            c[i][j]=(i ? c[i-1][j]:0LL);
            d[i][j]=(i ? d[i-1][j]:1LL);
            id[i][j]=(i ? id[i-1][j]:1LL);
            while(q%pr[j]==0) {
                q/=pr[j];
                c[i][j]++;
                d[i][j]=d[i][j]*pr[j]%p;
                id[i][j]=id[i][j]*ipr[j]%p;
            }
        }
        b[i]=(i ? b[i-1]:1LL)*q%p;
        ib[i]=inv(b[i],p);
    }
}
 
inline int solve(int l, int r) {
    int fl=1; rep(j,m) {
        pwt[j]=c[r][j]-(l ? c[l-1][j]:0);
        if(pwt[j]<pw[j]) fl=0;
    }
    if(fl) return 0;
 
    ll ans=b[r]*(l ? ib[l-1]:1)%p;
    rep(j,m) {
        //ll ans1=1; while(pwt[j]--) ans1=ans1*pr[j]%p;
        //ans=ans*ans1%p;
        ans=ans*(d[r][j]*(l ? id[l-1][j]:1)%p)%p;
    }
    return ans;
}
 
int main() {
    ll t, q; scanf("%lld", &t);
    while(t--) {
        scanf("%lld%lld%lld", &n, &p, &q);
        rep(i,n) scanf("%lld", &a[i]);
        precalc();
        ll x=0, bp, bc, li, ri;
        scanf("%lld", &bc);
        rep(i,q) {
            if(i%64) {
                li = (li+x)%n;
                ri = (ri+x)%n;
            }
            else {
                bp = bc;
                scanf("%lld", &bc);
                li = (bp+x)%n;
                ri = (bc+x)%n;
            }
            if(li>ri) swap(li,ri);
            x = (solve(li,ri)+1)%p;
        }
        printf("%lld\n", x);
    }
    return 0;
}
