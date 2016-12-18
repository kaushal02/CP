ll fac[N], inv[N], mod_ = mod;
inline ll pwr(ll a, ll n, ll m = mod) {
    ll ans(1);
    while(n) {
        if(n & 1) ans = ans * a % m;
        n >>= 1;
        a = a * a % m;
    }
    return ans;
}
inline void init_ncr(int N) {
    fac[0] = 1;
    rep1(i,1,N) fac[i] = fac[i-1] * i % mod_;
    inv[N] = pwr(fac[N], mod_-2);
    rep2(i,N,1) inv[i-1] = inv[i] * i % mod_;
}
inline ll ncr(ll n, ll r) {
    static bool status = false;
    if(!status) init_ncr(N-1);
    status = true;
    
    if(n < 0 or r < 0 or n < r) return 0;
    return fac[n] * (inv[r] * inv[n-r] % mod_) % mod_;
}