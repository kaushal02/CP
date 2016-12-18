vi t[N];
int n, lca[25][N], h[N], start[N], stop[N], tm_;
inline bool is_anc(int a, int v) { // determines if a is ancestor of v
    return start[a] <= start[v] and stop[a] >= stop[v];
}
inline int kth_anc(int v, int k) { // returns k'th ancestor of v
    rep(i,20) {
        if(k & 1) v = lca[i][v];
        k >>= 1;
    }
    return v;
}
inline int get_lca(int u, int v) { // returns LCA
    if(h[u] < h[v]) swap(u,v);
    
    int x = h[u] - h[v];
    rep(i,20) {
        if(x & 1) u = lca[i][u];
        x >>= 1;
    }
    if(u == v) return u;
    
    rep2(i,18,0) if(lca[i][u] != lca[i][v]) u = lca[i][u], v = lca[i][v];
    return lca[0][u];
}
inline void dfs(int v, int p) {
    start[v] = tm_++; // h[v] is the depth of node. h[root] = 0
    lca[0][v] = p; // lca[i][v] is (1<<i)'th ancestor of v, or root
    rep1(i,1,20) lca[i][v] = lca[i - 1][lca[i - 1][v]];
    for(int ch: t[v]) if(ch != p) h[ch] = h[v] + 1, dfs(ch, v);
    stop[v] = tm_++;
}

vi t[N];
int n, lca[25][N], h[N], start[N], stop[N], tm_, e;
inline bool is_anc(int a, int v) { // determines if a is ancestor of v
    return start[a] <= start[v] and stop[a] >= stop[v];
}
inline int kth_anc(int v, int k) { // returns k'th ancestor of v
    rep(i,20) {
        if(k & 1) v = lca[i][v];
        k >>= 1;
    }
    return v;
}
inline int get_lca(int u, int v) { // returns LCA
    if(h[u] < h[v]) swap(u,v);
    
    int x = h[u] - h[v];
    rep(i,20) {
        if(x & 1) u = lca[i][u];
        x >>= 1;
    }
    if(u == v) return u;
    
    rep2(i,18,0) if(lca[i][u] != lca[i][v]) u = lca[i][u], v = lca[i][v];
    return lca[0][u];
}

inline void first_extreme(int v, int p) {
    for(int ch: t[v]) if(ch != p)
        h[ch] = h[v] + 1, first_extreme(ch, v);
}
inline void second_extreme(int v, int p) {
    start[v] = tm_++; // h[v] is the depth of node. h[root] = 0
    lca[0][v] = p; // lca[i][v] is (1<<i)'th ancestor of v, or root
    rep1(i,1,20) lca[i][v] = lca[i - 1][lca[i - 1][v]];
    for(int ch: t[v]) if(ch != p) h[ch] = h[v] + 1, second_extreme(ch, v);
    stop[v] = tm_++;
}
inline void dia() {
    e = 1; // remember that nodes are numbered 1..n
    
    h[e] = 0;
    first_extreme(1,1);
    int x = 0;
    rep1(i,1,n) if(x < h[i]) x = h[i], e = i;
    
    h[e] = 0;
    second_extreme(e,e);
    x = 0;
    rep1(i,1,n) if(x < h[i]) x = h[i], e = i;
}