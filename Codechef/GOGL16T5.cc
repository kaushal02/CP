/*
_offline _bit

O(nlogn + qlogq)
*/

#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
 
#define X first
#define Y second
#define mp make_pair
#define all(c) begin(c), end(c)
#define con(i,a,b) a<=i and i<=b
#define uni(c) c.resize(distance(c.begin(), unique(all(c))))
 
#define rep(i,n) for(ll i=0, _n=(n); i<_n; i++)
#define rep1(i,n) for(ll i=1, _n=(n); i<=_n; i++)
 
#define cout(d) cout << fixed << setprecision(d)
#define err(x) cerr << #x << " = " << x << "\n"
 
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
 
int a[N], ans[N];
pii va[N];
pair<pii,pii> qu[N];
int main() {
	// string fname = "my";
	// freopen((fname+".in").c_str(), "r", stdin);
	// freopen((fname+".out").c_str(), "w", stdout);
	int n, q; cin >> n >> q;
	rep(i,n) {
		cin >> a[i];
		va[i] = {a[i],i};
	}
	sort(va, va+n);
	rep(i,q) {
		int l, r, x;
		cin >> l >> r >> x;
		qu[i] = {{x,i},{l-1,r-1}};
	}
	sort(qu, qu+q);
 
	bit<int> b(n);
	int i(0), j(0);
	while(j<q) {
		while(i<n and va[i].X < qu[j].X.X) {
			b.add(va[i++].Y);
		}
		ans[qu[j].X.Y] = b.sum(qu[j].Y.X,qu[j].Y.Y);
		j++;
	}
	rep(i,q) cout << ans[i] << '\n';
	return 0;
}
