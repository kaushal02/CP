/*
_FFT _sieve

https://icpc.kattis.com/problems/tiles

O(L * (n + log L)) where L = 5E5 is the limit on a_hi
*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
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

#define rep(i,n) for(int i=0, _n=(n); i<_n; i++)
#define rep1(i,n) for(int i=1, _n=(n); i<=_n; i++)
#define cout(d) cout << fixed << setprecision(d)
#define err(x) cerr << #x << " = " << x << "\n"

#define cases int _t_; cin >> _t_; rep1(_t,_t_)
#define coutt cout << "Case #" << _t << ": "
#define io ios_base::sync_with_stdio(false); cin.tie(NULL);

template <typename T> inline bool Max(T &a, T b) { return (a<b ? a=b,1:0);}
template <typename T> inline bool Min(T &a, T b) { return (a>b ? a=b,1:0);}

const dbl eps=1e-12, pi=acosl(-1);
const int inf=1e16, mod=1e9+7, N=5e5+10;

typedef complex<dbl> cpx;
const int W = 1 << 20;
cpx pw[W][2];
void init() {
    for (int i = 0; i < W; i++) {
        dbl ang = i * 2 * pi / W;
        pw[i][0] = cpx(cos(ang), sin(ang));
        pw[i][1] = cpx(cos(-ang), sin(-ang));
    }
}
void fft(vector<cpx>& a, bool inv = false) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        while (j >= bit) {
            j -= bit;
            bit >>= 1;
        }
        j += bit;
        if(i < j) {
            swap(a[i], a[j]);
        }
    }
    for(int len = 2, shift = W >> 1; len <= n; len <<= 1, shift >>= 1) {
        int len2 = len >> 1;
        for (int i = 0; i < n; i += len) {
            for (int j = 0; j < len2; j++) {
                cpx u = a[i + j], v = a[i + j + len2] * pw[j * shift][inv];
                a[i + j] = u + v;
                a[i + j + len2] = u - v;
            }
        }
    }
    if (inv) {
        for (int i = n; i--; ) {
            a[i] /= n;
        }
    }
}
vector<int> multiply(vector<int> a, vector<int> b) {
    vector<cpx> fa(all(a)), fb(all(b));
    
    int n = 1;
    while (n < max(a.size(), b.size())) {
        n <<= 1;
    }
    n <<= 1;
    fa.resize(n), fb.resize(n);
    fft(fa), fft(fb);

    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
    }
    fft(fa, true);
    
    vector<int> res(n);
    for (int i = 0; i < n; i++) {
        res[i] = fa[i].real() + 0.5;
    }
    return res;
}



signed main() {
    init();
    
    vector<int> divcount(N, 1);
    divcount[0] = 0;
    for (int i = 2; i < N; i++) {
        if (divcount[i] == 1) {
            divcount[i] <<= 1;
            for (int j = i << 1; j < N; j += i) {
                int c = 0, d = j;
                while (d % i == 0) {
                    d /= i;
                    c++;
                }
                divcount[j] *= c + 1;
            }
        }
    }
    auto v = multiply(divcount, divcount);

    cases {
        int lo, hi; cin >> lo >> hi;
        int id = lo;
        for (int i = lo; i <= hi; i++) {
            if (v[i] > v[id]) {
                id = i;
            }
        }
        cout << id << " " << v[id] << "\n";
    }

    return 0;
}
