struct dsu {
	vi par, sz;
	dsu(int n): par(n), sz(n), iota(all(par),0) {}
	int root(int a) { return par[a] == a ? a:par[a]=root(par[a]);}
	void merge(int a, int b) {
		a=root(a), b=root(b);
		if(a==b)return;
		if(sz[a]<sz[b])swap(a,b);
		sz[a]+=sz[b];
		par[b]=a;
	}
};
template<class T> struct dsu {
	map<T,T> par,sz;
	T root(T a) {
		if(par.find(a)==par.end() or par[a]==a) return par[a]=a;
		return par[a]=root(par[a]);
	}
	// same merge
}
