/*
_bit _inclusion-exclusion
O(4*q*logn) per test
*/
// g++ -std=c++11 -O2
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
const int N = 1e3 + 30;

ll bt[N][N], a[N][N], n;
inline void upd(int x, int y, ll val) {
    val-=a[x][y];
    a[x][y]+=val;
    x++, y++;
    for(int i=x; i<=n; i+=i&-i)
        for(int j=y; j<=n; j+=j&-j)
            bt[i][j]+=val;
}
inline ll sumh(int x, int y) {
    ll sum=0;
    for(int i=x; i>0; i^=i&-i)
        for(int j=y; j>0; j^=j&-j)
            sum+=bt[i][j];
    return sum;
}
inline ll sum(int x, int y, int X, int Y) {
    X++, Y++;
    return sumh(X,Y) - sumh(X,y) - sumh(x,Y) + sumh(x,y);
}

template <typename T = int>
inline void in(T&p) {
    p=0;register bool negative=false; register char ch=0;
    while(ch<0x30 or ch>0x39) {if(ch=='-') negative=true; ch=getchar();}
    while(ch>=0x30 and ch<=0x39) {p=(p<<1)+(p<<3)+(ch&15); ch=getchar();}
    if(negative) p=-p;
}
template <typename T>
inline void out(T n) {
    register char d[20],i=0;
    if(n < 0){putchar('-'); n = -n;}
    do{ d[i++] = (n%10)|0x30 ; n = n/10;} while(n);
    while(i) putchar(d[--i]);
    putchar('\n');
}

int main() {
    // string fname = "my";
    // freopen((fname+".in").c_str(), "r", stdin);
    // freopen((fname+".out").c_str(), "w", stdout);
    int q; in(q);
    while(q--) {
        in(n);
        rep(i,n+1)rep(j,n+1) a[i][j]=bt[i][j]=0;
        char s[4]; scanf("%s", s);
        while(s[0] != 'E') {
            if(s[1] == 'E') {
                int x, y, num;
                in(x), in(y), in(num);
                upd(x,y,num);
            }
            if(s[1] == 'U') {
                int x1, y1, x2, y2;
                in(x1), in(y1), in(x2), in(y2);
                out(sum(x1,y1,x2,y2));
            }
            scanf("%s", s);
        }
        putchar('\n');
    }
    return 0;
}
