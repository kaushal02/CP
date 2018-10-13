/*
_fast_matrix_multiply _DP

https://www.codechef.com/problems/ACM14KN2
https://threads-iiith.quora.com/Solving-Dynamic-Programming-with-Matrix-Exponentiation

O((4*K) ^ 3 * log N)
*/

#include <iostream>
using namespace std;
#define int long long

const int M = 40, mod = 1E7 + 7;

inline void mul(int a[M][M], int b[M][M]) {
    int c[M][M] = {};
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < M; k++) {
                c[i][j] += a[i][k] * b[k][j] % mod;
            }
        }
    }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            a[i][j] = c[i][j] % mod;
        }
    }
}
inline void pwr(int a[M][M], int n) {
    int b[M][M];
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            b[i][j] = a[i][j];
            a[i][j] = i == j;
        }
    }
    while (n) {
        if (n & 1) mul(a, b);
        if (n >>= 1) mul(b, b);
    }
}

signed main() {

    int t; cin >> t;
    while (t--) {
        int a[M][M] = {};
        int n, k; cin >> n >> k;
        for (int i = 0; i < k + !k; i++) {
            for (int j = 0; j < 4; j++) {
                if (k) a[4 * ((i + 1) % k) + j % 2][4 * i + j]++;
                if (j < 2) a[4 * i + (j | 2)][4 * i + j]++;
                a[4 * i + 1][4 * i + j]++;
            }
        }
        pwr(a, n);
        cout << (a[1][0] + a[3][0]) % mod << '\n';
    }

    return 0;
}
