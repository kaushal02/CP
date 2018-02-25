/*
_BIT
Counting problem involving subarrays
https://www.hackerearth.com/problem/algorithm/good-subarrays/description/

O(n*log(n))
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

#define cout(d) cout << fixed << setprecision(d)
#define err(x) cerr << #x << " = " << x << '\n'
#define time() cerr << "clock = " << clock() << " ms\n"

const ll inf = 1e16, mod = 1e9 + 7;
const double eps = 1e-16;
const int N = 1e5 + 10;

template<class T>
struct bit {
    T *bt; int n;
    bit() {}
    bit(int n_):n(n_) { bt=(T*)calloc(n+1,sizeof(T));}
    void cons(int n_) { n = n_; bt=(T*)calloc(n+1,sizeof(T));}
    void reset() {memset(bt,0,sizeof(T)*(n+1));}
    void add(int u,T v=1) {u++;while(u<=n)bt[u]+=v,u+=u&-u;} // arr[u] += v
    T sum(int l,int r) {
        T ans=0;r++;
        while(r)ans+=bt[r],r^=r&-r;
        while(l)ans-=bt[l],l^=l&-l;
        return ans;
    } // arr[l]+..+arr[r]
};

ll a[N], l[N], r[N], b[N];
int main() {
    ll n, p; cin >> n >> p;
    rep(i,n) cin >> a[i];
    
    stack<ll> st;
    rep1(i,0,n-1) {
        while(!st.empty() and a[st.top()] < a[i]) { // soft right
            r[st.top()] = i - 1;
            st.pop();
        }
        st.push(i);
    }
    while(!st.empty()) {
        r[st.top()] = n - 1;
        st.pop();
    }
    rep2(i,n-1,0) {
        while(!st.empty() and a[st.top()] <= a[i]) { // hard left
            l[st.top()] = i + 1;
            st.pop();
        }
        st.push(i);
    }
    while(!st.empty()) {
        l[st.top()] = 0;
        st.pop();
    }
    
    ll tot(0), lt(0), rt(-1);
    while(lt < n) {
        while(rt + 1 < n and tot + a[rt+1] <= p) {
            tot += a[++rt];
        }
        b[lt] = rt;
        tot -= a[lt++];
    }
  	
    bit<ll> bt(n); rep(i,n) bt.add(i,b[i]);
    map<ll,ll> mp;
    rep(i,n) {
        if(a[i] > p) continue;
        ll j, k, ans1;
        lt = l[i], rt = i;
        while(lt < rt) {
            j = (lt + rt) / 2;
            if(b[j] >= i) rt = j;
            else lt = j + 1;
        } j = lt;
        lt = l[i], rt = i;
        while(lt < rt) {
            k = (lt + rt + 1) / 2;
            if(b[k] <= r[i]) lt = k;
            else rt = k - 1;
        } k = lt;
        if(b[k] > r[i]) ans1 = (r[i]-i+1)*(i-j+1);
        else ans1 = bt.sum(j,k) - (i-1)*(k-j+1) + (i-k)*(r[i]-i+1);
        mp[a[i]] += ans1;
    }
    
    ll ans(-1), cnt(0);
    for(auto ele: mp) if(ele.Y >= cnt) tie(ans,cnt) = ele;
    cout << ans << '\n';
    
    // for(auto ele: mp) cout << ele.X << " occurs " << ele.Y << " times\n";
    return 0;
}
