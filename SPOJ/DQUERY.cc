/*
_MO

O(q*sqrt(n))
*/
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
#define print(ans) cout<<"Case #"<<_t<<": "<<ans<<"\n"
const int mod = 1e9 + 7, N = 1e6 + 10;
int k;

typedef pair<pair<int,int>,int> node;
int main() {
    int n; scanf(" %d", &n);
    vi a(n); rep(i,n) scanf(" %d", &a[i]);
    
    int t; scanf(" %d", &t);
    k = t / sqrt(n);
	vi ans(t);
    vector<node> q(t);
    
    rep(i,t) {
		scanf(" %d %d", &q[i].X.X, &q[i].X.Y);
		q[i].Y = i;
		q[i].X.X--;
		q[i].X.Y--;
	}
    sort(all(q), [](node l, node r) {
		if(l.X.X/k == r.X.X/k) return l.X.Y < r.X.Y;
    	else return l.X.X < r.X.X;});
    
    vi cur(N);
    int curl(q[0].X.X), curr(q[0].X.X-1), l, r, num(0);
    rep(i,t) {
        l = q[i].X.X;
        r = q[i].X.Y;
        while(curl < l)
            if(--cur[a[curl++]] == 0)
                --num;
        while(curl > l)
            if(cur[a[--curl]]++ == 0)
                ++num;
        while(curr < r)
            if(cur[a[++curr]]++ == 0)
                ++num;
        while(curr > r)
            if(--cur[a[curr--]] == 0)
                --num;
        ans[q[i].Y] = num;
    }
    rep(i,t) printf("%d\n", ans[i]);
    return 0;
}
