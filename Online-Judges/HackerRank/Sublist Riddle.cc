/*
_inclusion_exclusion

Based on the venn-diagram and #ways to distribute all balls of a particular color
https://www.hackerrank.com/contests/sears-dots-arrows/challenges/sublist-riddle
O(linear)
*/
#include <iostream>
#include <cmath>
using namespace std;

typedef long long ll;
#define rep(i,n) for(ll i = 0, _n = (n); i < _n; i++)
const ll mod = 1e9 + 7, N = 1e6 + 10;

inline ll ch(ll n, ll r) {
    ll num(1), den(1);
    rep(i,r) num *= (n - i), den *= (1 + i);
    return (num / den) % mod;
}

ll n, c[N];
int main() {
    int x; cin >> n; rep(i,n) cin >> x, c[x]++;
    
    ll ans(0);
    rep(j,4) {
        ll ans1 = pow(-1,j) * ch(3,j);
        rep(i,N) ans1 = ans1 * (1 + (6-j)*c[i] + (6-2*j)*ch(c[i],2)) % mod;
        ans = (ans + ans1 + mod) % mod;
    }
    cout << ans << '\n';
    return 0;
}
