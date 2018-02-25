/*
_bitmask
Construction problem

O(t+n)
*/
// g++ -std=c++11 -O2 -fmax-errors=1
#include <bits/stdc++.h>
using namespace std;
 
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
const int N=2e6+10;
 
int ans[20], val[20];
inline int count(int mask, int n) {
    int ans=1;
    rep(i,n)rep(j,i) {
        int fl=1;
        int p=j, q=i;
        while(p<q) {
            if((mask>>p&1)^(mask>>q&1)) fl=0;
            p++, q--;
        }
        if(fl and ans<i-j+1) ans=i-j+1;
    }
    return ans;
}
int main() {
    rep1(l,10) {
        val[l]=mod;
        rep(i,1<<l) {
            int val2=count(i,l);
            if(val2<val[l]) {
                ans[l]=i;
                val[l]=val2;
            }
        }
    }
    string code="aabbab", coded="abc";
    cases {
        int n, a; cin >> n >> a;
        if(a<2) {
            cout << n << " ";
            rep(i,n) cout << 'a';
            cout << '\n';
        }
        else if(a>2) {
            cout << "1 ";
            rep(i,n) cout << coded[i%3];
            cout << '\n';
        }
        else {
            if(n<=10) {
                cout << val[n] << " ";
                rep(i,n) cout << (char)('a'+(ans[n]>>i&1));
                cout << '\n';
            }
            else {
                cout << "4 ";
                rep(i,n) cout << code[i%6];
                cout << '\n';
            }
        }
    }
    return 0;
}
