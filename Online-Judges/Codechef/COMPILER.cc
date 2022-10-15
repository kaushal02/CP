#include <iostream>
#include <cassert>
using namespace std;

class Solution {
public:
    static int longestValidPrefixLength(string s) {
        int open = 0, last_balanced_index = -1;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '<') {
                open++;
            } else {
                open--;
                if (open < 0) {
                    break;
                } else if (!open) {
                    last_balanced_index = i;
                }
            }
        }
        return last_balanced_index + 1;
    }
    static void unittests() {
        assert(longestValidPrefixLength("") == 0);
        assert(longestValidPrefixLength("<>") == 2);
        assert(longestValidPrefixLength("<<>>") == 4);
        assert(longestValidPrefixLength("<<>><>") == 6);
        assert(longestValidPrefixLength("<") == 0);
        assert(longestValidPrefixLength(">") == 0);
        assert(longestValidPrefixLength("<>>") == 2);
        assert(longestValidPrefixLength("<><") == 2);
        assert(longestValidPrefixLength("<<><<><>>>><<>") == 10);
    }
};

int main() {
    // your code goes here
    Solution::unittests();

    int cases; cin >> cases;
    while (cases--) {
        string s; cin >> s;
        cout << Solution::longestValidPrefixLength(s) << '\n';
    }
    return 0;
}