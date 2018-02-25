struct trie{
	int l, r, sum;
	trie() {};
};
trie arr[N];
int nodes_count = 1;
void add(int x, int val, int lvl = 31) {
	int c(0);
	while(lvl--) {
		if(x >> lvl & 1) {
			if(!arr[c].r) arr[c].r = nodes_count++;
			c = arr[c].r;
		}
		else {
			if(!arr[c].l) arr[c].l = nodes_count++;
			c = arr[c].l;
		}
		arr[c].sum += val;
	}
}
int max_xor(int x) {
	int lvl(31), c(0), ans(0);
	while(lvl--) {
		if(x >> lvl & 1) {
			if(!arr[c].l or !arr[arr[c].l].sum) c = arr[c].r;
			else ans |= 1 << lvl, c = arr[c].l;
		}
		else {
			if(!arr[c].r or !arr[arr[c].r].sum) c = arr[c].l;
			else ans |= 1 << lvl, c = arr[c].r;
        }
	}
	return ans;
}