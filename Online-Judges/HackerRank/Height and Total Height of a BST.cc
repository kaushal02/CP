/*
_dfs _trie

https://www.hackerrank.com/contests/rookierank-4/challenges/height-and-total-height-of-a-bst/problem

O(n^2) worst-case when the input is fully skewed
*/
#include <bits/stdc++.h>
using namespace std;
#define int ll
typedef long long ll;
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

#define rep(i,n) for(ll i=0, _n=(n); i<_n; i++)
#define rep1(i,n) for(ll i=1, _n=(n); i<=_n; i++)
#define cout(d) cout << fixed << setprecision(d)
#define err(x) cerr << #x << " = " << x << "\n"

#define cases int _t_; cin >> _t_; rep1(_t,_t_)
#define coutt cout << "Case " << _t << ": "
#define io ios_base::sync_with_stdio (false); cin.tie(NULL);

const dbl eps=1e-12, pi=acosl(-1);
const ll inf=1e16, mod=1e9+7;
const int N=1e6+10;

struct node {
    int l, r, v;
    node(): l(0), r(0), v(-1) {};
};
node a[N];
int k=2;
void add(int x) {
    int c(1);
    while(true) {
        if(a[c].v==-1) {
            a[c].v = x;
            return;
        }
        else if(a[c].v>x) {
            if(!a[c].l) a[c].l = k++;
            c = a[c].l;
        }
        else if(a[c].v<x) {
            if(!a[c].r) a[c].r = k++;
            c = a[c].r;
        }
        else return;
    }
}
int sum;
int dfs(int x) {
    if(a[x].v==-1) return -1;
    int ret = 1 + max(dfs(a[x].l), dfs(a[x].r));
    sum += ret;
    return ret;
}

#undef int
int main() {
#define int ll

    int n; cin >> n;
    int x; while(n--) {
        cin >> x;
        add(x);
    }
    cout << dfs(1);
    cout << endl;
    cout << sum;
    return 0;
}