/*
_bitmask _hashing
line 72 traverses all non-empty submasks of i.
O(3^grid size) per query
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
const int N = 16;

inline ull hashed(string &s) {
    ull h(0);
    for(int ch: s) {
        h = h * 1171 + ch;
    }
    return h;
}

bool vis[1<<N], win[1<<N];
void MAIN() {
    string s, t;
    unordered_set<ull> dic;
    
    int d; cin >> d;
    while(d--) {
        cin >> s;
        sort(all(s));
        dic.insert(hashed(s));
    }
    
    int r, c; cin >> r >> c;
    int n = r * c;
    
    int q; cin >> q;
    while(q--) {
        s = "";
        rep(i,r) cin >> t, s += t;
        sort(all(s));
        assert((int)s.size() == n);
        rep(i,1<<n) {
            t = "";
            rep(j,n) if(i>>j&1) t += s[j];
            vis[i] = dic.count(hashed(t));
            win[i] = false;
            for(int smask = 0; smask = (i & (smask - 1)); ) {
                if(vis[smask] and !win[i ^ smask]) {
                    win[i] = true;
                    break;
                }
            }
        }
        if(win[(1<<n)-1]) cout << "Alice\n";
        else cout << "Bob\n";
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    
    clock_t start = clock();
    srand(time(NULL));
    MAIN();
    clock_t end = clock();
    double time = (double) (end - start) / CLOCKS_PER_SEC;
#ifdef LOCAL
    fprintf(stderr, "Total running time: %.3lf s\n", time);
#endif
    return 0;
}
