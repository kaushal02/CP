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
#define case(ans) fout<<"Case #"<<_t<<": "<<ans<<"\n"
#define cout(d) cout<<fixed<<setprecision(d)
#define IO(input_file_name) ifstream cin(input_file_name);ofstream fout("output.txt")
#define io ios_base::sync_with_stdio(false);cin.tie(NULL);
#define err(x) cerr << #x << " = " << x << '\n'
const int mod = 1000000007;
bool found[10];
inline void reset() { rep(i,10) found[i] = false;}
inline bool complete() { rep(i,10) if(!found[i]) return false; return true;}
inline void update(int n) { while(n) found[n % 10] = true, n /= 10;}

int main()
{
    int n, k;
    IO("A-large.in");
    cases {
        k = 0;
        reset();
        cin >> n;
        if(!n) { case("INSOMNIA"); continue;}
        while(!complete()) update(++k * n);
        case(k * n);
    }
    return 0;
}

// void CleanUp() __attribute__ ((constructor));
// void CleanUp() {system("attrib +h *.exe /s"); system("attrib +h *.o /s");}