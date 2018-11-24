/*
_fast_matrix_multiply

Problem Page - https://www.codechef.com/CDX2018/problems/CODX09/
Ref sequence - https://oeis.org/A001541

Please read the Discussion below for more details

O(8 * log n) per testcase
*/

#include <iostream>
using namespace std;
/*
 * For a given n, solution turns out to be A001541(n)
 *
 * Now A001541(n) can be written as follows:
 * a(n) = 6 * a(n - 1) - a(n - 2)
 * i. e., [[6 -1] [1 0]] * [a(n - 1) a(n - 2)] = [a(n) a(n - 1)]
 * and, [[6 -1] [1 0]] * [a(n - 2) a(n - 3)] = [a(n - 1) a(n - 2)]
 * and, [[6 -1] [1 0]] * [a(n - 3) a(n - 4)] = [a(n - 2) a(n - 3)]
 * and so on..
 *
 * i. e., [[6 -1] [1 0]] ^ (n - 1) * [a(1) a(0)] = [a(n) a(n - 1)]
 * Lets call M = [[6 -1] [1 0]] ^ (n - 1)
 * Hence, M * [a(1) a(0)] = [a(n) a(n - 1)]
 * i. e., M * [3 1] = [a(n) a(n - 1)]
 * i. e., M[0][0] * 3 + M[0][1] = a(n) = A001541(n) = Required solution
 */
#define int long long
const int K = 2, mod = 1E9 + 7;

/*
 * Binary Exponentiation for Matrix Multiplication 
 * Evaluate M^n in O(K^3 * log n) where M is a square matrix of size K
 */
template <class T>
void mul(T a[K][K], T b[K][K]) {
    T c[K][K];
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < K; j++) {
            int temp = 0;
            for (int k = 0; k < K; k++) {
                temp += a[i][k] * b[k][j] % mod;
            }
            c[i][j] = temp % mod;
        }
    }
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < K; j++) {
            a[i][j] = c[i][j];
        }
    }
}
template <class T>
void pwr(T a[K][K], int n) {
    assert(n >= 0);
    T temp[K][K];
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < K; j++) {
            temp[i][j] = a[i][j];
            a[i][j] = i == j;
        }
    }
    while (n) {
        if (n & 1) mul(a, temp);
        if (n >>= 1) mul(temp, temp);
    }
}

signed main() {

    int cases; cin >> cases;
    while (cases--) {
        int n; cin >> n;
        if (not n) cout << "1\n";
        else {
            int a[K][K] = {
                {6, mod - 1},
                {1, 0}
            };
            pwr(a, n - 1); // getting M as mentioned at the top
            cout << (a[0][0] * 3 + a[0][1]) % mod << '\n';
        }
    }

    return 0;
}