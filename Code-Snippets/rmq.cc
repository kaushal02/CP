const int K = 25;
int n, a[N], lg[N], m[N][K];
inline void init() {
	for (int i = 2; i <= n; i++) {
		lg[i] = lg[i >> 1] + 1;
	}
	for (int j = 0; j < K; j++) {
		for (int i = 0; i <= n - (1 << j); i++) {
			m[i][j] = (j ? min(m[i][j - 1], m[i + (1 << j - 1)][j - 1]): a[i]);
		}
	}
}
inline int rmq(int l, int r) {
	assert(l <= r);
	int k = lg[r - l + 1];
	return min(m[l][k], m[r - (1 << k) + 1][k]);
}
