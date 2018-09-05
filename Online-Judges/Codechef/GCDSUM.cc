/*
_inclusion_exclusion _sieve

https://www.codechef.com/viewsolution/19721406

O(n*(m + NlogN))
*/
#include <iostream>
#include <cstring> // memset
using namespace std;
typedef int Int;
#define int long long

const int mod=1e9+7, N=1e5+10;
int a[N], b[25][N], c[N];
Int main() {
    int n, m; cin >> n >> m;
    for(int i=0; i<n; i++) {
    	memset(c, 0, sizeof c);
    	for(int j=0; j<m; j++) {
    		int x; cin >> x;
    		c[x]++;
    	}
    	for(int j=1; j<=N; j++) {
    		for(int k=j; k<=N; k+=j) {
    			b[i][j] += c[k];
    		}
    	}
    }

    for(int j=1; j<N; j++) {
    	int t1=1, t2=1;
    	for(int i=0; i<n; i++) {
    		t1 = t1 * (1 + b[i][j]) % mod;
    		t2 += b[i][j];
    	}
    	a[j] = (t1 - t2 + mod) % mod;
    }

    int ans = 0;
    for(int j=N; j>0; j--) {
    	for(int k=2*j; k<N; k+=j) {
    		a[j] -= a[k];
    	}
    	a[j] = (a[j]%mod + mod) % mod;
    	ans += j*a[j]%mod;
    }
    cout << (ans%mod + mod) % mod;
    return 0;
}
