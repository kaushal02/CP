/*
_sweep

Techgig Code Gladiators Semi-Finals 2018 Problem 1

O(n^2 * log n)
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long double dbl;
typedef pair<int,int> pii;
typedef vector<int> vi;

#define X first
#define Y second
#define mp make_pair
#define pb push_back
#define all(c) begin(c), end(c)
#define mem(c,v) memset(c, v, sizeof c)
#define uni(c) c.resize(distance(c.begin(), unique(all(c))))

#define rep(i,n) for(int i=0, _n=(n); i<_n; i++)
#define rep1(i,n) for(int i=1, _n=(n); i<=_n; i++)
#define cout(d) cout << fixed << setprecision(d)
#define err(x) cerr << #x << " = " << x << "\n"

#define cases int _t_; cin >> _t_; rep1(_t,_t_)
#define coutt cout << "Case " << _t << ": "
#define io ios_base::sync_with_stdio(false); cin.tie(NULL);

template <typename T> inline bool Max(T &a, T b) { return (a<b ? a=b,1:0);}
template <typename T> inline bool Min(T &a, T b) { return (a>b ? a=b,1:0);}

const dbl eps=1e-12, pi=acosl(-1);
const int inf=1e16, mod=1e9+7, N=2e6+10;



#undef int
int main() {
#define int long long

    int n; cin >> n;
    vector<pii> v;
    vi vx(n); rep(i,n) cin >> vx[i];
    vi vy(n); rep(i,n) cin >> vy[i];
    rep(i,n) v.pb({vy[i], -i-1});
    rep(i,n) v.pb({vy[i]+vx[i], i+1});
    sort(all(v));

    vi p; for(pii x: v) if(p.empty() or p.back() != x.X) p.pb(x.X);
    int vn=v.size(), pn=p.size();
    int ans=0, i, j;
    set<int> s1, s2;
    
    i=0; rep(l,pn) {
    	while(i<vn and v[i].X<p[l]) i++;
    	while(i<vn and v[i].X==p[l] and v[i].Y<0) s1.insert(-v[i++].Y);
    	
    	j=0; rep(r,pn) if(r>l) {
    		while(j<vn and v[j].X<p[r]) j++;
    		while(j<vn and v[j].X==p[r] and v[j].Y<0) s2.insert(-v[j++].Y);
    		Max(ans, (int)(s1.size()+s2.size()));

    		while(j<vn and v[j].X==p[r]) {
    			if(s2.count(v[j].Y)) s2.erase(v[j].Y);
    			j++;
    		}
    	}

    	while(i<vn and v[i].X==p[l]) s1.erase(v[i++].Y);
    }
    cout << ans;
    return 0;
}
