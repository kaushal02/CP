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
stack<pii> st;
vector<pii> v;
int ans;

void add(int lim)
{
    int s, ss, cnt, val, ans1;
    while(!st.empty() && st.top().Y < lim)
    {
        s = 0;
        ss = 0;
        cnt = 0;
        val = st.top().Y;
        while(!st.empty() && st.top().Y == val)
        {
            ++cnt;
            s = (s + st.top().X) % mod;
            ss = (ss + (ll)st.top().X * st.top().X) % mod;
            st.pop();
        }
        ans1 = ((ll)cnt * ss - (ll)s * s) % mod;
        ans += ans1;
        ans %= mod;
        if(ans < 0) ans += mod;
    }
}

int main()
{
    io;
    IO("snakes_and_ladders.txt");
    int t;cin>>t;
    rep1(_t,1,t)
    {
        ans = 0;
        
        int n;cin>>n;
        fix(v, n);
        rep(i,n)cin>>v[i].X>>v[i].Y;///position and height
        sort(all(v));
        
        int cur(0);
        while(cur < n)
        {
            add(v[cur].Y);
            st.push(v[cur++]);
        }
        add(mod);
        assert(st.empty());
        
        print(ans);
    }
    return 0;
}