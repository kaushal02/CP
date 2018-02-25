/*
_hashing _suffix_array
https://www.hackerrank.com/contests/university-codesprint-4/challenges/maximum-permutation

O(n*(26+log^2(n)))
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
const int inf=1e16, mod=1e9+7, M=2e4+10, N=2e5+10;
const int key[]={257,997,182537}, diV[]={mod,mod+2,911046887};
int pkey[3][N], has[3][N];

inline vi hasH(int i, int m) {
    vi ans; rep(k,3) {
        int val = (has[k][i]-(i-m<0? 0:has[k][i-m])*pkey[k][m])%diV[k];
        if(val<0) val += diV[k];
        ans.pb(val);
    }
    return ans;
}

inline bool eq(int a[], int b[], int n) {
    rep(i,n) if(a[i]!=b[i]) return false;
    return true;
}

int suff[N], srank[N];
inline void suffixarr(string &s) {
    // srank[i] denotes the rank of s[i..end]
    // suff[i] denotes id such that s[id..end] is i'th best suffix
    int n = s.size(), lvl(20); // increase lvl if size > 1e6
    vector<pair<pii,int>> id(n);
    vi ranks[lvl]; rep(i,lvl) ranks[i].reserve(n);
    
    rep(i,n) ranks[0][i] = s[i];
    for(int len=1, cur=1; len<n; len<<=1, cur++) {
        rep(i,n) {
            id[i].X.X = ranks[cur-1][i];
            id[i].X.Y = (i+len<n ? ranks[cur-1][i+len]:-1);
            id[i].Y = i;
        }
        sort(all(id));
        
        int rk(0);
        ranks[cur][id[0].Y] = rk;
        rep(i,n) if(i) {
            if(id[i].X > id[i-1].X) rk++;
            ranks[cur][id[i].Y] = rk;
        }
    }
    rep(i,n) suff[i] = id[i].Y;
    rep(i,n) srank[suff[i]] = i;
}

#undef int
int main() {
#define int long long
    rep(k,3)rep(i,M) pkey[k][i]=(i? pkey[k][i-1]*key[k]%diV[k]:1);    
    cases {
        string w, s; cin >> w >> s;
        int m=w.size(), n=s.size();
        rep(k,3)rep(i,n) has[k][i]=((i? has[k][i-1]:0)*key[k]+s[i])%diV[k];
        
        map<vi,vi> loc;
        int c[26]={}; for(char ch: w) c[ch-'a']++;
        int d[26]={}; rep(i,n) {
            d[s[i]-'a']++;
            if(i>=m) d[s[i-m]-'a']--;
            if(eq(c,d,26)) loc[hasH(i,m)].pb(i-m+1);
        }
        
        int maxocc=0; for(auto &foo: loc) maxocc=max(maxocc, (int)foo.Y.size());
        if(!maxocc) {cout << "-1\n"; continue;}
        vi can; for(auto foo: loc) if(foo.Y.size()==maxocc) can.pb(foo.Y.back());

        int ilexmin=can[0]; suffixarr(s);
        for(int i: can) if(srank[ilexmin]>srank[i]) ilexmin=i;
        cout << s.substr(ilexmin, m) << '\n';
    }
    return 0;
}
