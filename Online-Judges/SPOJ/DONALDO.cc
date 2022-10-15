#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

class Solution {
public:
    static int solve(vector <int>& a, int k) {
        int ans = 0;
        deque <int> dq;
        for (int ai : a) {
            while (!dq.empty() and ai - dq.front() >= k) {
                dq.pop_front();
            }
            dq.push_back(ai);
            ans = max(ans, (int) dq.size());
        }
        return ans;
    }
    static void unittests() {

    }
};

int main() {
    // your code goes here
    Solution::unittests();

    int cases; cin >> cases;
    for (int casenum = 1; casenum <= cases; casenum++) {
        int n; cin >> n;
        vector <int> times(n);
        for (int i = 0; i < n; i++) {
            char c;
            int hh, mm, ss;
            cin >> hh >> c >> mm >> c >> ss;
            times[i] = ss + 60 * (mm + 60 * hh);
        }
        sort(times.begin(), times.end());
        int minGap; cin >> minGap;
        cout << "Case " << casenum << ": " << Solution::solve(times, minGap) << '\n';
    }
    return 0;
}