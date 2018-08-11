/*
_bitset

https://www.codechef.com/viewsolution/19349222

O(n + q*k*N/32)
*/
#include <iostream>
#include <vector>
#include <bitset>
using namespace std;
 
const int N=101010, B=1010;
 
vector<int> shop[N];
bitset<N> shopIds[B], temp;
inline void shopEntry(int id) {
	for(int x: shop[id]) shopIds[x].reset(id);
	shop[id].clear();
	
	int k; cin >> k;
	while(k--) {
		int x; cin >> x;
		shopIds[x].set(id);
		shop[id].push_back(x);
	}
}
 
int main() {
 
    int n, q; cin >> n >> q;
    for(int i=1; i<=n; i++) shopEntry(i);
 
    while(q--) {
    	int t; cin >> t;
    	if(t==1) {
    		int x; cin >> x;
    		shopEntry(x);
    	}
    	else {
    		int l, r, k; cin >> l >> r >> k;
    		temp.reset();
    		while(k--) {
    			int x; cin >> x;
    			temp |= shopIds[x];
    		}
    		cout << (r-l+1) - ((temp>>l).count() - (temp>>r+1).count()) << '\n';
    	}
    }
 
    return 0;
}