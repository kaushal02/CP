#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

long long getCost(vector <int>& height, vector <int>& cost, int final_height) {
    long long ans = 0;
    int n = height.size();
    for (int i = 0; i < n; i++) {
        ans += abs(final_height - height[i]) * cost[i];
    }
    return ans;
}

long long minCost(vector <int>& height, vector <int>& cost) {
    int n = height.size();
    assert(n == cost.size());

    int l = 0, r = 10000, mi;
    while (l < r) {
        mi = (l + r) / 2;
        if (getCost(height, cost, mi) > getCost(height, cost, mi + 1)) {
            l = mi + 1;
        } else {
            r = mi;
        }
    }
    return getCost(height, cost, l);
}


int main() {
    // your code goes here
    int cases; cin >> cases;
    while (cases--) {
        int n; cin >> n;
        vector <int> height(n), cost(n);
        for (int i = 0; i < n; i++) {
            cin >> height[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> cost[i];
        }
        cout << minCost(height, cost) << '\n';
    }
    return 0;
}