void print(double A[N][N*2], int n) {
    cerr << fixed << setprecision(2);
    rep(i,n)rep(j,n*2) {
        if(j == n) cerr << " | ";
        cerr << A[i][j] << " \n"[j == 2*n - 1];
    }
    cerr << '\n';
}
int DiaReduce(double A[N][N*2], int n) {
    rep(i,n)rep(j,n) A[i][j + n] = i == j;
    rep(k,n) {
        int i_max = k;
        rep(i,n) if(i > k and abs(A[i][k]) > abs(A[i_max][k])) i_max = i;
        if(abs(A[i_max][k]) < eps) return k;
        if(i_max != k) rep(j,n*2) swap(A[k][j], A[i_max][j]);
        rep(i,n) if(i != k) {
            double f = A[i][k] / A[k][k];
            rep(j,n*2) A[i][j] -= A[k][j] * f;
        }
    }
    return -1;
}
bool Inv(double A[N][N*2], int n) {
    if(DiaReduce(A, n) + 1) return false;
    rep(i,n)rep(j,n) A[i][j + n] /= A[i][i];
    return true;
}
double Det(double A[N][N*2], int n) {
    if(DiaReduce(A, n) + 1) return 0;
    double ans(1); rep(i,n) ans *= A[i][i]; return ans;
}
bool solve(double A[N][N*2], double x[N], double B[N], int n) {
    // solve Ax = B for unique x only
    if(!Inv(A, n)) return false;
    rep(i,n) {
        x[i] = 0;
        rep(j,n) x[i] += A[i][n + j] * B[j];
    }
}


ll p, in[N]; // in[i] = inverse of i modulo p
inline ll inv(ll n) {
    return in[n];
}
void print(ll A[N][N*2], int n) {
    rep(i,n)rep(j,n*2) {
        if(j == n) cerr << " | ";
        cerr << A[i][j] << " \n"[j == 2*n - 1];
    }
    cerr << '\n';
}
int DiaReduce(ll A[N][N*2], int n) {
    rep(i,n)rep(j,n) {
        A[i][j] %= p;
        A[i][j + n] = i == j;
    }
    rep(k,n) {
        int i_max = k;
        rep(i,n) if(i > k and abs(A[i][k]) > abs(A[i_max][k])) i_max = i;
        if(!A[i_max][k]) return k;
        if(i_max != k) rep(j,n*2) swap(A[k][j], A[i_max][j]);
        rep(i,n) if(i != k) {
            ll f = A[i][k] * inv(A[k][k]) % p;
            rep(j,n*2) {
                A[i][j] -= A[k][j] * f % p;
                if(A[i][j] < 0) A[i][j] += p;
            }
        }
    }
    return -1;
}
bool Inv(ll A[N][N*2], int n) {
    if(DiaReduce(A, n) + 1) return false;
    rep(i,n)rep(j,n) A[i][j + n] = A[i][j + n] * inv(A[i][i]) % p;
    return true;
}
ll Det(ll A[N][N*2], int n) {
    if(DiaReduce(A, n) + 1) return 0;
    ll ans(1); rep(i,n) ans = ans * A[i][i] % p; return ans;
}
bool solve(ll A[N][N*2], ll x[N], ll B[N], int n) {
    // solve Ax = B for unique x
    if(!Inv(A, n)) return false;
    rep(i,n) x[i] = 0, B[i] %= p;
    rep(i,n) {
        rep(j,n) x[i] += A[i][n + j] * B[j] % p;
        x[i] %= p;
    }
}