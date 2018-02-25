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
#define IO(input_file_name) ifstream cin(input_file_name);ofstream cout("outpput.txt")
#define print(ans) cout<<"Case #"<<_t<<": "<<ans<<"\n"
const int mod = 1e9 + 7;
///.............................................................................///
ll l, n, m, d;
ll w[100100];

ll f(ll v) {
    ll ans(0);
    rep(i,n)ans += v/w[i];
    return ans;
}

int main()
{
    io;
    IO("q2i.txt");
    int t(50);cin>>t;
    rep1(_t,1,t)
    {
        cin>>l>>n>>m>>d;
        rep(i,n)cin>>w[i];
        
        ll mi(1), ma(1e16), v;
        while(mi < ma)
        {
            v = (mi+ma)/2;
            if(f(v) >= l)
                ma = v;
            else
                mi = v+1;
        }
        vector<ll> tm;
        rep(i,n)
        {
            ll temp(w[i]);
            while(temp <= mi)
            {
                tm.pb(temp);
                temp += w[i];
            }
        }
        sort(all(tm));
        ll ans1, ptr(l-1), cnt(1), ans(0);
        while(ptr >= 0)
        {
            ans1 = tm[ptr] + cnt*d;
            cnt++;
            ans = max(ans, ans1);
            ptr -= m;
        }
        print(ans);
    }
    return 0;
}