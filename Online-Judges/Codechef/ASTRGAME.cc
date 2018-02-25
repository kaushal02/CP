/*
_grundy

O(∑(n^4*log(n)))
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;

#define X first
#define Y second
#define mp make_pair
#define all(c) begin(c), end(c)
#define eb emplace_back // tie, ignore, get<i>(a)
#define mem(a,val) memset(a, (val), sizeof a)
#define uni(c) c.resize(distance(c.begin(), unique(all(c))))

#define rep(i,n) for(ll i = 0, _n = (n); i < _n; i++)
#define rep1(i,a,b) for(ll i = a, _b = (b); i <= _b; i++)
#define rep2(i,b,a) for(ll i = b, _a = (a); i >= _a; i--)

#define case(ans) "Case #" << _t << ": " << ans << "\n"
#define cout(d) cout << fixed << setprecision(d)
#define err(x) cerr << #x << " = " << x << '\n'

#define TTi template<typename T> inline

const ll inf = 1e16, mod = 1e9 + 7;
const double eps = 1e-16;
const int N = 1e5 + 10;

string s;
int dp[32][32];
unordered_set<string> st;
inline int grundy(int l, int r) {
    if(l > r) return 0;
    if(dp[l][r] + 1) return dp[l][r];
    
    set<int> mex;
    rep1(idx,l,r)rep1(len,1,r-idx+1) {
        if(st.count(s.substr(idx,len))) {
            mex.insert(grundy(l,idx-1) ^ grundy(idx+len,r));
        }
    }
    int ans(0);
    while(mex.count(ans)) ans++;
    return dp[l][r] = ans;
}

int main() {
    int q; cin >> q;
    while(q--) {
        cin >> s;
        st.clear();
        mem(dp, -1);
        int n; cin >> n;
        while(n--) {
            string t; cin >> t;
            st.insert(t);
        }
        if(grundy(0,(int)s.size()-1)) cout << "Teddy\n";
        else cout << "Tracy\n";
    }
    return 0;
}