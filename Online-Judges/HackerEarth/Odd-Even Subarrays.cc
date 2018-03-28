/*
_subarray

Find the number of subarrays having equal number of odd and even elements
https://www.hackerearth.com/challenge/competitive/airtel-crack-the-code/algorithm/odd-even-subarrays-72ad69db/
Codeshare link: https://codeshare.io/Gqlz4x
O(nlogn)
*/
#include <bits/stdc++.h>
int main() {
#define int long long

    std::map<int,int> yet;
    int n, x, off=0, ans=0;
    std::cin >> n; while(n--) {
        yet[off]++;
        std::cin >> x;
        ans += yet[off+=(x&1 ? 1:-1)];
    }
    std::cout << ans;
    return 0;
}