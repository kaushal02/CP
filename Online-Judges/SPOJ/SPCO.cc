#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

typedef unsigned long long ull;
const int B = 65;

class Prime {
    int N;
    vector <bool> isPrime;
public:
    vector <int> value;
    Prime(int n) {
        N = n;
        isPrime.resize(n, true);
        isPrime[0] = isPrime[1] = false;
        for (int i = 2; i < n; i++) {
            if (isPrime[i]) {
                value.push_back(i);
                for (int j = 2 * i; j < n; j += i) {
                    isPrime[j] = false;
                }
            }
        }
    }
    bool check(int n) {
        return isPrime[n];
    }
    void unittests() {
        assert(isPrime[2]);
        assert(isPrime[3]);
        assert(isPrime[13]);
        assert(value[0] == 2);
        assert(value[3] == 7);
    }
};

template <class T>
class NCR {
    int N;
    vector <vector <T> > value;
public:
    NCR(int n) {
        N = n;
        value.resize(n, vector <T> (n));
    }
    T getValue(int n, int r) {
        if (n < 0 or r < 0 or n < r) {
            return 0;
        }
        if (r == 0) {
            return 1;
        }
        if (value[n][r]) {
            return value[n][r];
        }
        return value[n][r] = getValue(n - 1, r - 1) + getValue(n - 1, r);
    }
    void unittests() {
        assert(getValue(0, 0) == 1);
        assert(getValue(1, 0) == 1);
        assert(getValue(10, 0) == 1);
        assert(getValue(1, 1) == 1);
        assert(getValue(10, 1) == 10);
        assert(getValue(10, 10) == 1);
        assert(getValue(6, 3) == 20);
    }
};

ull countBitwisePrimesHelper(NCR<ull> &ncr, Prime &prime, int b, int offset) {
    // #bitwise primes of b bits assuming primes are offset by "offset"
    // for e.g., if offset=1, primes will be {1,2,4,6,10,12,16,..}
    ull ans = 0;
    for (int p : prime.value) {
        if (p > b + offset) {
            break;
        }
        ans += ncr.getValue(b, p - offset);
    }
    return ans;
}

ull countBitwisePrimes(NCR<ull> &ncr, Prime &prime, ull n) {
    // #bitwise primes in [1, n)
    int set_bits = 0;
    ull ans = 0;
    for (int i = B - 1; i--; ) {
        if (n >> i & 1) {
            ans += countBitwisePrimesHelper(ncr, prime, i, set_bits);
            set_bits++;
        }
    }
    return ans;
}

void unittests(NCR<ull> &ncr, Prime &prime) {
    ncr.unittests();
    prime.unittests();
    assert(countBitwisePrimesHelper(ncr, prime, 0, 0) == 0);
    assert(countBitwisePrimesHelper(ncr, prime, 0, 10) == 0);
    assert(countBitwisePrimesHelper(ncr, prime, 1, 0) == 0);
    assert(countBitwisePrimesHelper(ncr, prime, 2, 0) == 1);
    assert(countBitwisePrimesHelper(ncr, prime, 2, 1) == 3);
    assert(countBitwisePrimesHelper(ncr, prime, 2, 2) == 3);
    assert(countBitwisePrimesHelper(ncr, prime, 4, 0) == 10);
    assert(countBitwisePrimesHelper(ncr, prime, 4, 1) == 11);
    assert(countBitwisePrimesHelper(ncr, prime, 4, 2) == 9);
    assert(countBitwisePrimesHelper(ncr, prime, 4, 3) == 8);
    assert(countBitwisePrimes(ncr, prime, 1) == 0);
    assert(countBitwisePrimes(ncr, prime, 2) == 0);
    assert(countBitwisePrimes(ncr, prime, 3) == 0);
    assert(countBitwisePrimes(ncr, prime, 4) == 1);
    assert(countBitwisePrimes(ncr, prime, 7) == 3);
    assert(countBitwisePrimes(ncr, prime, 8) == 4);
    assert(countBitwisePrimes(ncr, prime, 15) == 10);
}

int main() {
    // your code goes here
    Prime prime(B);
    NCR <ull> ncr(B);
    unittests(ncr, prime);

    int cases;
    cin >> cases;
    while (cases--) {
        ull a, b;
        cin >> a >> b;
        cout << countBitwisePrimes(ncr, prime, b + 1) - countBitwisePrimes(ncr, prime, a) << '\n';
    }



    return 0;
}
