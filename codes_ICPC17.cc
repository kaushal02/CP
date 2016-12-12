#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;

#define X first
#define Y second
#define mp make_pair
#define pb push_back
#define all(c) begin(c), end(c)
#define con(i,a,b) a<=i and i<=b
#define uni(c) c.resize(distance(c.begin(), unique(all(c))))

#define rep(i,n) for(ll i=0, _n=(n); i<_n; i++)
#define rep1(i,n) for(ll i=1; _n=(n); i<=_n; i++)

#define cout(d) cout << fixed << setprecision(d)
#define err(x) cerr << #x << " = " << x << "\n"

const ll inf = 1e16, mod = 1e9 + 7;
const double eps = 1e-16;
const int N = 2e6 + 10;

int main() {
	
	return 0;
}
/***************************************************************/
int np(0), prime[N];
bool isprime[N];
void sieve(int N) {
	memset(isprime, true, sizeof isprime);
	for(int i=2; i<N; i++) {
		if(isprime[i]) {
			prime[++np] = i;
			for(int j=2*i; j<N; j+=i) {
				isprime[j] = false;
			}
		}
	}
}
inline ll mul(ll a, ll b, ll m) {
	ll q = ((long double)a * (long double)b) / (long double)m;
	ll r = a*b - q*m;
	return (r<0 ? r+m:r);
}
bool ispmiller(ll p) { // O(30*logp)
	if(p<2) return false;
	if(p==2) return true;
	if(p%2==0) return false;
	ll s=p-1; s>>=__builtin_ctzll(s);
	rep(i,30) {
		ll val=pwr(myrand(p-1)+1,s,p), temp=s;
		while(temp!=p-1 and con(val,2,p-2)) {
			val=mul(val,val,p);
			temp<<=1;
		}
		if(val!=p-1 and temp%2==0) return false;
	}
	return true;
}
inline ll pollardrho(ll n) { // O(n^0.25)
	if(n==1) return 1;
	if(n%2==0) return 2;
	ll c=myrand(n-1)+1, x=myrand(n-2)+2, y=x;
	ll d=1; while(d==1) {
		x=mul(x,x,n)+c; if(x>=n) x-=n;
		y=mul(y,y,n)+c; if(y>=n) y-=n;
		y=mul(y,y,n)+c; if(y>=n) y-=n;
		d=__gcd(abs(x-y),n);
		if(d==n) return (ispmiller(n) ? n:pollardrho(n));
	}
	return d;
}
/***************************************************************************/
struct dsu {
	vi par, sz;
	dsu(int n): par(n), sz(n), iota(all(par),0) {}
	int root(int a) { return par[a] == a ? a:par[a]=root(par[a]);}
	void merge(int a, int b) {
		a=root(a), b=root(b);
		if(a==b)return;
		if(sz[a]<sz[b])swap(a,b);
		sz[a]+=sz[b];
		par[b]=a;
	}
};
TTi struct dsu {
	map<T,T> par,sz;
	T root(T a) {
		if(par.find(a)==par.end() or par[a]==a) return par[a]=a;
		return par[a]=root(par[a]);
	}
	// same merge
}
/***************************************************************************/
const int M=2;
TTi void mul(T a[M][M], T b[M][M]) {
	T c[M][M];
	rep(i,M)rep(j,M) {
		ll temp=0;
		rep(k,M) temp += a[i][k]*b[k][j]%mod;
		c[i][j]=temp%mod;
	}
	rep(i,M)rep(j,M) a[i][j]=c[i][j];
}
TTi pwr(T a[M][M], ll n) {
	assert(n>=0);
	T temp[M][M];
	rep(i,M)rep(j,M) temp[i][j]=a[i][j], a[i][j]=i==j;
	while(n) {
		if(n&1) mul(a,temp);
		mul(temp,temp);
		n>>=1;
	}
}
/***************************************************************************/
TTi void in(T&p) {
	p=0;char neg=0,ch=0;
	while(ch<0x30 or ch>0x39) {if(ch=='-')neg=1; ch=getchar();}
	while(0x30<=ch and ch<=0x39) {p=(p<<1)+(p<<3)+(ch&15); ch=getchar();}
	if(neg)p=-p;
}
TTi void out(T n) {
	char d[20],i=0;
	if(n<0){putchar('-'); n=-n;}
	do{d[i++]=(n%10)|0x30; n/=10;} while(n);
	while(i) putchar(d[--i]);
	putchar('\n');
}
cin >> ws;//eat whitespaces
c = cin.peek();//get next character, maybe EOF
cin.putback(c); //put c in stream
/***************************************************************************/
inline int high(ll n) { return 63 - __builtin_clzll(n);} // location of highest set bit
#define pq(c) priority_queue<c,vector<c>,compare<c>>
TTi struct compare {
	bool operator()(const T& l, const T& r) const {
		return l.Y > r.Y;
	}
};
#define umap(key, val) unordered_map<key,val,hashed<key>>
TTi struct hashed {
	size_t operator()(T const& c) const {
		return c.X+231LL*c.Y;
	}
}

vi c(a, a+n); sort(all(c)); uni(c);
map<int,int> id;
int k(0); for(auto x: c) id[x]=k++;
/***************************************************************************/
inline int kth(int i, int j) {
	if(i==j) return a[i];
	int s(i), e(j), M(a[i+myrand(j-i+1)]);
	while(s<=e) {
		while(s<=j and a[s]<M) s++;
		while(e>=i and M<a[e]) e--;
		if(s<=e) swap(a[s++], a[e--]);
	}
	if(i<=e and k<=e) return kth(i,e);
	if(s<=j and s<=k) return kth(s,j);
	return M;
}
/***************************************************************************/
typedef pair<pii,int> node;
int K, a[N];
inline void add(int i) {}
inline void rem(int i) {}
int main() {
	int q; cin >> q; // query count
	K = q/sqrt(n);
	vector<node> qu(q);
	rep(i,q) {
		int x,y; cin>>x>>y;
		qu[i]={{x-1,y-1},i};
	}
	sort(all(qu),[](node l, node r){
		if(l.X.X/K==r.X.X/K) return l.X.Y<r.X.Y;
		return l.X.X<r.X.X;});
	vi ans(q);
	int curl(0), curr(-1), l, r;
	rep(i,q) {
		tie(l,r)=qu[i].X;
		while(curl>l) add(--curl);
		while(curr<r) add(++curr);
		while(curl<l) rem(curl++);
		while(curr>r) rem(curr--);
		ans[qu[i].Y]=getans();
	}}
/***************************************************************************/
ll fac[N], inv[N];
inline void init(int N) {
	fac[0]=1; rep1(i,N) fac[i]=fac[i-1]*i%mod;
	inv[N]=pwr(fac[N],mod-2);
	for(ll i=N; i>=1; i--) inv[i-1]=inv[i]*i%mod;
}
inline ll ncr(ll n, ll r) {
	if(n<0 or r<0 or n<r) return 0;
	return fac[n]*inv[r]%mod*inv[n-r]%mod;
}
/***************************************************************************/
182537		24976361	911046887	996955601
257		577		1009		2213
/***************************************************************************/
while(l<r) {
	//minimum ok..
	mid=l+r>>1;
	if(ok(mid)) r=mid;
	else l=mid+1;
	//maximum ok..
	mid=l+r+1>>1;
	if(ok(mid)) l=mid;
	else r=mid-1;
}
while(l<r) {
	if(f((l+l+r)/3) < f((l+r+r)/3)) l=(l+l+r)/3;
	else r=(l+r+r)/3;
}
/***************************************************************************/
const int K=25;
int n, a[N], lg[N], m[N][K];
inline void init() {
	lg[0]=-2;
	rep(i,n+1) lg[i]=1+lg[i>>1];
	rep(j,K) {
		if(!j) rep(i,n) { m[i][j]=a[i];}
		else rep(i,n-(1<<j)+1) { m[i][j]=min(m[i][j], m[i+(1<<j-1)][j-1]);}
	}
}
inline int rmq(int l, int r) {
	int k=lg[r-l+1];
	return min(m[l][k], m[r-(1<<k)+1][k]);
}
/***************************************************************************/
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
TTi using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
s.insert(x); s.erase(x); s.erase(s.lower_bound(x));
s.order_of_key(x); // 0-based index of least a[i] >= x
*s.find_by_order(i); // a[i]
/***************************************************************************/
// In main(), only initialize n, m, S, T, and call add() to build graph
const int V = 270;
const int E = V * V * 2;
const int INF = (int)1e9;

struct edge {
    int v, to, cap, flow;
};
int n, m, S, T;

edge ed[E];
int edSz;   //edSz=2*i for ith edge and 2*i+1 is its reverse   
vector<int> g[V];
int dist[V], idx[V], q[V];
int topQ;

void add(int v, int to, int cap) {
    g[v].pb(edSz);
    ed[edSz++] = {v,to,cap,0};
    g[to].pb(edSz);
    ed[edSz++] = {to,v,0,0};
}

bool bfs()
{
    rep(i,n) dist[i]=INF;
    dist[S] = 0;
    topQ = 1;
    q[0] = S;
    rep(k,topQ) {
        int v = q[k];
        for (int id : g[v])
        {
            edge e = ed[id];
            if (e.cap == e.flow) continue;
            int to = e.to;
            if (dist[to] <= dist[v] + 1) continue;
            dist[to] = dist[v] + 1;
            q[topQ++] = to;
        }
    }
    return dist[T] != INF;
}

int dfs(int v, int flow)
{
    if (v == T || flow == 0) return flow;
    int res = 0;
    for (int &i = idx[v]; i < (int)g[v].size(); i++)
    {
        int id = g[v][i];
        edge e = ed[id];
        int to = e.to;
        if (dist[to] != dist[v] + 1) continue;
        int df = dfs(to, min(flow, e.cap - e.flow));
        res += df;
        flow -= df;
        ed[id].flow += df;
        ed[id ^ 1].flow -= df;
        if (flow == 0) return res;
    }
    return res;
}
/***************************************************************************/
