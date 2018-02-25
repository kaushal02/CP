const int K=25;
int n, a[N], lg[N], m[N][K];
inline void init() {
	lg[0]=-2;
	rep(i,n+1) lg[i]=1+lg[i>>1];
	rep(j,K) {
		if(!j) rep(i,n) { m[i][j]=a[i];}
		else rep(i,n-(1<<j)+1) { m[i][j]=min(m[i][j], m[i+(1<<j-1)][j-1]);}
	}
}
inline int rmq(int l, int r) {
	assert(l<=r);
	int k=lg[r-l+1];
	return min(m[l][k], m[r-(1<<k)+1][k]);
}
