// Time erodes gratitude more quickly than it does beauty!
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;

#define X first
#define Y second
#define rep(i,n) for(int i=0, _n=(n); i<_n; i++)
#define rep1(i,a,b) for(int i=a,_b=(b); i<=_b; i++)
#define rep2(i,b,a) for(int i=b,_a=(a); i>=_a; i--)
#define mem(a,val) memset(a, (val), sizeof a)
#define mp make_pair
#define mt make_tuple
#define eb emplace_back
#define all(c) (c).begin(), (c).end()
#define uni(c) c.resize(distance(c.begin(), unique(all(c))))
#define fix(c,sz_val...) c.clear();c.resize(sz_val);
#define tr(c,it) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)
#define cases int t;cin>>t;rep1(_t,1,t)
#define case(ans) "Case #"<<_t<<": "<<ans<<"\n"
#define cout(d) cout<<fixed<<setprecision(d)
#define IO(i, o) ifstream cin(i);ofstream fout(o)
#define io ios_base::sync_with_stdio(false);cin.tie(NULL);
#define err(x) cerr << #x << " = " << x << '\n'
const int mod = 1e9 + 7;

int main() {
    IO("B-large.in","B-large.out");
    cases {
        ll b, m;
        cin >> b >> m;
        if(m > (1ll << b - 2)) fout << case("IMPOSSIBLE");
        else {
            fout << case("POSSIBLE");
            rep(i,b-1) {
                rep1(j,0,i) fout << 0;
                rep1(j,i+1,b-2) fout << 1;
                if((m == (1ll << b - 2)) || (i && ((m >> i - 1) & 1))) fout << 1;
                else fout << 0;
                fout << endl;
            }
            rep(i,b) fout << 0;
            fout << endl;
        }
    }
    return 0;
}