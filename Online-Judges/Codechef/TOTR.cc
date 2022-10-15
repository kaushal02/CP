#include <iostream>
using namespace std;

int main() {
    // your code goes here
    int cases; cin >> cases;
    string mask; cin >> mask;
    while (cases--) {
        string input; cin >> input;
        for (char c : input) {
            if ('a' <= c and c <= 'z') {
                cout << mask[c - 'a'];
            } else if ('A' <= c and c <= 'Z') {
                cout << (char) ('A' + mask[c - 'A'] - 'a');
            } else if (c == '_') {
                cout << " ";
            } else {
                cout << c;
            }
        }
        cout << '\n';
    }
    return 0;
}
