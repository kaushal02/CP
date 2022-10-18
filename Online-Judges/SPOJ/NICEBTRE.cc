#include <iostream>
#include <cassert>
#include <stack>
using namespace std;

int solve(string s) {
    int ans(0);
    stack <int> st;
    for (char c : s) {
        if (c == 'n') {
            st.push(2);
            ans = max(ans, (int) st.size());
            continue;
        }
        while (!st.empty()) {
            if (!--st.top()) {
                st.pop();
            } else {
                break;
            }
        }
    }
    return ans;
}

void unittests() {
    assert(solve("") == 0);
    assert(solve("l") == 0);
    assert(solve("nll") == 1);
    assert(solve("nlnll") == 2);
    assert(solve("nnllnll") == 2);
    assert(solve("nlnlnlnnlll") == 5);
}

int main() {
    unittests();

    int cases; cin >> cases;
    while (cases--) {
        string s; cin >> s;
        cout << solve(s) << '\n';
    }
    return 0;
}