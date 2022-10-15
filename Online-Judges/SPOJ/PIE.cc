#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <iomanip>
using namespace std;

const double EPS = 1E-4;
const double PI = acos(-1);

bool canDivide(vector <int>& r, int count, double val) {
    if (r.empty()) {
        return count == 0;
    }
    int divided = 0;
    for (int radius : r) {
        divided += (int) ((PI * radius * radius + EPS) / val);
    }
    return divided >= count;
}

void unittests() {
    vector <int> r1(1, 1);
    vector <int> r2(1, 2);
    vector <int> r111(3, 1);
    vector <int> r12 = {1, 2};
    vector <int> r1234 = {1, 2, 3, 4};

    assert(canDivide(r1, 1, PI));
    assert(!canDivide(r1, 1, PI * 1.001));
    assert(canDivide(r2, 1, PI * 4));
    assert(!canDivide(r2, 1, PI * 4.001));
    assert(canDivide(r111, 3, PI));
    assert(!canDivide(r111, 4, PI));
    assert(canDivide(r12, 5, PI));
    assert(!canDivide(r12, 6, PI));
    assert(canDivide(r1234, 30, PI));
    assert(canDivide(r1234, 3, PI));
    assert(!canDivide(r1234, 31, PI));
}

int main() {
    // your code goes here
    unittests();
    int cases; cin >> cases;
    while (cases--) {
        int n, f; cin >> n >> f;
        vector <int> radii(n);
        for (int i = 0; i < n; i++) {
            cin >> radii[i];
        }

        double l = 0, r = 1E9, mi;
        while (r - l > EPS) {
            mi = (l + r) / 2;
            if (canDivide(radii, f + 1, mi)) {
                l = mi;
            } else {
                r = mi;
            }
        }
        cout << fixed << setprecision(4) << l << '\n';
    }
    return 0;
}