/*
ABDUL

https://www.codechef.com/problems/CF1921

O((q+n)*log n)
*/

#include <bits/stdc++.h>
using namespace std;
 
int main() {
	int mod = 1E9+7;
	
	int n; cin >> n;
	map<string, long long int> mp;
	while(n--) {
		string s; cin >> s;
		long long int x; cin >> x;
		x %= mod;
		
		string t="";
		for(char c: s) {
			t += c;
			mp[t] = (mp[t] + x) % mod;
		}		
	}
	
	int q; cin >> q;
	while(q--) {
		string s; cin >> s;
		cout << mp[s] << '\n';
	}
	
	return 0;
} 