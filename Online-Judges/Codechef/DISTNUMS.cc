#include <iostream>
using namespace std;
const int MOD = 1E9 + 7;

int pwr(int a, int n, int mod) {
    // a^n % mod
    int ans = 1;
    while (n) {
        if (n & 1) ans = (long long) ans * a % mod;
        if (n >>= 1) a = (long long) a * a % mod;
    }
    return ans;
}

int inv(int n) {
    return pwr(n, MOD - 2, MOD);
}

int sumGeometric(int p, int k, int s) {
    // p^k + p^(k+1) + p^(k+2) ... + p^((2^s)*k)
    int power = 1 + (long long) k * pwr(2, s, MOD - 1) % (MOD - 1);
    int ans = (pwr(p, power, MOD) - pwr(p, k, MOD)) % MOD;
    if (ans < 0) {
        ans += MOD;
    }
    return (long long) ans * inv(p - 1) % MOD;
}

int main() {
    // your code goes here
    int cases; cin >> cases;
    while (cases--) {
        int n, k;
        cin >> n >> k;
        int ans = 1;
        for (int factor = 2; factor * factor <= n; factor++) {
            int power = 0;
            while (n % factor == 0) {
                n /= factor;
                power++;
            }
            if (power) {
                ans = (long long) ans * sumGeometric(factor, power, k) % MOD;
            }
        }
        if (n > 1) {
            ans = (long long) ans * sumGeometric(n, 1, k) % MOD;
        }
        cout << ans << '\n';
    }
    return 0;
}