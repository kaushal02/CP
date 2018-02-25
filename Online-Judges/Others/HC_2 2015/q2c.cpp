///Nothing is more intolerable than to have to admit to yourself your own errors
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
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
#define io ios_base::sync_with_stdio(false);cin.tie(NULL)
#define IO(input_file_name) ifstream cin(input_file_name);ofstream cout("output.txt")
#define print(ans) cout<<"Case #"<<_t<<": "<<ans<<"\n"
const int mod = 1e9 + 7;
double eps = 1e-17;
///.............................................................................///
int n, k;
double p, q, rem;
double v[3500][3500], dp[3500];

int main()
{
    io;
    IO("in.txt");
    cout<<fixed<<setprecision(12);
    
    int t;cin>>t;
    rep1(_t,1,t)
    {
        cin>>n>>k>>p;
        q = 1-p;
        if(p < eps)
        {
            print(0);
            continue;
        }
        if(q < eps)
        {
            print(n/k);
            continue;
        }
        rep(j,k)v[0][j]=!j;
        rep1(i,1,n)
        {
            v[i][0] = 1;
            rep1(j,1,k)
                v[i][j] = q*v[i-1][j] + p*v[i-1][j-1];
        }
        
        rep(i,n+1)
        {
            dp[i] = v[i][k];
            rep(j,i)
                dp[i] = max(dp[i], dp[j]+dp[i-j]);
        }
        
        print(dp[n]);
    }
    return 0;
}