#include <iostream>
#include <vector>
#include <stack>
#include <cassert>
using namespace std;

long long maxArea(vector <int> heights) {
    int n = heights.size();

    long long ans = 0;
    stack <int> left;
    vector <int> leftIdx(n);
    for (int i = 0; i < n; i++) {
        while (!left.empty() and heights[left.top()] >= heights[i]) {
            ans = max(ans, (long long) (i - leftIdx[left.top()]) * heights[left.top()]);
            left.pop();
        }
        leftIdx[i] = (left.empty() ? 0 : left.top() + 1);
        left.push(i);
    }
    while (!left.empty()) {
        int top = left.top(); left.pop();
        int leftIndex = (left.empty() ? 0 : left.top() + 1);
        ans = max(ans, (long long) (n - leftIndex) * heights[top]);
    }
    return ans;
}

void unittests() {
    assert(maxArea({1}) == 1);
    assert(maxArea({10}) == 10);
    assert(maxArea({1,1,1,1}) == 4);
    assert(maxArea({1,2,4,5}) == 8);
    assert(maxArea({1,2,3,4,5}) == 9);
    assert(maxArea({3,7,4,5,2,3,3,3}) == 16);
}

int main() {
    // your code goes here
    unittests();

    int n; cin >> n;
    while (n) {
        vector <int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        cout << maxArea(a) << '\n';
        cin >> n;
    }
    return 0;
}