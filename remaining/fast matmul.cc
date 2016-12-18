const int N = 4;
inline void mul(ll a[N][N], ll b[N][N]) {
    register ll temp, c[N][N];
    rep(i,N)rep(j,N) {
        temp = 0;
        rep(k,N) temp += a[i][k] * b[k][j] % mod;
        c[i][j] = temp % mod;
    }
    rep(i,N)rep(j,N) a[i][j] = c[i][j];
}
inline void pwr(ll a[N][N], ll n) {
    ll temp[N][N];
    rep(i,N)rep(j,N) {
        temp[i][j] = a[i][j];
        a[i][j] = i == j;
    }
    while(n) {
        if(n & 1) mul(a, temp);
        n >>= 1;
        mul(temp, temp);
    }
}
/*****************************************************************************************
******************************************************************************************
*****************************************************************************************/
const int N = 5;
ll pow2[65][N][N], base[N], temp_vec[N];
inline void seed() {
    // Initialize values for pow2[0][i][j] and base[i]
    // Remember to use only non - negative seeds
    
}
inline void store() {
    rep1(x,1,60)rep(i,N)rep(j,N) {
        rep(k,N) pow2[x][i][j] += pow2[x-1][i][k] * pow2[x-1][k][j] % mod;
        pow2[x][i][j] %= mod;
    }
}
inline void mul(ll vec[N], int depth) {
    mem(temp_vec, 0);
    rep(i,N) {
        rep(j,N) temp_vec[i] += pow2[depth][i][j] * vec[j] % mod;
        temp_vec[i] %= mod;
    }
    rep(i,N) vec[i] = temp_vec[i];
}
inline ll get(ll n) {
    ll temp[N];
    rep(i,N) temp[i] = base[i];
    int depth = 0;
    while(n) {
        if(n & 1) mul(temp, depth);
        n >>= 1;
        depth++;
    }
    return temp[]; // add index
}