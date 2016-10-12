/*
lazy ; segment tree

O(q*log(n))
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
 
#define X first
#define Y second
#define rep(i,n) for(int i = 0, _n = (n); i < _n; i++)
#define rep1(i,a,b) for(int i = a, _b = (b); i <= _b; i++)
#define rep2(i,b,a) for(int i = b, _a = (a); i >= _a; i--)
#define mem(a,val) memset(a, (val), sizeof a)
#define mp make_pair
#define mt make_tuple // remember tie & ignore
#define eb emplace_back
#define all(c) (c).begin(), (c).end()
#define uni(c) c.resize(distance(c.begin(), unique(all(c))))
#define tr(c,it) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)
#define cases int __t; cin >> __t; rep1(_t,1,__t)
#define case(ans) "Case #" << _t << ": " << ans << "\n"
#define cout(d) cout << fixed << setprecision(d)
#define err(x) cerr << #x << " = " << x << '\n'
const int mod = 1e9 + 7, N = 10 + 1e5;

typedef int nod;
nod n, arr[N];
nod tree[N << 2], lazy[N << 2];

void build(int node = 1, int a = 0, int b = n-1) {
    if(a > b) return;
  	if(a == b) {lazy[node] = tree[node] = arr[a]; return;} // modify
	build(node<<1, a, a+b>>1); 
	build(node<<1|1, a+b+2>>1, b);
	tree[node] = min(tree[node<<1], tree[node<<1|1]);
	lazy[node] = lazy[node<<1] | lazy[node<<1|1];
}
void update(int i = 0, int j = n-1, int value = INT_MAX, int node = 1, int a = 0, int b = n-1) {
    if(!(lazy[node] & ~value)) return;
    if(a > b || b < i || j < a) return;
    if(a == b) {
        tree[node] &= value;
        lazy[node] &= value;
        return;
    }
    update(i, j, value, node<<1, a, a+b>>1);
	update(i, j, value, node<<1|1, a+b+2>>1, b);
    tree[node] = min(tree[node<<1], tree[node<<1|1]);
    lazy[node] = lazy[node<<1] | lazy[node<<1|1];
}
nod query(int i = 0, int j = n-1, int node = 1, int a = 0, int b = n-1) {
	if(a > b || b < i || j < a) return INT_MAX;
    if(i <= a && b <= j) return tree[node];
    nod q1 = query(i, j, node<<1, a, a+b>>1); 
	nod q2 = query(i, j, node<<1|1, a+b+2>>1, b);
	return min(q1, q2);
}
 
int main() {
    int q; cin >> n >> q;
    rep(i,n) cin >> arr[i];
    build();
    
    int type, l, r;
    rep(i,q) {
        cin >> type >> l >> r;
        if(!type) cout << query(l-1, r-1) << endl;
        else cin >> type, update(l-1, r-1, type);
    }
    return 0;
}
