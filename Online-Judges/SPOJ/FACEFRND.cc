#include <iostream>
#include <vector>
#include <set>
#include <numeric>
using namespace std;

int main() {
    // your code goes here
    set <int> ffs, fs;
    int n; cin >> n;
    while (n--) {
        int f, m;
        cin >> f >> m;
        while (m--) {
            int ff;
            cin >> ff;
            ffs.insert(ff);
        }
        fs.insert(f);
    }
    for_each(ffs.begin(), ffs.end(), )
    ffs.erase(fs.begin(), fs.end());
    cout << ffs.size();
    return 0;
}