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
#define coutt cout << "Case " << _t << ": "
#define io ios_base::sync_with_stdio(false); cin.tie(NULL);

const int N=1e5+10;

int np, prime[N];
bool isp[N];
vi pf[N];
void sieve(int N) {
    memset(isp, true, sizeof isp);
    isp[0] = isp[1] = false;
    for(int i=2; i<N; i++) if(isp[i]) {
        prime[++np]=i;
        pf[i]={np};
        for(int j=2*i; j<N; j+=i) {
            isp[j]=false;
            pf[j].pb(np);
        }
    }
}

int n, a[N], b[N/10][N/100]; // if(b[i][j]>>k&1) means prime[i] is in a[j*60+k]

#undef int
int main() {
#define int long long
    sieve(N);
    cin >> n; rep(i,n) {
        cin >> a[i];
        for(int pi: pf[a[i]]) {
            b[pi][i/60] |= 1LL<<(i%60);
        }
    }
    
    cases {
        int ty; cin >> ty;
        if(ty == 1) {
            int i, v; cin >> i >> v; i--;

            for(int pi: pf[a[i]]) b[pi][i/60] ^= 1LL<<(i%60);
            a[i] = v;
            for(int pi: pf[a[i]]) b[pi][i/60] |= 1LL<<(i%60);
        }
        else if(ty == 2) {
            int l, r, g; cin >> l >> r >> g; l--, r--;
            int ans=0, li=l/60, ri=r/60;
            for(int i=l; i<(li+1)*60; i++) {
                if(i>r) goto FLAG;
                int fl=0;
                for(int pi: pf[g]) if(b[pi][i/60]>>(i%60)&1LL) fl++;
                if(!fl) ans++;
            }
            for(int i=li+1; i<ri; i++) {
                int fl=0;
                for(int pi: pf[g]) fl |= b[pi][i];
                ans += 60 - __builtin_popcountll(fl);
            }
            for(int i=ri*60; i<=r; i++) {
                int fl=0;
                for(int pi: pf[g]) if(b[pi][i/60]>>(i%60)&1LL) fl++;
                if(!fl) ans++;
            }
FLAG:       cout << ans << '\n';
        }
        else assert(0);
    }

    return 0;
}
