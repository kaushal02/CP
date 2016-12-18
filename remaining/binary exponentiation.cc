inline ll pwr(ll a, ll n, ll m = mod) {
    ll ans(1);
    while(n) {
        if(n & 1) ans = ans * a % m;
        n >>= 1;
        a = a * a % m;
    }
    return ans;
}

inline ll mul(ll a, ll b, ll m) {
    long double temp = a;
    temp *= b;
    a *= b;
    b = temp / m;
    a -= b * m;
    return ((a % m) + m) % m;
}
inline ll pwr(ll a, ll n, ll m) {
    ll ans(1);
    while(n) {
        if(n & 1) ans = mul(ans, a, m);
        n >>= 1;
        a = mul(a, a, m);
    }
    return ans;
}