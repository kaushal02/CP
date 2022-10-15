#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int LIM = 1E9 + 1;

bool canKeepDistance(vector <int>& a, int count, int distance) {
    if (a.empty()) {
        return count == 0;
    }
    int used = 1, last_pos = a[0];
    for (int i = 1; i < a.size(); i++) {
        if (a[i] - last_pos >= distance) {
            last_pos = a[i];
            used++;
        }
    }
    return used >= count;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    // your code goes here
    int cases; cin >> cases;
    while (cases--) {
        int n, c; cin >> n >> c;
        vector <int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a.begin(), a.end());

        int l = 0, r = LIM, mi;
        while (l < r) {
            mi = l + (r - l + 1) / 2;
            if (canKeepDistance(a, c, mi)) {
                l = mi;
            } else {
                r = mi - 1;
            }
        }
        cout << l << '\n';
    }
    return 0;
}