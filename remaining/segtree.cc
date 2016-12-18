typedef int nod;
int arr[N];
nod tree[N << 2], lazy[N << 2];
inline nod combine(nod a, nod b) {
    // put the logic
}
void build(int node = 1, int a = 0, int b = n-1) {
    if(a > b) return;
  	if(a == b) {tree[node] = arr[a]; return;} // modify
	build(node<<1, a, a+b>>1); 
	build(node<<1|1, a+b+2>>1, b);
	tree[node] = combine(tree[node<<1], tree[node<<1|1]);
}
void update(int i = 0, int j = n-1, int value, int node = 1, int a = 0, int b = n-1) {
    if(lazy[node]) {
        tree[node] = combine(tree[node], lazy[node]);
        if(a != b) lazy[node<<1] = combine(lazy[node<<1], lazy[node]),\
                    lazy[node<<1|1] = combine(lazy[node<<1|1], lazy[node]);
        lazy[node] = 0;
    }
    if(a > b or b < i or j < a) return;
  	if(i <= a and b <= j) {
        tree[node] = value; // modify
        if(a != b) lazy[node<<1] = value, lazy[node<<1|1] = value; // modify
        return;
  	}
    update(i, j, value, node<<1, a, a+b>>1);
	update(i, j, value, node<<1|1, a+b+2>>1, b);
    tree[node] = combine(tree[node<<1], tree[node<<1|1]);
}
nod query(int i = 0, int j = n-1, int node = 1, int a = 0, int b = n-1) {
	if(a > b or b < i or j < a) return 0;
	if(lazy[node]) {
        tree[node] = combine(tree[node], lazy[node]);
        if(a != b) lazy[node<<1] = combine(lazy[node<<1], lazy[node]),\
                    lazy[node<<1|1] = combine(lazy[node<<1|1], lazy[node]);
        lazy[node] = 0;
    }
    if(i <= a and b <= j) return tree[node];
    nod q1 = query(i, j, node<<1, a, a+b>>1); 
	nod q2 = query(i, j, node<<1|1, a+b+2>>1, b);
	return combine(q1, q2);
}


struct nod {
    
}; // modify
int n, arr[N];
nod tree[N << 2];
inline nod combine(nod a, nod b) {
    // put the logic
}
void build(int node = 1, int a = 0, int b = n-1) {
    if(a > b) return;
  	if(a == b) {
        tree[node] = arr[a];
        return;
    } // modify
	build(node<<1, a, a+b>>1); 
	build(node<<1|1, a+b+2>>1, b);
	tree[node] = combine(tree[node<<1], tree[node<<1|1]);
}
void update(int i, int val, int node = 1, int a = 0, int b = n-1) {
    if(a > b or b < i or i < a) return;
  	if(a == b) {
        tree[node] = val;
        return;
  	} // modify
    update(i, x, y, node<<1, a, a+b>>1);
	update(i, x, y, node<<1|1, a+b+2>>1, b);
}
nod query(int i = 0, int j = n-1, int node = 1, int a = 0, int b = n-1) {
	if(a > b or b < i or j < a) return 0; // modify
    if(i <= a and b <= j) { return tree[node];} // modify
    nod q1 = query(i, j, node<<1, a, a+b>>1);
	nod q2 = query(i, j, node<<1|1, a+b+2>>1, b);
	return combine(q1, q2);
}


typedef int nod;
int n, arr[lim];
nod tree[lim << 1];
inline nod combine(nod a, nod b) {
    // Put the logic
}
inline void build() {
    for(int i = n; i--; )
        tree[n + i] = nod(arr[i]);
    for(int i = n; --i; )
        tree[i] = combine(tree[i << 1], tree[i << 1 | 1]); 
}
inline void update(int pos, int value) {
    tree[n + pos] = nod(value); // tree[n + pos] = combine(tree[n + pos], nod(value));
    for(int i = n + pos; i >>= 1; )
        tree[i] = combine(tree[i << 1], tree[i << 1 | 1]);
}
inline nod query(int l, int r) {
    nod ansl(), ansr();
    for(l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
        if(l & 1) ansl = combine(ansl, tree[l++]);
        if(r & 1) ansr = combine(tree[--r], ansr);
    }
    return combine(ansl, ansr);
}