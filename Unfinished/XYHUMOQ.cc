/*
[Codechef] https://www.codechef.com/JAN18/problems/XYHUMOQ
*/
#include <bits/stdc++.h>
using namespace std;
const int INF=100;

struct node {
	int o, z, t;
	node(int a=0, int b=0, int c=0): o(a), z(b), t(c) {}
	node operator+(node a) {
		node c=*this;
		return {c.o+a.o, c.z+a.z, c.t+a.t+c.t*a.t+c.o*a.z};
	}
	void pr() const {cout << o << " " << z << ": " << t << "\n"; }
};

node makenode(vector<int> v) {
	node n;
	if(v.empty()) return n;
	while(!v.empty() and !v.back()) n.z++, v.pop_back();
	while(!v.empty() and v.back()) n.o++, v.pop_back();
	n.t=n.z*n.o;
	return makenode(v)+n;
}

string solve() {
	string s; cin >> s;
	int x; cin >> x;
	int n=s.size(), n1=n/2, n2=n-n1;
	if(n<4) return (x==n-1 ? "YES\n0":"NO");

	map<pair<int,int>,int> flips;
	for(int i=0; i<(1<<n2); i++) {
		vector<int> v(n2);
		for(int j=0; j<n2; j++) v[j]=(i>>j&1);
		if(v.back()) continue;
		node w=makenode(v);
		int d=0; for(int j=0; j<n2; j++) if(s[n1+j]-'0'!=v[j]) d++;
		auto it=flips.find({w.z,w.t});
		if(it==flips.end()) flips[{w.z,w.t}]=d;
		else if(it->second>d) it->second=d;
	}
set<int> st1, st2;
set<pair<int,int>> st3;
	int ans=INF;
n1=16; int c=0;
	for(int i=0; i<(1<<n1); i++) if(i&1) {
		int d=0, tmp=0;
		vector<int> v(n1);
		for(int j=0; j<n1; j++) {
			if(s[j]-'0'!=(i>>j&1)) d++;
			v[j]=(j?v[j-1]:0);
			if(i>>j&1) tmp += 1+v[j];
			else for(int jj=0; jj<j; jj++) if(i>>jj&1) v[j] += 1+(jj?v[jj-1]:0);
		}
st1.insert(v.back());
st2.insert(tmp);
int g=__gcd(v.back(), tmp); st3.insert({v.back()/g,tmp/g});
if(tmp==v.back()) c++;
/*
		for(int j=0; j<=n2; j++) {
			int y=x-v.back()-w.o*j;
			if(y<0) continue;
			if(y%(w.t+1)) continue;
			y/=w.t+1;
			auto it=flips.find({j,y});
			if(it==flips.end()) continue;
			ans=min(ans,d+it->second);
		}
*/
	}
cout << st1.size() << " " << st2.size() << " " << st3.size() << " " << c;
	return (ans==INF ? "NO":"YES\n"+to_string(ans));
}

int main() {
	int t; cin >> t;
	while(t--) cout << solve() << '\n';
	return 0;
}
