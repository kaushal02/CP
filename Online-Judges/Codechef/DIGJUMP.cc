#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
using namespace std;

class Solution {
public:
    static int solve(string s) {
        int n = s.size();
        vector <int> positions[10];
        for (int i = 0; i < n; i++) {
            positions[s[i] - '0'].push_back(i);
        }

        vector <bool> isVisited(10, false);
        vector <int> steps(n, -1);
        int cur = 0;
        queue <int> q;
        q.push(n - 1);
        steps[n - 1] = cur;
        while (!q.empty()) {
            queue <int> next_q;
            while (!q.empty()) {
                int pos = q.front();
                q.pop();
                if (pos == 0) {
                    return steps[0];
                }
                if (pos > 0 and steps[pos - 1] == -1) {
                    next_q.push(pos - 1);
                    steps[pos - 1] = cur + 1;
                }
                if (pos < n - 1 and steps[pos + 1] == -1) {
                    next_q.push(pos + 1);
                    steps[pos + 1] = cur + 1;
                }
                int digit = s[pos] - '0';
                if (isVisited[digit]) {
                    continue;
                }
                isVisited[digit] = true;
                for (int p : positions[digit]) {
                    if (steps[p] == -1) {
                        next_q.push(p);
                        steps[p] = cur + 1;
                    }
                }
            }
            q.swap(next_q);
            cur++;
        }
        return -1;
    }
    static void unittests() {
        assert(solve("0") == 0);
        assert(solve("1") == 0);
        assert(solve("00000") == 1);
        assert(solve("01230") == 1);
        assert(solve("0123456789") == 9);
        assert(solve("0173456789") == 5);
        assert(solve("0512348568789") == 5);
    }
};

int main() {
    Solution::unittests();
    string s; cin >> s;
    cout << Solution::solve(s) << '\n';
}