/*
_BIT _hashing
[SPOJ] http://www.spoj.com/problems/MCHAOS/

O(IlogI) where I is input length
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
const int N = 1e5 + 10;

string s[N], rs[N];
int x[N], y[N];
pii a[N];

ll bt[N], nb;
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

int main() {
    int n; cin >> n;
    rep(i,n) cin >> s[i];
    rep(i,n) rs[i] = s[i], reverse(all(rs[i]));

    vector<string> v(n); rep(i,n) v[i]=s[i];
    sort(all(v)); uni(v);
    map<string,int> ids;
    int k(0); for(string s: v) ids[s]=k++;

    vector<string> w(n); rep(i,n) w[i]=rs[i];
    sort(all(w)); uni(w);
    map<string,int> idrs;
    int l(0); for(string s: w) idrs[s]=l++;

    rep(i,n) a[i]={ids[s[i]], idrs[rs[i]]};
    sort(a, a+n);
    nb=l;
    ll ans(0);
    rep(i,n) {
        ans+=sum(a[i].Y+1,nb-1);
        add(a[i].Y);
    }
    cout << ans << '\n';
    return 0;
}
