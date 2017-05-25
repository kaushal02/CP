/*
_stack _queue
*/

#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

int main() {
	int n, m, y=1; cin >> n >> m;
	vector<ull> a(n);
	for(int i=0; i<n; i++) cin >> a[i];
	sort(a.begin(), a.end());

	ull ans;
	stack<ull> s; for(ull x: a) s.push(x);
	queue<ull> q; while(m--) {
		int x; cin >> x;
		while(y <= x) {
			if(s.empty() and !q.empty()) ans=q.front(), q.pop();
			else if(!s.empty() and q.empty()) ans=s.top(), s.pop();
			else if(s.top() > q.front()) ans=s.top(), s.pop();
			else ans=q.front(), q.pop();

			if(ans>1) q.push(ans>>1);
			y++;
		}
		cout << ans << '\n';
	}
	return 0;
}
