const int M=2;
template<class T> void mul(T a[M][M], T b[M][M]) {
	T c[M][M];
	rep(i,M)rep(j,M) {
		ll temp=0;
		rep(k,M) temp += a[i][k]*b[k][j]%mod;
		c[i][j]=temp%mod;
	}
	rep(i,M)rep(j,M) a[i][j]=c[i][j];
}
template<class T> pwr(T a[M][M], ll n) {
	assert(n>=0);
	T temp[M][M];
	rep(i,M)rep(j,M) temp[i][j]=a[i][j], a[i][j]=i==j;
	while(n) {
		if(n&1) mul(a,temp);
		mul(temp,temp);
		n>>=1;
	}
}
/*****************************************************************************************
******************************************************************************************
*****************************************************************************************/
inline ll add(ll a, ll b){
    ll ans = a + b;
    if(ans >= mod) return ans - mod;
    return ans;
}
inline ll mul(ll a , ll b){
    ll ans = a * b;
    if(ans >= mod) return ans % mod;
    return ans;
}
const int SZ = 3;
struct matrix {
    ll a[SZ][SZ];
    matrix() { mem(a, 0);}
    inline void id() { rep(i,SZ)rep(j,SZ) a[i][j] = (i == j);}
    inline matrix operator+( matrix &m)  {
        matrix ans;
        rep(i,SZ)rep(j,SZ) ans.a[i][j] = add(a[i][j], m.a[i][j]);
        return ans;
    }
    inline matrix operator*(const matrix &m) const {
        matrix ans;
        rep(i,SZ)rep(j,SZ)rep(k,SZ) ans.a[i][j] = add(ans.a[i][j], mul(a[i][k], m.a[k][j]));
        return ans;
    }
};
inline matrix pwr(matrix a, ll n){
    assert(n >= 0);
    matrix ans;
    ans.id();
    while(n) {
        if(n & 1) ans = ans * a;
        a = a * a;
        n >>= 1;
    }
    return ans;
}
inline ostream& operator<<(ostream &cout, matrix &m) {
    rep(i,SZ) {
        cout << "| ";
        rep(j,SZ) cout << m.a[i][j] << " ";
        cout << "|\n";
    }
    cout << '\n';
}
/*****************************************************************************************
******************************************************************************************
*****************************************************************************************/
const int Nmat = 2;
template<typename T>
inline void mul(T a[Nmat][Nmat], T b[Nmat][Nmat]) {
    ll temp;
    register T c[Nmat][Nmat];
    rep(i,Nmat)rep(j,Nmat) { // modify
        temp = 0;
        rep(k,Nmat) temp += a[i][k] * b[k][j] % mod;
        c[i][j] = temp % mod;
    }
    rep(i,Nmat)rep(j,Nmat) a[i][j] = c[i][j];
}
template<typename T>
inline void pwr(T a[Nmat][Nmat], ll n) {
    assert(n >= 0);
    T temp[Nmat][Nmat];
    rep(i,Nmat)rep(j,Nmat) {
        temp[i][j] = a[i][j];
        a[i][j] = 0;
    }
    rep(i,Nmat) {
        a[i][i] = 1;
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
const int Nmat = 5;
ll pow2[65][Nmat][Nmat], base[Nmat], temp_vec[Nmat];
inline void seed() {
    // Initialize values for pow2[0][i][j] and base[i]
    // Remember to use only non - negative seeds

}
inline void store() {
    rep1(x,1,60)rep(i,Nmat)rep(j,Nmat) {
        rep(k,Nmat) pow2[x][i][j] += pow2[x-1][i][k] * pow2[x-1][k][j] % mod;
        pow2[x][i][j] %= mod;
    }
}
inline void mul(ll vec[Nmat], int depth) {
    mem(temp_vec, 0);
    rep(i,Nmat) {
        rep(j,Nmat) temp_vec[i] += pow2[depth][i][j] * vec[j] % mod;
        temp_vec[i] %= mod;
    }
    rep(i,Nmat) vec[i] = temp_vec[i];
}
inline ll get(ll n) {
    ll temp[Nmat];
    rep(i,Nmat) temp[i] = base[i];
    int depth = 0;
    while(n) {
        if(n & 1) mul(temp, depth);
        n >>= 1;
        depth++;
    }
    return temp[]; // add index
}
