/*
multiple _RMQ

O(n*log(n) + q)
*/

#include <cstdio>
#define rep(i,n) for(int i = 0, _n = (n); i < _n; i++)
const int N = 1e5 + 10, K = 20;
inline int min(int a, int b) { if(a < b) return a; return b;}
inline int max(int a, int b) { if(a > b) return a; return b;}

int n, a[N], lg[N], m[N][K], M[N][K];
inline void init() {
    lg[0] = -2;
    rep(i,n+1) lg[i] = 1 + lg[i>>1];
    rep(j,K) {
        if(!j) {
            rep(i,n) {
                m[i][j] = a[i];
                M[i][j] = a[i];
            }
        }
        else {
            rep(i,n-(1<<j)+1) {
                m[i][j] = min(m[i][j-1], m[i+(1<<j-1)][j-1]);
                M[i][j] = max(M[i][j-1], M[i+(1<<j-1)][j-1]);
            }
        }
    }
}
inline int rmq(int l, int r) {
    if(l > r) return 0xf7f7f7f;
    int k = lg[r-l+1];
    return min(m[l][k], m[r-(1<<k)+1][k]);
}
inline int rMq(int l, int r) {
    if(l > r) return 0;
    int k = lg[r-l+1];
    return max(M[l][k], M[r-(1<<k)+1][k]);
}

int main() {
    scanf("%d", &n);
    rep(i,n) scanf("%d", a + i);
    init();
    
    int q;
    scanf("%d", &q);
    int l, r, extra;
    while(q--) {
        scanf("%d%d", &l, &r);
        extra = max((rMq(l,r) - rmq(l,r)), max(rMq(0,l-1), rMq(r+1,n-1)) << 1);
        if(extra & 1) printf("%d.5\n", rmq(l,r) + (extra >> 1));
        else printf("%d.0\n", rmq(l,r) + (extra >> 1));
    }
}
