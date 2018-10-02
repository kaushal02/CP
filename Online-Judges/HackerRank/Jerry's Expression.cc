/*
Linear solution
https://www.hackerrank.com/contests/hourrank-30/challenges/jerrys-expression
*/
#include <iostream>
#include <cstring>
using namespace std;
const int N = 1e6 + 10;

string s;
int k, a[N], dp[N], b[N];
inline pair<pair<int,int>,int> solve(int l) {
    if (a[l] + 1) return {{a[l], a[l]}, l + 1};
    char op = s[l];
    auto lt = solve(l + 1);
    auto rt = solve(lt.second);
    if (op == '-') {
        dp[rt.first.first]++;
        dp[rt.first.second + 1]--;
    }
    return {{lt.first.first, rt.first.second}, rt.second};
}

signed main() {
    memset(a, -1, sizeof a);

    cin >> s;
    int n = s.size();
    for (int i = 0; i < n; i++) {
        a[i] = (s[i] == '?' ? k++ : -1);
    }
    // recursive function with cumulative range sum
    solve(0);
    for (int i = 1; i < k; i++) {
        dp[i] += dp[i - 1];
    }
    // get how many positives and negatives
    int pos = 0, neg = 0;
    for (int i = 0; i < k; i++) {
        if (dp[i] &= 1) neg++;
        else pos++;
    }
    // find minimum numbers
    if (pos == neg) {
        for (int i = 0; i < k; i++) {
            b[i] = 1;
        }
    }
    else if(pos > neg) {
        int c = pos / neg, d = pos % neg;
        for (int i = 0; i < k; i++) {
            if (not dp[i]) b[i] = 1;
            else b[i] = c + (d-- > 0);
        }
    }
    else {
        int c = neg / pos, d = neg % pos;
        for (int i = 0; i < k; i++) {
            if (dp[i]) b[i] = 1;
            else b[i] = c + (d-- > 0);
        }
    }
    // output
    for (int i = 0; i < k; i++) {
        cout << b[i] << '\n';
    }
    return 0;
}