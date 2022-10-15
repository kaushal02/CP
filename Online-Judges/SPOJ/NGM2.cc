#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

class Solution {
    static const int K = 15;
    int n, k;
    vector <int> nums;
    vector <int> lcms;
    int gcd(int a, int b) {
        return (b ? gcd(b, a % b) : a);
    }
    int lcm(int a, int b) {
        long long temp = (long long) a * b / gcd(a, b);
        if (temp > n) {
            return n + 1;
        }
        return temp;
    }
    // getLCM returns LCM of elements as positions defined by mask
    // if LCM > n, return n + 1
    int getLCM(int mask) {
        if (lcms[mask] != -1) {
            return lcms[mask];
        }
        if (!mask) {
            return 1;
        }
        int x = (mask & -mask), pos = 0;
        int removed = x;
        while (x >>= 1) {
            pos++;
        }
        return lcms[mask] = lcm(getLCM(mask ^ removed), nums[pos]);
    }
    // getSign returns 1 or -1, whether to include or exclude
    int getSign(int mask) {
        return ((__builtin_popcount(mask) & 1) ? -1 : 1);
    }
public:
    Solution(int _n, vector <int> _nums): n(_n), k(_nums.size()), nums(_nums), lcms(1 << K, -1) {}
    int solve() {
        long long ans(0);
        for (int mask = 0; mask < (1 << k); mask++) {
            ans += (n / getLCM(mask)) * getSign(mask);
        }
        return ans;
    }
    static void unittests() {
        assert(Solution(100, {1}).solve() == 0);
        assert(Solution(100, {2}).solve() == 50);
        assert(Solution(10, {11}).solve() == 10);
        assert(Solution(10, {2,4,5}).solve() == 4);
        assert(Solution(100, {4,6,8,12}).solve() == 67);
    }
};


int main() {
    // your code goes here
    Solution::unittests();

    int n, k; cin >> n >> k;
    vector <int> nums(k);
    for (int& num : nums) {
        cin >> num;
    }
    Solution solution(n, nums);
    cout << solution.solve();
    return 0;
}