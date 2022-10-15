#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main() {
    // your code goes here
    int n, m, p;
    cin >> n >> m >> p;
    vector < map <int, int> > inc(n + 1);
    while (p--) {
        int x, y;
        cin >> x >> y;
        inc[x][y]++;
    }
    for (int i = 1; i <= n; i++) {
        int ans = m - 1, last_col = 0, last_value = 0;
        for (auto& kv : inc[i]) {
            if (last_col == kv.first - 1) {
                if (last_value > kv.first + kv.second) {
                    ans = -1;
                    break;
                }
            } else {
                if (last_value > last_col + 1) {
                    ans = -1;
                    break;
                }
            }
            last_col = kv.first;
            last_value = kv.first + kv.second;
            if (kv.first == 1) {
                ans -= kv.second;
            }
            if (kv.first == m) {
                ans += kv.second;
            }
        }
        if (last_col < m and last_value > last_col + 1) {
            ans = -1;
        }
        cout << ans << '\n';
    }

    return 0;
}