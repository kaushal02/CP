#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
using namespace std;

class Prime {
    int N;
    vector <int> values;
    vector <bool> isPrime;
public:
    Prime() {}
    Prime(int n) {
        init(n);
    }
    void init(int n) {
        N = n;
        isPrime.resize(n, true);
        isPrime[0] = isPrime[1] = false;
        for (int i = 2; i < n; i++) {
            if (isPrime[i]) {
                values.push_back(i);
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
        return values[k - 1];
    }
    static void unittests() {
        Prime p(100);
        assert(p.check(2));
        assert(p.check(3));
        assert(p.check(13));
        assert(p.getKthPrime(1) == 2);
        assert(p.getKthPrime(5) == 11);
    }
};

class Solution {
    const int N = 10000;
    Prime prime;
public:
    Solution(): prime(N) {
        Prime::unittests();
    }
    // number of steps to reach from a to b through primes
    int solve(int a, int b) {
        vector <int> distance(N, -1);
        queue < pair <int, int> > q;
        q.push(make_pair(a, 0));
        distance[a] = 0;
        while (!q.empty()) {
            int n = q.front().first;
            int steps = q.front().second;
            q.pop();
            if (0 <= distance[n] and distance[n] < steps) {
                continue;
            }
            if (n == b) {
                return steps;
            }
            for (int i = 0, p10 = 1; i < 4; i++, p10 *= 10) {
                // changing i-th digit of n
                int cur_digit = (n / p10) % 10;
                for (int d = (i == 3); d < 10; d++) {
                    if (d == cur_digit) {
                        continue;
                    }
                    int new_n = n + (d - cur_digit) * p10;
                    if (prime.check(new_n) and distance[new_n] == -1) {
                        q.push(make_pair(new_n, steps + 1));
                        distance[new_n] = steps + 1;
                    }
                }
            }
        }
        return -1;
    }
    static void unittests() {
        Solution s;
        assert(s.solve(1033, 1033) == 0);
        assert(s.solve(1033, 1733) == 1);
        assert(s.solve(1733, 3733) == 1);
        assert(s.solve(3733, 3739) == 1);
        assert(s.solve(3739, 3779) == 1);
        assert(s.solve(3779, 8779) == 1);
        assert(s.solve(8779, 8179) == 1);
        assert(s.solve(1373, 8017) == 7);
    }
};

int main() {
    Solution::unittests();

    Solution s;
    int cases; cin >> cases;
    while (cases--) {
        int a, b; cin >> a >> b;
        cout << s.solve(a, b) << '\n';
    }
    return 0;
}