#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
#include <climits>
using namespace std;

class Solution {
    static int solveHelper(int limit, vector <int>& ranks) {
        int ans = 0;
        for (int r : ranks) {
            // k such that r * (1 + 2 + .. k) <= limit
            int k = sqrt(2 * limit / r) + 2;
            while (r * k * (k + 1) / 2 > limit) {
                k--;
            }
            ans += k;
        }
        return ans;
    }
public:
    static int solve(int count, vector <int> ranks) {
        int lo = 0, hi = INT_MAX, mi;
        while (lo < hi) {
            mi = lo + (hi - lo) / 2;
            if (solveHelper(mi, ranks) < count) {
                lo = mi + 1;
            } else {
                hi = mi;
            }
        }
        return lo;
    }
    static void unittests() {
        assert(solve(0, {}) == 0);
        assert(solve(0, {1,2,3}) == 0);
        assert(solve(1, {5,3}) == 3);
        assert(solve(2, {5,3}) == 5);
        assert(solve(10, {1,1,1,1,1}) == 3);
    }
};

int main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    Solution::unittests();

    int cases; cin >> cases;
    while (cases--) {
        int count; cin >> count;
        int chef_count; cin >> chef_count;
        vector <int> chef_ranks(chef_count);
        for (int& r : chef_ranks) {
            cin >> r;
        }
        cout << Solution::solve(count, chef_ranks) << '\n';
    }
    return 0;
}