typedef pair<pii,int> node;
int K, a[N];
inline void add(int i) {}
inline void rem(int i) {}

#undef int
int main() {
#define int ll

	int q; cin >> q; // query count
	K = q/sqrt(n);
	vector<node> qu(q);
	rep(i,q) {
		int x,y; cin>>x>>y;
		qu[i]={{x-1,y-1},i};
	}
	sort(all(qu),[](node l, node r){
		if(l.X.X/K==r.X.X/K) return l.X.Y<r.X.Y;
		return l.X.X<r.X.X;});
	vi ans(q);
	int curl(0), curr(-1), l, r;
	rep(i,q) {
		tie(l,r)=qu[i].X;
		while(curl>l) add(--curl);
		while(curr<r) add(++curr);
		while(curl<l) rem(curl++);
		while(curr>r) rem(curr--);
		ans[qu[i].Y]=getans();
	}
    rep(i,q) cout << ans[i] << ' ';
}
