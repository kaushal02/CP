ll k;

map<ll,ll> memo[20];
inline ll f(int len, ll sum) {
    if(!len) return sum == k; // modify value
    if(memo[len].find(sum) != memo[len].end())
        return memo[len][sum];
    
    ll ans(0);
    rep(i,10) ans += f(len - 1, sum + i); // modify 'sum'
    return memo[len][sum] = ans;
}

inline ll tot(ll n) {
    if(!n) return 0;
    rep(i,20) memo[i].clear();
    
    int d[20], len(0);
    ll ncopy = n;
    while(n) d[len++] = n % 10, n /= 10;
    
    ll ans(0), p(0), pcopy;
    rep2(i,len-1,0) {
        pcopy = p;
        rep1(j,0,d[i]) {
            p = pcopy + j; // modify 'p'
            if(j < d[i]) ans += f(i, p);
        }
    }
    return ans;
}