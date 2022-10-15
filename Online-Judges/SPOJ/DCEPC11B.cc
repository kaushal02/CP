#include <iostream>
#include <cassert>
using namespace std;

int pwr(int a, int n, int mod) {
    int ans = 1;
    while (n > 0) {
        if (n & 1) ans = (long long) ans * a % mod;
        if (n >>= 1) a = (long long) a * a % mod;
    }
    return ans % mod;
}

int inv(int n, int mod) {
    // n ^ (mod - 1) = 1 % mod
    return pwr(n, mod - 2, mod);
}

int solve(int n, int p) {
    if (n >= p) {
        return 0;
    }
    if (n == p - 1) {
        return n;
    }
    // (p-1)! == p-1 mod p
    // (p-2)! == 1 mod p
    // (p-3)! = inv(p-2) mod p
    // (p-4)! = inv(p-3) * inv(p-2) mod p
    // n! = inv(n+1) * inv(n+2) * ... * inv(p-2) mod p
    int ans = 1;
    while (++n <= p - 2) {
        ans = (long long) ans * inv(n, p) % p;
    }
    return ans;
}

void unittests() {
    assert(pwr(1, 0, 2) == 1);
    assert(pwr(1, 0, 11) == 1);
    assert(pwr(1, 1, 2) == 1);
    assert(pwr(1, 1, 11) == 1);
    assert(pwr(10, 1, 2) == 0);
    assert(pwr(10, 1, 3) == 1);
    assert(pwr(10, 1, 7) == 3);
    assert(inv(1, 2) == 1);
    assert(inv(1, 3) == 1);
    assert(inv(2, 3) == 2);
    assert(inv(3, 5) == 2);
    assert(inv(4, 5) == 4);
    assert(solve(1, 2) == 1);
    assert(solve(2, 2) == 0);
    assert(solve(3, 2) == 0);
    assert(solve(1, 3) == 1);
    assert(solve(2, 3) == 2);
    assert(solve(3, 3) == 0);
    assert(solve(2, 5) == 2);
    assert(solve(3, 5) == 1);
    assert(solve(4, 5) == 4);
    assert(solve(4, 7) == 3);
    assert(solve(5, 7) == 1);
}

int main() {
    // your code goes here
    unittests();

    int cases; cin >> cases;
    while (cases--) {
        int n, p; cin >> n >> p;
        cout << solve(n, p) << '\n';
    }
    return 0;
}