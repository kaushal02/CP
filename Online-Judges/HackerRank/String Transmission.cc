/*
_nCr _DP
https://www.hackerrank.com/challenges/string-transmission/problem

O(k*n*logn)
*/
// Time erodes gratitude more quickly than it does beauty!
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;

#define X first
#define Y second
#define rep(i,n) for(ll i=0; i<(n); i++)
#define rep1(i,a,b) for(ll i=a; i<=(b); i++)
#define rep2(i,b,a) for(ll i=b; i>=(a); i--)
#define mem(a,val) memset(a, (val), sizeof a)
#define mp make_pair
#define pb push_back
#define all(c) (c).begin(), (c).end()
#define uni(c) c.resize(distance(c.begin(), unique(all(c))))
#define fix(c,sz_val...) c.clear();c.resize(sz_val);
#define tr(c,it,ctype...) for(ctype::iterator it = c.begin(); it != c.end(); ++it)
#define io ios_base::sync_with_stdio(false);cin.tie(NULL)
#define IO(input_file_name) ifstream cin(input_file_name);ofstream cout("output.txt")
#define print(ans) cout<<"Case #"<<_t<<": "<<ans<<"\n"
const int mod = 1e9 + 7;

int n, k, a[1010], c[1010], result;
int f[1010];
map<int,int> m;

const int LIM = 1010;
int factorial[LIM];

inline int pwr(int _a, int _n) {
    int _ans(1);
    while(_n) {
        if(_n & 1) _ans = (ll)_ans * _a % mod;
        _n >>= 1;
        _a = (ll)_a * _a % mod;
    }
    return _ans;
}

inline int ncr(int _n, int _r) {
    if(_n < 0 || _r < 0 || _n < _r) return 0;
    return (ll)factorial[_n] * pwr((ll)factorial[_r] * factorial[_n-_r] % mod, mod-2) % mod;
}

inline void fac_fill() {
    factorial[0] = 1;
    rep(i,LIM) factorial[i] = (ll)factorial[i-1] * i % mod;
}

inline void resolve(int x) {
    /// x is the window's length, p being the number of such windows
    int p = n/x, pos[x];
    mem(c, 0);
    mem(pos, 0);
    
    rep(i,n) if(a[i]) pos[i%x]++;
    rep(i,x) pos[i] = min(pos[i], p-pos[i]);
    
    ++c[pos[0]];
    ++c[p-pos[0]];
    rep1(i,1,x-1)
        rep2(j,k,0)
            if(pos[i] == 0) {
                if(j + p <= k)
                    c[j+p] = (c[j+p] + c[j]) % mod;
            }
            else {
                if(j + pos[i] <= k)
                    c[j+pos[i]] = (c[j+pos[i]] + c[j]) % mod;
                if(j + p-pos[i] <= k)
                    c[j+p-pos[i]] = (c[j+p-pos[i]] + c[j]) % mod;
                c[j] = 0;
            }
    
    int val(0);
    rep1(i,0,k) val = (val + c[i]) % mod;
    
    tr(m, it, map<int,int>)
        if(x % it->X == 0)
            val = (val - it->Y + mod) % mod;
    m[x] = val;
    
    result = (result - val + mod) % mod;
}

int main() {
    fac_fill();
    string s;
    int t; cin >> t; while(t--) {
        cin >> n >> k >> s;
        rep(i,n) a[i] = s[i] - '0';
        
        result = 0;
        rep1(i,0,k) result = (result + ncr(n,i)) % mod;
        
        m.clear();
        rep1(i,1,n/2) if(n % i == 0) resolve(i);
        
        cout << result % mod << "\n";
    }
    return 0;
}