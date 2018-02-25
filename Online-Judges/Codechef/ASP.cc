/*


O(linear)
*/
#include <cstdio>
#define rep(i,n) for(int i = 0, _n = (n); i < _n; i++)
const int N = 1e6 + 10;

inline void in(int&p) {
    p=0;register bool negative=false; register char ch=0;
    while(ch<0x30 or ch>0x39) {if(ch=='-') negative=true; ch=getchar();}
    while(ch>=0x30 and ch<=0x39) {p=(p<<1)+(p<<3)+(ch&15); ch=getchar();}
    if(negative) p=-p;
}

int n, a[N];
inline bool dis1(int i, int mi) {
    if(i > n-1) return true;
    if(a[i] < mi) return false;
    if(i > n-2) return true;
    if(a[i+1] < mi) return false;
    return dis1(i+1+(a[i]>a[i+1]), a[i]);
}

int main() {
    int q; in(q);
    while(q--) {
        in(n); rep(i,n) in(a[i]);
        if(dis1(0,0)) puts("YES");
        else puts("NO");
    }
}
