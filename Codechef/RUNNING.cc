/*
_prefix_array _kmp

O(linear)
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
 
#define X first
#define Y second
#define rep(i,n) for(int i = 0, _n = (n); i < _n; i++)
#define rep1(i,a,b) for(int i = a, _b = (b); i <= _b; i++)
#define rep2(i,b,a) for(int i = b, _a = (a); i >= _a; i--)
#define mem(a,val) memset(a, (val), sizeof a)
#define mp make_pair
#define mt make_tuple // remember tie & ignore
#define eb emplace_back
#define all(c) (c).begin(), (c).end()
#define uni(c) c.resize(distance(c.begin(), unique(all(c))))
#define tr(c,it) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)
#define cases int __t; cin >> __t; rep1(_t,1,__t)
#define case(ans) "Case #" << _t << ": " << ans << "\n"
#define cout(d) cout << fixed << setprecision(d)
#define err(x) cerr << #x << " = " << x << '\n'
const int mod = 1e9 + 7, N = 1e6 + 10;
 
int pref[N];
template <typename T>
void prefixarr(T& s) {
    // pref[i] denotes 'j' such that s[0..j-1] == s[i-j+1..i]
    int i = 1, j = 0, n = s.size();
    rep(k,n) pref[k] = 0;
    while(i < n)
        if(s[i] == s[j]) pref[i++] = ++j;
        else if(j) j = pref[j-1];
        else i++;
}
 
template <typename T>
int kmp(T& s, T t) {
    // finds list of occurrences of t in s
    int m = s.size(), n = t.size(), i = 0, j = 0, occur = 0;
    prefixarr(t);
    
    while(i < m) {
        if(s[i] == t[j]) i++, j++;
        else if(j > 0) j = pref[j-1];
        else i++;
        
        if(j == n) occur++, j = pref[j-1];
    }
    return occur;
}
 
int main() {
    cases {
        int n, k; cin >> n >> k;
        vi a(n); rep(i,n) cin >> a[i];
        rep(i,n-1) a[i] = a[i+1] - a[i]; a.pop_back();
        
        vi b(k); rep(i,k) cin >> b[i];
        cout << kmp(a, b) << '\n';
    }
    return 0;
} 
