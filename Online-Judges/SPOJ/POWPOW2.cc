#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

const int MOD = 1E9 + 7;
const int MOD2 = 5E8 + 3;
const int MODn2 = 41 * 41;
const int MODn3 = 148721;
const int N = 2E5 + 5;
int prime[N], fac[N], inv[N];
int choose_array[N], choose_array_modn2[N], choose_array_modn3[N];

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

inline int squared(int a, int mod) {
    return (long long) a * a % mod;
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

int get_quotient_extended_euclid(int a, int b) {
    // x such that ax + by = gcd(a, b)
    int r0 = a, r1 = b, s0 = 1, s1 = 0; // defined such that r_i = s_i * a + t_i * b
    while (r1) {
        int r2 = r0 % r1;
        int q1 = (r0 - r2) / r1;
        int s2 = s0 - q1 * s1;
        r0 = r1, s0 = s1;
        r1 = r2, s1 = s2;
    }
    return s0;
}

int crt_merge(int a1, int a2, int n1, int n2) {
    /* assume X = a1 mod n1
     *        X = a2 mod n2
     *        gcd(n1, n2) = 1
     * find m1, m2 such that m1n1 + m2n2 = 1
     * return a1m2n2 + a2m1n1 = X mod n1n2
     */
    int m1 = get_quotient_extended_euclid(n1, n2);
    int m2 = (1 - (long long) m1 * n1) / n2;
    assert((long long) m1 * n1 + (long long) m2 * n2 == 1LL);
    return remainder(((long long) a1 * m2) * n2 + ((long long) a2 * m1) * n1, n1 * n2);
}

int remove_prime_power(int& n, int p) {
    // reduce n to n1 such that n = n1 * p^k, return k
    int removed_power = 0;
    while (n && n % p == 0) {
        removed_power++;
        n /= p;
    }
    return removed_power;
}

void fill_ncr_array() {
    // choose_array[i] = choose(2i, i) % (MOD2 - 1)
    /*
     * (MOD2 - 1) = 2 * MODn2 * MODn3
     * a1 = choose(2i, i) mod 2
     * a2 = choose(2i, i) mod MODn2
     * a3 = choose(2i, i) mod MODn3
     * Using CRT, a12 = crt_merge(a1, a2, 2, MODn2) = choose(2i, i) mod 2*MODn2
     * Using CRT, choose_array[i] = crt_merge(a12, a3, 2*MODn2, MODn3)
     */
    fac[0] = 1;
    for (int i = 1; i < N; i++) {
        fac[i] = (long long) fac[i - 1] * i % MODn3;
    }
    inv[N / 2] = pwr(fac[N / 2], MODn3 - 2, MODn3);
    for (int i = N / 2; i--; ) {
        inv[i] = (long long) inv[i + 1] * (i + 1) % MODn3;
    }
    choose_array_modn3[0] = 1;
    for (int i = 1; 2 * i < N; i++) {
        choose_array_modn3[i] = ((long long) fac[2 * i] * inv[i]) * inv[i] % MODn3;
    }

    int res = 1;
    int prime_power = 0;
    choose_array_modn2[0] = res;
    for (int i = 1; i < N; i++) {
        int x = 2 * i - 1;
        prime_power += remove_prime_power(x, 41);
        res = (long long) res * x % MODn2;

        x = 2 * i;
        prime_power += remove_prime_power(x, 41);
        res = (long long) res * x % MODn2;

        x = i;
        prime_power -= 2 * remove_prime_power(x, 41);
        res = (long long) res * squared(pwr(x, MODn2 - 41 - 1, MODn2), MODn2) % MODn2;

        int prime_factor = 1;
        if (prime_power == 1) {
            prime_factor = 41;
        } else if (prime_power > 1) {
            prime_factor = 0;
        } else {
            assert(prime_power == 0);
        }
        choose_array_modn2[i] = remainder((long long) res * prime_factor, MODn2);
    }

    choose_array[0] = 1;
    for (int i = 1; i < N; i++) {
        res = crt_merge(0, choose_array_modn2[i], 2, MODn2);
        res = crt_merge(res, choose_array_modn3[i], 2 * MODn2, MODn3);
        choose_array[i] = res;
    }
}

int residue(int a, int n) {
    // a^choose(2n, n) % MOD2
    return pwr(a, choose_array[n], MOD2);
}

int powpow2(int a, int b, int n) {
    // a^(b^choose(2n, n)) % MOD
    /*
     * If   a1 = b^choose(2n, n) mod 2
     *      a2 = b^choose(2n, n) mod MOD2
     * Then  A = b^choose(2n, n) mod (2 * MOD2)
     *         = b^choose(2n, n) % (MOD - 1)
     * Where A = a2 * (MOD2 + 1) + a1 * (-MOD2)
     *         = (a2 - a1) * MOD2 + a2
     */
    int a1 = (b & 1);
    int a2 = residue(b, n);
    int A = remainder((long long)(a2 - a1) * MOD2 + a2, MOD - 1);
    return pwr(a, A, MOD);
}

void unittests() {
    // fill_ncr_array
    assert(choose_array_modn3[1] == 2);
    assert(choose_array_modn3[2] == 6);
    assert(choose_array_modn3[3] == 20);
    assert(choose_array[1] == 2);
    assert(choose_array[2] == 6);
    assert(choose_array[3] == 20);
    assert(choose_array[10] == 184756);
    assert(choose_array[20] == 346528270);
    assert(choose_array_modn2[41] == 2);
    assert(choose_array_modn2[840] == 206);
    assert(choose_array_modn2[841] == 0);
    assert(choose_array_modn2[1000] == 1476);
    assert(choose_array_modn3[(MODn3 + 1) / 2] == 0);
    assert(choose_array_modn3[(MODn3 - 1) / 2] != 0);
    // residue
    assert(residue(0, 0) == 0);
    assert(residue(0, 10) == 0);
    assert(residue(10, 0) == 10);
    assert(residue(2, 2) == 64);
    // powpow2
    assert(powpow2(0, 0, 0) == 1);
    assert(powpow2(10, 0, 0) == 1);
    assert(powpow2(0, 10, 0) == 0);
    assert(powpow2(0, 0, 10) == 1);
    assert(powpow2(10, 20, 0) == 4900);
    assert(powpow2(10, 0, 20) == 1);
    assert(powpow2(0, 10, 20) == 0);
    assert(powpow2(1, 1, 1) == 1);
    assert(powpow2(2, 2, 0) == 4);
    assert(powpow2(2, 2, 2) == 582344008);
    assert(powpow2(10, 10, 10) == 330427784);
    assert(powpow2(458, 9575, 7458) == 688147711);
    assert(powpow2(79981, 79981, 79981) == 79981);
    assert(powpow2(100000, 100000, 100000) == 754901378);
}

int main() {
    // your code goes here
    fill_primes();
    fill_ncr_array();
    unittests();

    int cases;
    cin >> cases;
    while (cases--) {
        int a, b, n;
        cin >> a >> b >> n;
        cout << powpow2(a, b, n) << '\n';
    }
    return 0;
}