#include <iostream>
#include <cassert>
using namespace std;

const int B = 64;
long long ncr[B + 1][B + 1];
long long countKBitNumbersHelper(int n, int k) {
    // count of numbers having exactly k set bits in range (0, 1<<n)
    // equals choose(n, k)
    if (n < k or n < 0 or k < 0) {
        return 0;
    }
    if (k == 0) {
        return 1;
    }
    if (ncr[n][k]) {
        return ncr[n][k];
    }
    return ncr[n][k] = countKBitNumbersHelper(n - 1, k) + countKBitNumbersHelper(n - 1, k - 1);
}

long long countKBitNumbers(long long n, int k) {
    // count of numbers having exactly k set bits in range (0, n)
    long long ans = 0;
    for (int i = B; i--; ) {
        if (n >> i & 1) {
            ans += countKBitNumbersHelper(i, k--);
        }
    }
    return ans;
}

void unittests() {
    assert(countKBitNumbersHelper(0, 0) == 1);
    assert(countKBitNumbersHelper(1, 0) == 1);
    assert(countKBitNumbersHelper(10, 0) == 1);
    assert(countKBitNumbersHelper(0, 1) == 0);
    assert(countKBitNumbersHelper(1, 1) == 1);
    assert(countKBitNumbersHelper(10, 1) == 10);
    assert(countKBitNumbersHelper(6, 3) == 20);
    assert(countKBitNumbersHelper(50, 2) == 1225);
    assert(countKBitNumbers(1, 1) == 0);
    assert(countKBitNumbers(15, 1) == 4);
    assert(countKBitNumbers(15, 2) == 6);
}

int main() {
    // your code goes here
    long long m; cin >> m;
    int k; cin >> k;
    unittests();

    long long lo = 1, hi = 1E18 + 1, mi;
    while (lo < hi) {
        mi = (lo + hi + 1) / 2;
        if (countKBitNumbers(2 * mi + 1, k) - countKBitNumbers(mi + 1, k) > m) {
            hi = mi - 1;
        } else {
            lo = mi;
        }
    }
    cout << lo << '\n';
    return 0;
}