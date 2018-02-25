/*
_hashing _palindrome _string

O(input size)
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
#define rep(i,n) for(int i = 0, _n = (n); i != _n; i++)
#define rep1(i,a,b) for(int i = a, _b = (b); i <= _b; i++)
#define rep2(i,b,a) for(int i = b, _a = (a); i >= _a; i--)
#define mem(a,val) memset(a, (val), sizeof a)
#define mp make_pair
#define mt make_tuple // remember tie & ignore
#define eb emplace_back
#define all(c) (c).begin(), (c).end()
#define uni(c) c.resize(distance(c.begin(), unique(all(c))))
#define cases int __t; cin >> __t; rep1(_t,1,__t)
#define case(ans) "Case #" << _t << ": " << ans << "\n"
#define cout(d) cout << fixed << setprecision(d)
#define err(x) cerr << #x << " = " << x << '\n'
typedef unsigned long long ull;
const int N = 1e5 + 10;
template <typename T = int>
inline void in(T&p) {
    p=0;register bool negative=false; register char ch=0;
    while(ch<0x30 or ch>0x39) {if(ch=='-') negative=true; ch=getchar();}
    while(ch>=0x30 and ch<=0x39) {p=(p<<1)+(p<<3)+(ch&15); ch=getchar();}
    if(negative) p=-p;
}
 
int n;
ull fwd[N], bck[N], p[N], key = 1129;
inline ull fhash(int i, int j) {
    if(i == 0) return fwd[j];
    return fwd[j] - fwd[i-1] * p[j-i+1];
}
inline ull bhash(int i, int j) {
    if(j == n-1) return bck[i];
    return bck[i] - bck[j+1] * p[j-i+1];
}
inline string solve() {
    register ull fwd_, bck_;
    register int i, j, k, l;
    in(i), in(j), in(k), in(l);
    i--, j--, k--, l--;
    
    if(j < k) {
        fwd_ = fhash(k, l);
        bck_ = bhash(k, l);
    }
    if(i <= k and k <= j and j < l) {
        fwd_ = fhash(j+1, l) + p[l-j] * bhash(i, i+j-k);
        bck_ = fhash(i, i+j-k) + p[j-k+1] * bhash(j+1, l);
    }
    if(i <= k and l <= j) {
        fwd_ = fhash(i+j-l, i+j-k);
        bck_ = bhash(i+j-l, i+j-k);
    }
    if(k < i and i <= l and l <= j) {
        fwd_ = bhash(i+j-l, j) + p[l-i+1] * fhash(k, i-1);
        bck_ = bhash(k, i-1) + p[i-k] * fhash(i+j-l, j);
    }
    if(l < i) {
        fwd_ = fhash(k, l);
        bck_ = bhash(k, l);
    }
    
    return (fwd_ == bck_ ? "Yes\n":"No\n");
}
 
int main() {
    string s; cin >> s; n = s.size();
    p[0] = 1; rep1(i,1,n) p[i] = p[i-1] * key;
    fwd[0] = s[0]; rep1(i,1,n-1) fwd[i] = fwd[i-1] * key + s[i];
    bck[n-1] = s[n-1]; rep2(i,n-2,0) bck[i] = bck[i+1] * key + s[i];
    
    cases cout << solve();
    return 0;
} 
