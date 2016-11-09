/*
Problem to find k-th order statistic in optimal way. Some unnecessary steps taken to avoid TLE.
I modified quick sorting to handle the task. Repeated elements help reduce the time complexity of this code.

https://courses.edx.org/courses/course-v1:ITMOx+I2CPx+3T2016/courseware/3e4889eff12145bbb546d72c531cf952/87c0d792bf1b4616bcc0e56f4e0c3d59/
from the course "ITMOx: I2CPx How to win coding competitions: secrets of champions" on edX

O(N) in average
*/
#include <tuple>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
const int N = 4E7 + 10;
int a[N], k;

unsigned int x = 0x12A01, y = 0x341B1, z = 0xA324, w = 0x4320B;
unsigned int myrand() {
    // This RNG generates float in the range [0, 1], with a precision of 10 digits
    // It is nearly 6% faster than regular std::rand() function
    // Visit "https://en.wikipedia.org/wiki/Xorshift" for more details
    unsigned int t = x;
    t ^= t << 11;
    t ^= t >> 8;
    std::tie(x, y, z) = std::tie(y, z, w);
    w ^= w >> 19;
    w ^= t;
    return w;
}

inline int kth(int i, int j) {
    // K-th order statistics using quick-sort. Address mode the container.
    if(i == j) return a[i];
    
    int s(i), e(j), M(a[i + myrand() % (j - i + 1)]);
    while(s <= e) {
        while(s <= j and a[s] < M) s++;
        while(e >= i and M < a[e]) e--;
        if(s <= e) std::swap(a[s++], a[e--]);
    }
    if(i <= e and k <= e) return kth(i, e);
    if(s <= j and s <= k) return kth(s, j);
    return M;
}

int main() {
    freopen("kth.in","r",stdin);
    freopen("kth.out","w",stdout);

    int n, k1, k2, req; std::cin >> n >> k1 >> k2; req = k2 - k1 + 1;
    int p, q, r; std::cin >> p >> q >> r >> a[0] >> a[1];
    for(int i = 2; i < n; i++) a[i] = a[i-2] * p + a[i-1] * q + r;
    
    int x1, x2;
    k = k1 - 1; x1 = kth(0, n-1);
    k = k2 - 1; x2 = kth(0, n-1);
    
    std::vector<int> ans;
    int les(0), occ(0);
    for(int i = 0; i < n; i++) {
        if(a[i] < x1) les++;
        else if(a[i] == x1) occ++;
        else if(a[i] < x2) ans.emplace_back(a[i]);
    }
    int o1 = std::min(req, les + occ - (k1 - 1)); while(o1--) ans.emplace_back(x1);
    int o2 = req - (int)ans.size(); while(o2--) ans.emplace_back(x2);
    sort(ans.begin(), ans.end());
    
    for(int x: ans) std::cout << x << ' ';
    return 0;
}
