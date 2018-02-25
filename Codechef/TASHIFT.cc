/*
_prefix_array _kmp _string

O(n)
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
const int mod = 1e9 + 7, N = 2e6 + 10;

int n;
char s[N], t[N];

int pref[N];
void prefixarr() {
    // pref[i] denotes 'j' such that s[0..j-1] == s[i-j+1..i]
    int i = 0, j = 0;
    pref[i++] = 0;
    while(i < n)
        if(t[i] == t[j]) pref[i++] = ++j;
        else if(j) j = pref[j-1];
        else i++;
}
 
int kmp() {
    // finds list of occurrences of t in s
    int m = 2 * n, i, j;
    prefixarr();
    
    int maxlen(0), pos(0);
    i = j = 0;
    while(i < m) {
        if(s[i] == t[j]) i++, j++;
        else if(j > 0) j = pref[j-1];
        else i++;
        
        if(j > maxlen) maxlen = j, pos = i-j;
        if(j == n) break;//j = pref[j-1];
    }
    return pos;
}

int main() {
    scanf("%d %s %s", &n, t, s);
    rep(i,n) s[n + i] = s[i];
    printf("%d ", kmp());
    return 0;
} 
