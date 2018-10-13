#include <iostream>
using namespace std;

int CircularSubstring(string source, string target) {
    int n = source.size();
    source += source;

    int a[26] = {}, nz = 0;
    for (char c : target) {
        if (not a[c - 'a']++) {
            nz++;
        }
    }

    int min_len = 2 * n;
    for (int i = 0, j = 0; i < 2 * n; i++) {
        if (not --a[source[i] - 'a']) {
            nz--;
        }
        while (a[source[j] - 'a'] < 0) {
            a[source[j++] - 'a']++;
        }
        if (not nz) {
            min_len = min(min_len, i - j + 1);
        }
    }
    return min_len > n ? -1 : min_len;
}

int main() {
    // your code goes here
    cout << CircularSubstring("kecrha", "ack") << '\n';
    return 0;
}