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
#define IO(input_file_name) ifstream cin(input_file_name);ofstream fout("output.txt")
#define io ios_base::sync_with_stdio(false);cin.tie(NULL);
#define err(x) cerr << #x << " = " << x << '\n'
const int mod = 1000000007;

int main()
{
    IO("D-large.in");
    ll k, c, s, pos, mul, maxmul, check;
    cases {
        cin >> k >> c >> s;
        fout << "Case #" << _t << ": ";
        
        if(s * c < k) {fout << "IMPOSSIBLE\n"; continue;}
        
        maxmul = 1; rep(i,c - 1) maxmul *= k;
        pos = 0; while(pos < k) {
            check = 0;
            mul = maxmul;
            while(pos < k and mul) {
                check += pos * mul;
                pos++;
                mul /= k;
            }
            fout << check + 1 << " ";
        }
        fout << "\n";
    }
    return 0;
}

// void CleanUp() __attribute__ ((constructor));
// void CleanUp() {system("attrib +h *.exe /s"); system("attrib +h *.o /s");}