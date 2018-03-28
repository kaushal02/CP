#include <bits/stdc++.h>
using namespace std;
typedef long double dbl;
typedef pair<int,int> pii;
typedef vector<int> vi;

#define X first
#define Y second
#define pb push_back
#define not2 dfdsfgafes
#define all(c) begin(c), end(c)

#define rep(i,n) for(int i=0, _n=(n); i<_n; i++)
#define err(x) cerr << #x << ": " << x << "\n" << flush;
const int N=3e5+10;

vector<pii> pf[N];
int np, prime[N];
bool isp[N];
void setFactor(int p, int pMul) {
    int x=pMul, c=0;
    while(x%p==0) x/=p, c++;
    pf[pMul].pb({p,c});
}
void sieve(int N) {
    memset(isp, true, sizeof isp);
    isp[0] = isp[1] = false;
    for(int i=2; i<N; i++) if(isp[i]) {
        prime[++np]=i;
        setFactor(i,i);
        for(int j=2*i; j<N; j+=i) {
            isp[j]=false;
            setFactor(i,j);
        }
    }
}

pair<pii,int> qu[N];
int K, a[N], ans[N], c[N], not2, not3, neg, zeros;
inline void updFlags(int x, int y) {
    if((x&1) ^ (y&1)) {
        if(y&1) not2++;
        else not2--;
    }
    if((x%3==0) ^ (y%3==0)) {
        if(y%3) not3++;
        else not3--;
    }
}
inline void add(int i) {
    if(!a[i]) {
        zeros++;
        return;
    }
    for(pii f: pf[abs(a[i])]) {
        updFlags(c[f.X], c[f.X] + f.Y);
        c[f.X] += f.Y;
    }
    if(a[i]<0) neg^=1;
}
inline void rem(int i) {
    if(!a[i]) {
        zeros--;
        return;
    }
    for(pii f: pf[abs(a[i])]) {
        updFlags(c[f.X], c[f.X] - f.Y);
        c[f.X] -= f.Y; 
    }
    if(a[i]<0) neg^=1;
}
inline int getFlag() {
    if(zeros) return 3;
    return !neg*!not2 + 2*!not3;
}

int main() {
    sieve(N);

    int n, q; scanf("%d%d", &n, &q);
    rep(i,n) scanf("%d", a+i);
    K = q/sqrt(n);
    
    rep(i,q) {
        int x, y; scanf("%d%d", &x, &y);
        qu[i] = {{x-1,y-1},i};
    }
    sort(qu, qu+q, [&](pair<pii,int> l, pair<pii,int> r){
        if(l.X.X/K == r.X.X/K) return l.X.Y<r.X.Y;
        return l.X.X<r.X.X;
    });
    
    int curl=0, curr=-1, l, r;
    rep(i,q) {
        tie(l,r) = qu[i].X;
        while(curl>l) add(--curl);
        while(curr<r) add(++curr);
        while(curl<l) rem(curl++);
        while(curr>r) rem(curr--);
        ans[qu[i].Y] = getFlag();
    }
    rep(i,q) switch(ans[i]) {
        case 0: printf("None\n"); break;
        case 1: printf("Square\n"); break;
        case 2: printf("Cube\n"); break;
        case 3: printf("Both\n"); break;
        default: assert(0);
    }

    return 0;
}