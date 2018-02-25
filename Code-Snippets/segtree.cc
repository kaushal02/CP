typedef int node;
int arr[N];
node tree[N<<2], lazy[N<<2];
inline node merge(node a, node b) {
    // put the logic
}
void build(int nd=1, int a=0, int b=n-1) {
    if(a>b) return;
  	if(a==b) {tree[nd]=arr[a]; return;} // modify
	build(nd<<1, a, a+b>>1);
	build(nd<<1|1, a+b+2>>1, b);
	tree[nd]=merge(tree[nd<<1], tree[nd<<1|1]);
}
void update(int i=0, int j=n-1, int v, int nd=1, int a=0, int b=n-1) {
    if(lazy[nd]) {
        tree[nd]=merge(tree[nd], lazy[nd]);
        if(a != b) lazy[nd<<1]=merge(lazy[nd<<1], lazy[nd]),\
                    lazy[nd<<1|1]=merge(lazy[nd<<1|1], lazy[nd]);
        lazy[nd]=0;
    }
    if(a>b or b<i or j<a) return;
  	if(i<=a and b<=j) {
        tree[nd]=v; // modify
        if(a != b) lazy[nd<<1]=v, lazy[nd<<1|1]=v; // modify
        return;
  	}
    update(i, j, v, nd<<1, a, a+b>>1);
	update(i, j, v, nd<<1|1, a+b+2>>1, b);
    tree[nd]=merge(tree[nd<<1], tree[nd<<1|1]);
}
node query(int i=0, int j=n-1, int nd=1, int a=0, int b=n-1) {
	if(a>b or b<i or j<a) return 0;
	if(lazy[nd]) {
        tree[nd]=merge(tree[nd], lazy[nd]);
        if(a != b) lazy[nd<<1]=merge(lazy[nd<<1], lazy[nd]),\
                    lazy[nd<<1|1]=merge(lazy[nd<<1|1], lazy[nd]);
        lazy[nd]=0;
    }
    if(i<=a and b<=j) return tree[nd];
    node q1=query(i, j, nd<<1, a, a+b>>1);
	node q2=query(i, j, nd<<1|1, a+b+2>>1, b);
	return merge(q1, q2);
}


struct node {

}; // modify
int n, arr[N];
node tree[N << 2];
inline node merge(node a, node b) {
    // put the logic
}
void build(int nd=1, int a=0, int b=n-1) {
    if(a>b) return;
  	if(a==b) {
        tree[nd]=arr[a];
        return;
    } // modify
	build(nd<<1, a, a+b>>1);
	build(nd<<1|1, a+b+2>>1, b);
	tree[nd]=merge(tree[nd<<1], tree[nd<<1|1]);
}
void update(int i, int val, int nd=1, int a=0, int b=n-1) {
    if(a>b or b<i or i<a) return;
  	if(a==b) {
        tree[nd]=val;
        return;
  	} // modify
    update(i, x, y, nd<<1, a, a+b>>1);
	update(i, x, y, nd<<1|1, a+b+2>>1, b);
	/// WRONG????????
}
node query(int i=0, int j=n-1, int nd=1, int a=0, int b=n-1) {
	if(a>b or b<i or j<a) return 0; // modify
    if(i<=a and b<=j) { return tree[nd];} // modify
    node q1=query(i, j, nd<<1, a, a+b>>1);
	node q2=query(i, j, nd<<1|1, a+b+2>>1, b);
	return merge(q1, q2);
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/
int n, a[N];
#define node int
node t[N<<1];
inline node merge(node a, node b) {}
inline void build() {
    for(int i=n; i--; ) t[n+i]=node(a[i]);
    for(int i=n; --i; ) t[i]=merge(t[i<<1], t[i<<1|1]);
}
inline void upd(int p, int v) {
    t[n+p]=node(v); // t[n+p]=merge(t[n+p],node(v));
    for(int i=n+p; i>>=1; ) t[i]=merge(t[i<<1], t[i<<1|1]);
}
inline node get(int l, int r) {
    node lt(0), rt(0); // identity
    for(l+=n,r+=n+1; l<r; l>>=1,r>>=1) {
        if(l&1) lt=merge(lt, t[l++]);
        if(r&1) rt=merge(t[--r], rt);
    }
    return merge(lt,rt);
}
