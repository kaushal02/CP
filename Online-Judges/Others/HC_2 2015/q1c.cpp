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

int main()
{
    io;
    IO("boomerang_decoration.txt");
    string a,b;
    int t;cin>>t;
    rep1(_t,1,t)
    {
        int n;cin>>n;
        cin>>a>>b;
        vi pre(n), suf(n), p(n), s(n);
        
        pre[0]=1;
        rep1(i,1,n-1)if(b[i]!=b[i-1])pre[i]=pre[i-1]+1;else pre[i]=pre[i-1];
        suf[n-1]=1;
        rep2(i,n-2,0)if(b[i]!=b[i+1])suf[i]=suf[i+1]+1;else suf[i]=suf[i+1];
        
        p[0] = (a[0] != b[0]);
        rep1(i,1,n-1)
            if(a[i] == b[i])
                p[i] = p[i-1];
            else
                p[i] = pre[i];
        
        s[n-1] = (a[n-1] != b[n-1]);
        rep2(i,n-2,0)
            if(a[i] == b[i])
                s[i] = s[i+1];
            else
                s[i] = suf[i];
        
        int ans(1e8);
        rep1(i,0,n-2)
            ans = min(ans, max(p[i], s[i+1]));
        ans = min(ans, p[n-1]);
        ans = min(ans, s[0]);
        print(ans);
    }
    return 0;
}