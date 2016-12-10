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
const int N = 2e6 + 10;

template<class T>
struct bit2 {
    T **a, **bt; int n, m;
    bit2(int _n, int _m) {
        n=_n; m=_m;
        a=(T**)calloc(n+1,sizeof(T*));
        rep(i,n+1) a[i]=(T*)calloc(m+1,sizeof(T));
        bt=(T**)calloc(n+1,sizeof(T*));
        rep(i,n+1) bt[i]=(T*)calloc(m+1,sizeof(T));
    }
    void set(int x, int y, T v) {
        v-=a[x][y];
        a[x][y]+=v;
        x++;
        while(x<=n) {
            int yy=y; yy++;
            while(yy<=m) {
                bt[x][yy]+=v;
                yy+=yy&-yy;
            }
            x+=x&-x;
        }
    }
    T sumh(int x, int y) {
        T ans=0; x++;
        while(x) {
            int yy=y; yy++;
            while(yy) {
                ans+=bt[x][yy];
                yy^=yy&-yy;
            }
            x^=x&-x;
        }
        return ans;
    }
    T sum(int x1, int y1, int x2, int y2) {
        T ans=0; x1--, y1--;
        ans+=sumh(x2,y2);
        ans-=sumh(x2,y1);
        ans-=sumh(x1,y2);
        ans+=sumh(x1,y1);
        return ans;
    }
};

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
        int n; in(n);
        bit2<int> b(n,n);
        char s[4]; scanf("%s", s);
        while(s[0] != 'E') {
            if(s[1] == 'E') {
                int x, y, num;
                in(x), in(y), in(num);
                b.set(x,y,num);
            }
            if(s[1] == 'U') {
                int x1, y1, x2, y2;
                in(x1), in(y1), in(x2), in(y2);
                out(b.sum(x1,y1,x2,y2));
            }
            scanf("%s", s);
        }
        putchar('\n');
    }
    return 0;
}
