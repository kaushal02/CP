/*
_BIT _inclusion_exclusion

O(8*q*logn)
*/
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
#define rep1(i,n) for(ll i=1, _n=(n); i<=_n; i++)

#define cout(d) cout << fixed << setprecision(d)
#define err(x) cerr << #x << " = " << x << "\n"

const ll inf = 1e16, mod = 1e9 + 7;
const double eps = 1e-16;
const int N = 100 + 10;

ll bt[N][N][N], tot, n;
void add(int x, int y, int z, ll val) {
    x++, y++, z++;
    for(int i=x; i<=n; i+=i&-i)
        for(int j=y; j<=n; j+=j&-j)
            for(int k=z; k<=n; k+=k&-k)
                bt[i][j][k]+=val;
}
ll sumh(int x, int y, int z) {
    ll sum=0;
    for(int i=x; i>0; i^=i&-i)
        for(int j=y; j>0; j^=j&-j)
            for(int k=z; k>0; k^=k&-k)
                sum+=bt[i][j][k];
    return sum;
}
ll sum(int x, int y, int z, int X, int Y, int Z) {
    X++, Y++, Z++;
    return sumh(X,Y,Z) - sumh(X,Y,z) - sumh(X,y,Z) - sumh(x,Y,Z) +\
     sumh(x,y,Z) + sumh(x,Y,z) + sumh(X,y,z) - sumh(x,y,z);
}

int main() {
    int q; cin >> n >> q; n++;
    while(q--) {
        int type; cin >> type;
        int x, y, z; cin >> x >> y >> z;
        if(type==1) {
            ll val; cin >> val;
            add(x,y,z,val); tot+=val;
        }
        if(type==2) {
            int X, Y, Z; cin >> X >> Y >> Z;
            cout << tot-sum(x,y,z,X,Y,Z) << '\n';
        }
    }
    return 0;
}
