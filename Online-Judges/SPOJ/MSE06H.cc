/*
_BIT

O(k*log(max(k,n,m)))
*/
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
const int N = 1e3 + 10;

template <typename T = int>
inline void in(T&p) {
    p=0;register bool negative=false; register char ch=0;
    while(ch<0x30 or ch>0x39) {if(ch=='-') negative=true; ch=getchar();}
    while(ch>=0x30 and ch<=0x39) {p=(p<<1)+(p<<3)+(ch&15); ch=getchar();}
    if(negative) p=-p;
}

string s[N], rs[N];
int x[N], y[N];
pii a[N*N];

ll bt[N], nb=N;
inline void add(int x, ll val=1) {
    x++;
    for(int i=x; i<=nb; i+=i&-i)
        bt[i]+=val;
}
inline ll sumh(int x) {
    ll sum=0;
    for(int i=x; i>0; i^=i&-i)
        sum+=bt[i];
    return sum;
}
inline ll sum(int x, int X) {
    X++;
    return sumh(X) - sumh(x);
}

void solve(int kase) {
    memset(bt, 0, sizeof bt);
    int n, m, k; in(n), in(m), in(k);
    rep(i,k) in(a[i].X), in(a[i].Y);
    sort(a, a+k);
    
    ll ans(0);
    rep(i,k) {
        ans+=sum(a[i].Y+1,nb-1);
        add(a[i].Y);
    }
    cout << "Test case " << kase << ": " << ans << '\n';
}

int main() {
    int t; in(t);
    rep1(i,t) solve(i);
    return 0;
}
