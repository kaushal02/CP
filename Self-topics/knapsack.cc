/*
_recursion 

Given a list of coin denominations and the number of coins available in each denomination,
the task is to find the minimum number of coins required to exchange for a given value V.
Also, print all possible ways in which this can be done.
*/

#include <bits/stdc++.h>
using namespace std;
const int LIM=1e5, N=10, INF=1e5;

int val[N], cnt[N], memo[LIM][N];
vector<int> used[LIM][N];
inline int solve(int tot, int i) {
	if(!tot) return 0;
	if(i<0) return INF;
	int &ans=memo[tot][i];
	if(~ans) return ans;
	    
	ans=INF;
	vector<int>& vec=used[tot][i];
	for(int c=0; c<=cnt[i]; c++) {
        	int tot2=c*val[i];
        	if(tot2>tot) break;
       		int ans2=c+solve(tot-tot2, i-1);
        	if(ans2>ans) continue;
		if(ans2==ans) vec.push_back(c);
        	if(ans2<ans) vec={c};
		ans=ans2;
	}
	return ans;
}

inline void print(int tot, int i, string line) {
	int pc=0, tot2=tot;
	for(int c: used[tot2][i]) {
		while(pc<c) {
			line += to_string(val[i]) + " ";
			tot -= val[i];
			pc++;
		}
		print(tot, i-1, line);
	}
	if(!tot2) cout << line << '\n';
}

int main() {
	int n; cin >> n;
	for(int i=0; i<n; i++) cin >> val[i] >> cnt[i];
	memset(memo, -1, sizeof(memo));
	
	int v; while(cin>>v) {
	        int ans = solve(v, n-1);
		if(ans<INF) {
			cout << ans << " coin" << (ans>1 ? "s":"") << " required\n";
			print(v, n-1, "");
		} else cout << "Not possible\n";
		cout << '\n';
    	}
	return 0;
}
