/*
_recursion

Question to find smallest number in the range [2,k] having maximum number of divisors.
Key observation is that any number can have a very small limited number of distinct divisors.
As we are interested in maximising the divisor count while keeping our number as small as possible,
we will only check for numbers of the form 2^a * 3^b * 5^c and so on where a >= b >= c..

Problem link:
https://courses.edx.org/courses/course-v1:ITMOx+I2CPx+3T2016/courseware/5f7ded3dde75420f8da894830d69e7e4/05c1037ba1e2450e931dfbd1c2d1856d/
from the course "ITMOx: I2CPx How to win coding competitions: secrets of champions" on edX

Makes nearly 1E5 calls for k = 1E18.
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

ll p[] = {0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53}, M;
ll pw[20], k, maxd, minn;
unordered_set<ull> vis;
inline void solve(ll n) {
    ull hs = n;
    for(int i = 1; i <= M; i++) {
        hs = hs * 257 + pw[i];
    }
    if(vis.count(hs)) return;
    vis.insert(hs);
    
    ll temp = 1;
    for(int i = 1; i <= M; i++) temp *= 1 + pw[i];
    if(temp > maxd) maxd = temp, minn = n;
    else if(temp == maxd and minn > n) minn = n;
    
    for(int i = 1; i <= M; i++) {
        if(n <= k / p[i] and pw[i] < pw[i-1]) {
            pw[i]++;
            solve(n * p[i]);
            pw[i]--;
        }
    }
}
inline void init() {
    ll temp = 1;
    while(temp <= k / p[M+1]) temp *= p[++M];
    pw[0] = 100;
}
int main() {
    freopen("testgen.in","r",stdin);
    freopen("testgen.out","w",stdout);
    
    cin >> k;
    init();
    solve(1);
    cout << k - minn + 1 << '\n';
    return 0;
}
