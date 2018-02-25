inline int kth(int i, int j) {
	if(i==j) return a[i];
	int s(i), e(j), M(a[i]);
	while(s<=e) {
		while(s<=j and a[s]<M) s++;
		while(e>=i and M<a[e]) e--;
		if(s<=e) swap(a[s++], a[e--]);
	}
	if(i<=e and k<=e) return kth(i,e);
	if(s<=j and s<=k) return kth(s,j);
	return M;
}
