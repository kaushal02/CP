#include <iostream>
#include <map>
using namespace std;

const string OUTPUTS[4] = {"neither", "homo", "hetero", "both"};

int main() {
    // your code goes here
    int ops; cin >> ops;
    map <int, int> counts;
    int cur_count = 0;
    while (ops--) {
        string op; cin >> op;
        int n; cin >> n;
        if (op == "insert") {
            counts[n]++;
            cur_count++;
        } else if (op == "delete") {
            if (counts[n] > 1) {
                counts[n]--;
                cur_count--;
            } else {
                if (counts[n] == 1) {
                    cur_count--;
                }
                counts.erase(n);
            }
        }
        int sz = counts.size();
        cout << OUTPUTS[(sz < cur_count) + 2 * (sz > 1)] << '\n';
    }
    return 0;
}