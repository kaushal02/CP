// https://code.google.com/codejam/contest/32003/dashboard#s=p0

// g++ -std=c++11 -O2 -fmax-errors=1
#include <bits/stdc++.h>
using namespace std;

int decode(string num, string base) {
	int nbase = base.size();
	int val[128]; for(int i=0; i<nbase; i++) val[base[i]] = i;

	int ans=0, mul=1;
	reverse(num.begin(), num.end());
	for(char c: num) {
		ans += val[c] * mul;
		mul *= nbase;
	}
	return ans;
}
string encode(int num, string base) {
	int nbase = base.size();
	char sym[128]; for(int i=0; i<nbase; i++) sym[i] = base[i];

	string ans="";
	while(num) {
		ans += sym[num%nbase];
		num /= nbase;
	}
	reverse(ans.begin(), ans.end());
	return ans;
}

int main() {
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	int t; cin >> t;
	for(int _t=1; _t<=t; _t++) {
        string s, a, b; cin >> s >> a >> b;
        cout << "Case #" << _t << ": " << encode(decode(s, a), b) << "\n";
	}
	return 0;
}
