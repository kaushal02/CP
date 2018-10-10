/*
average O(n) space and time
Replacing unordered_map with map gives O(n log n) time and O(n) space
*/

#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

string huffmanDecode(int n, vector<char> keys, vector<string> vals, string encoded) {
    unordered_map <string, int> codes;
    for (int i = 0; i < n; i++) {
        codes.insert({vals[i], keys[i]});
    }
    string decoded = "", cur = "";
    for (char c : encoded) {
        cur += c;
        if (codes.find(cur) != codes.end()) {
            decoded += codes[cur];
            cur = "";
        }
    }
    if (cur != "") {
        decoded += codes[cur];
    }
    return decoded;
}

int main() {
    // your code goes here
    cout << huffmanDecode(
                5,
                {'a', 'b', 'c', 'd', '\n'},
                {"01", "110", "101", "0010", "1111"},
                "1100010110111101"
            ) << "\n";
    return 0;
}