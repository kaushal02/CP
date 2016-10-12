/*
_prefix_array _string

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
#define sz(c) (ll)c.size()
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
const int mod = 1e9 + 7, N = 4e6 + 10;

string s;
int pref[N], n;
void prefixarr() {
    // pref[i] denotes 'j' such that s[0..j-1] == s[i-j+1..i]
    rep(i,n) pref[i] = 0;
    int i = 0, j = 0;
    pref[i++] = 0;
    while(i < n)
        if(s[i] == s[j]) pref[i++] = ++j;
        else if(j) j = pref[j-1];
        else i++;
}
 
int main() {
    cin >> s;
    while(s != "End") {
        n = sz(s);
        prefixarr();
        rep(i,n) cout << pref[i] << " \n"[i==n-1];
        cin >> s;
    }
    return 0;
}
