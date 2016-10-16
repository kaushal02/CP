/*
_graph _euler_path _dsu

http://codeforces.com/contest/508/problem/D
O(input size)
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

const ll inf = 1e16, mod = 1e9 + 7;
const double eps = 1e-16;
const int N = 5e3 + 10;

struct dsu {
    vi par, sz;
    dsu(int n): par(n), sz(n) { rep(i,n) par[i] = i, sz[i] = 1;}
    int root(int a) { return a == par[a] ? a : par[a] = root(par[a]);}
    void merge(int a, int b) {
        a = root(a);
        b = root(b);
        if(a == b) return;
        if(sz[a] < sz[b]) swap(a,b);
        
        sz[a] += sz[b];
        par[b] = a;
    }
};

inline void imp() {
    cout << "NO\n";
    exit(0);
}

inline int f(char c) {
    if(isupper(c)) return c - 'A';
    if(islower(c)) return c - 'a' + 26;
    if(isdigit(c)) return c - '0' + 52;
    assert(0);
}
inline char g(int n) {
    if(n < 26) return n + 'A';
    if(n < 52) return n - 26 + 'a';
    if(n < 62) return n - 52 + '0';
    assert(0);
}

vi revt[N], vec;
int in[N], out[N], it[N];
inline void dfs(int v) {
    while(it[v] < in[v]) {
        int x = it[v]++;
        dfs(revt[v][x]);
        vec.eb(revt[v][x]);
    }
}

int main() {    
    int n; cin >> n;
    dsu d(N);
    rep(i,n) {
        string s; cin >> s;
        int u = f(s[0]) * 70 + f(s[1]);
        int v = f(s[1]) * 70 + f(s[2]);
        out[u]++; in[v]++;
        revt[v].eb(u);
        d.merge(u, v);
    }
    rep(i,N) assert(in[i] == revt[i].size());
    
    int comp = 0;
    rep(i,N) if(d.root(i) == i) comp += (in[i] or out[i]);
    if(comp > 1) imp();
    assert(comp == 1);
    
    int ini = -1, fin = -1;
    rep(i,N) {
        if(in[i] + 1 == out[i]) {
            if(ini + 1) imp();
            ini = i;
        }
        else if(in[i] == out[i] + 1) {
            if(fin + 1) imp();
            fin = i;
        }
        else if(in[i] != out[i]) imp();
    }
    if(fin == -1) {
        fin = 0; while(!in[fin]) fin++;
    }
    
    dfs(fin);
    vec.eb(fin);
    
    cout << "YES\n" << g(vec.front()/70);
    for(auto x: vec) cout << g(x%70);
    
    return 0;
}
