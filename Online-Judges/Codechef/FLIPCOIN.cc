/*
_lazy _segment_tree

Given array of all 0s, make the following:
Range update: flip all values
Range query: sum all values

O((N+Q)*log N)
*/
#include <iostream>
#include <bitset>
using namespace std;

const int N=1E5+5;

struct node {
	int val, len;
	void flip() {val=len-val;}
} tree[N<<2];
node operator+(node l, node r) {
	node n;
	n.val = l.val + r.val;
	n.len = l.len + r.len;
	return n;
}

int lazy[N<<2], n;
void build(int nd=1, int a=0, int b=n-1) {
    if(a>b) return;
  	if(a==b) {tree[nd]={0,1}; return;}
	build(nd<<1, a, a+b>>1);
	build(nd<<1|1, a+b+2>>1, b);
	tree[nd] = tree[nd<<1] + tree[nd<<1|1];
}
void update(int i, int j, int nd=1, int a=0, int b=n-1) {
    if(lazy[nd]) {
        tree[nd].flip();
        if(a != b) {
        	lazy[nd<<1] ^= lazy[nd];
            lazy[nd<<1|1] ^= lazy[nd];
        }
        lazy[nd]=0;
    }
    if(a>b or b<i or j<a) {
    	return;
  	}
  	if(i<=a and b<=j) {
        tree[nd].flip();
        if(a != b) {
        	lazy[nd<<1] ^= 1;
        	lazy[nd<<1|1] ^= 1;
        }
        return;
  	}
    update(i, j, nd<<1, a, a+b>>1);
	update(i, j, nd<<1|1, a+b+2>>1, b);
    tree[nd] = tree[nd<<1] + tree[nd<<1|1];
}
node query(int i, int j, int nd=1, int a=0, int b=n-1) {
	if(a>b or b<i or j<a) {
		return {0, 0};
	}
	if(lazy[nd]) {
        tree[nd].flip();
        if(a != b) {
        	lazy[nd<<1] ^= lazy[nd];
            lazy[nd<<1|1] ^= lazy[nd];
        }
        lazy[nd]=0;
    }
    if(i<=a and b<=j) {
    	return tree[nd];
    }
    node q1=query(i, j, nd<<1, a, a+b>>1);
	node q2=query(i, j, nd<<1|1, a+b+2>>1, b);
	return q1 + q2;
}
int main() {
	// your code goes here
	int q, t, a, b;
	scanf("%d%d", &n, &q);
	build();
	while(q--) {
		scanf("%d%d%d", &t, &a, &b);
		if(t==0) update(a, b);
		else printf("%d\n", query(a, b).val);
	}
	return 0;
}