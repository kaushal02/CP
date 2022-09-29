#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

const int MOD = 1E9 + 7;
const int MOD2 = 5E8 + 3;
const int N = 2E5 + 5;
int prime[N], choose_array[N];

inline int pwr(int a, int n, int mod) {
    // a^n % mod
    int ans = 1;
    while (n) {
        if (n & 1) ans = (long long) ans * a % mod;
        a = (long long) a * a % mod;
        n >>= 1;
    }
    return ans % mod;
}

inline int inverse_squared(int a, int mod) {
    int inv = pwr(a, mod - 2, mod);
    return (long long) inv * inv % mod;
}

inline int remainder(long long a, int mod) {
    a %= mod;
    return (a < 0 ? a + mod : a);
}

void fill_primes() {
    // prime[i] = i'th prime
    int np = 0;
    vector <bool> isPrime(N, true);
    for (int i = 2; i < N; i++) {
        if (isPrime[i]) {
            prime[np++] = i;
            for (int j = 2 * i; j < N; j += i) {
                isPrime[j] = false;
            }
        }
    }
}

void fill_ncr_array() {
    // choose_array[i] = choose(2*i, i) % MOD2
    choose_array[0] = 1;
    for (int i = 1; i < N; i++) {
        int res = choose_array[i - 1];
        res = (long long) res * (2 * i - 1) % MOD2;
        res = (long long) res * (2 * i) % MOD2;
        res = (long long) res * inverse_squared(i, MOD2) % MOD2;
        choose_array[i] = res;
    }
}

int residue(int a, int n) {
    // choose(2a, a)^n % MOD2
    return pwr(choose_array[a], n, MOD2);
}

int powpow(int a, int b, int n) {
    // a^(choose(2n, n)^b) % MOD
    /*
     * If   a1 = choose(2n, n)^b mod 2
     *      a2 = choose(2n, n)^b mod MOD2
     * Then  A = choose(2n, n)^b mod (2 * MOD2)
     *         = choose(2n, n)^b % (MOD - 1)
     * Where A = a2 * (MOD2 + 1) + a1 * (-MOD2)
     *         = (a2 - a1) * MOD2 + a2
     * Furthermore, observe that a1 = !(n && b)
     */
    int a1 = !(n && b);
    int a2 = residue(n, b);
    int A = remainder((long long)(a2 - a1) * MOD2 + a2, MOD - 1);
    return pwr(a, A, MOD);
}

int main() {
    // your code goes here
    fill_primes();
    fill_ncr_array();
    int cases;
    cin >> cases;
    while (cases--) {
        int a, b, n;
        cin >> a >> b >> n;
        cout << powpow(a, b, n) << '\n';
    }
    return 0;
}