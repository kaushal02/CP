#include <vector>

/*
 * Prime(n) stores all primes below n
 * Time : O(n * log log n)
 * Space: O(n)
 */
class Prime {
    int N;
    vector <int> value;
    vector <bool> isPrime;
public:
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
    int getKthPrime(int k) {
        return value[k - 1];
    }
    static void unittests() {
        Prime p(100);
        assert(p.check(2));
        assert(p.check(3));
        assert(p.check(13));
        assert(p.getKthPrime(1) == 2);
        assert(p.getKthPrime(4) == 7);
    }
};
