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
///.............................................................................///
ll c[100500] = {0}, s[100500] = {0}, n, a, b;

int main()
{
    io;
    IO("yachtzee_example_input.txt");
    int t;cin>>t;
    cout<<fixed<<setprecision(10);
    rep1(_t,1,t)
    {
        cin>>n>>a>>b;
        rep1(i,1,n)cin>>c[i];
        rep1(i,1,n)s[i]=s[i-1]+c[i];
        
        double x(0), y(0), z(0), xz(0), ans(0);
        ll one(a/s[n]), two(b/s[n]);
        ll low(upper_bound(s, s+n+1, a%s[n]) - s), up(upper_bound(s, s+n+1, b%s[n]) - s);
        
        if(one == two)
        {
            if(low == up)
                xz += ((double)one*s[n] + s[low-1])*(b - a);
            else
            {
                assert(low < up);
                xz += ((double)one*s[n] + s[low-1])*((double)one*s[n] + s[low] - a);
                rep1(it, low, up-2)
                    xz += (double)c[it+1]*((double)one*s[n] + s[it]);
                xz += ((double)one*s[n] + s[up-1])*(b - (double)one*s[n] - s[up-1]);
            }
            xz = (b*b - a*a)/2 - xz;
            
            ans = xz;
        }
        else
        {
            assert(one < two);
            x += ((double)one*s[n] + s[low-1])*((double)one*s[n] + s[low] - a);
            rep1(it, low, n-1)
                x += (double)c[it+1]*((double)one*s[n] + s[it]);
            x = (((double)(one+1)*s[n])*((double)(one+1)*s[n]) - a*a)/2 - x;
            
            y = (double)s[n]*s[n]/2;
            rep(i,n)
                y += (double)s[i]*c[i+1];
            y *= (two-one-1);
            
            rep1(it, 0, up-2)
                z += (double)c[it+1]*((double)two*s[n] + s[it]);
            z += ((double)two*s[n] + s[up-1])*(b - (double)two*s[n] - s[up-1]);
            z = (b*b - ((double)two*s[n])*((double)two*s[n]))/2 - z;
            
            ans = x+y+z;
        }
        
        ans /= (b-a);
        print(ans);
    }
    return 0;
}