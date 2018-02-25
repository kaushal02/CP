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
///.............................................................................///
int a[100500];

int main()
{
    io;
 //   IO("q1i.txt");
    int t;cin>>t;
    rep1(_t,1,t)
    {
        int n;cin>>n;
        rep(i,n)cin>>a[i];
        int ans(0), req(3);
        rep(i,n)
        {
            if(i+1 == n)
            {
                ans += req;
                break;
            }
            if(req == 0)
            {
                req = 3;
                continue;
            }
            if(a[i+1] <= a[i] || a[i+1] > a[i] + 10*req)
            {
                ans += req;
                req = 3;
                continue;
            }
            if(a[i+1] <= a[i] + 10)
            {
                req--;
                continue;
            }
            if(a[i+1] <= a[i] + 20)
            {
                ans += 1;
                req -= 2;
                continue;
            }
            if(a[i+1] <= a[i] + 30)
            {
                ans += 2;
                req -= 3;
                continue;
            }
        }
        print(ans);
    }
    return 0;
}