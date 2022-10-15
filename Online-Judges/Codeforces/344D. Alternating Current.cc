#include <iostream>
#include <stack>
#include <cassert>
using namespace std;

class Solution {
public:
    static bool entangled(string s) {
        stack <char> st;
        for (char c : s) {
            if (!st.empty()) {
                if (st.top() == c) {
                    st.pop();
                    continue;
                }
            }
            st.push(c);
        }
        return !st.empty();
    }

    static void unittests() {
        assert(!entangled(""));
        assert(!entangled("++"));
        assert(!entangled("--"));
        assert(entangled("-"));
        assert(entangled("+"));
        assert(!entangled("++--"));
        assert(!entangled("+-++-+"));
    }
};

int main() {
    // your code goes here
    Solution::unittests();

    string s; cin >> s;
    cout << (Solution::entangled(s) ? "No" : "Yes");
    return 0;
}