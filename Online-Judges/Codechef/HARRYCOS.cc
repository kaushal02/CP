/*
2D _subarray _hashing

O(linear)
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
const int inf=1e16, N=2e3+10, K=2, mymod=1e9+7;
const int key[]={24976361, 911046887}, mod[]={mymod, mymod+2};
const int key2[]={2003, 24976361}, mod2[]={mymod+2, mymod};
 
int KEYX[K], KEY2X[K];
vector<pii> hm[2];
int a[2][N][N];
 
#undef int
int main() {
#define int long long
    io
    
    int n[2], m[2], x; cin >> n[0] >> m[0] >> n[1] >> m[1] >> x;
    rep(p,2)rep(i,n[p])rep(j,m[p]) cin >> a[p][i][j];
 
    rep(k,K) {
        KEYX[k]=KEY2X[k]=1;
        rep(i,x) KEYX[k]=KEYX[k]*key[k]%mod[k];
        rep(i,x) KEY2X[k]=KEY2X[k]*key2[k]%mod2[k];
    }
 
    rep(p,2) {
        int h[N][K]={};
        rep(j,m[p]) {
            int hs[K]={};
            rep(i,n[p]) {
                rep(k,K) {
                    h[i][k] = h[i][k]*key[k] + a[p][i][j] - (x>j ? 0:a[p][i][j-x])*KEYX[k];
                    h[i][k] = (h[i][k]%mod[k] + mod[k])%mod[k];
 
                    hs[k] = hs[k]*key2[k] + h[i][k] - (x>i ? 0:h[i-x][k])*KEY2X[k];
                    hs[k] = (hs[k]%mod2[k] + mod2[k])%mod2[k];
                }
                if(i>=x-1 and j>=x-1) hm[p].pb({hs[0], hs[1]});
            }
        }
    }
    
    sort(all(hm[0]));
    sort(all(hm[1]));
    int s1=hm[0].size();
    int s2=hm[1].size();
    int ans=0, i=0, j=0;
    while(i<s1 and j<s2) {
        int k=i; while(k<s1 and hm[0][k]==hm[0][i]) k++;
        while(j<s2 and hm[1][j]<hm[0][i]) j++;
        while(j<s2 and hm[1][j]==hm[0][i]) j++, ans += k-i;
        i=k;
    }
    cout << ans;
    return 0;
} 