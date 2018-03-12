bool vis[N];
int n, a[N][N], par[N];
inline int mst() {
    // Prim's algorithm for Adjacency Matrices
    // O(n^2) minimum spanning tree
    mem(par, -1);
    mem(vis, false);
    bool error = false;
    
    vi key(n,INT_MAX);
    par[0] = key[0] = 0;
    
    int ans(0); // weight of MST
    rep(i,n) {
        int mi(INT_MAX), k(-1);
        rep(j,n) {
            if(!vis[j] and key[j] < mi)
                mi = key[j], k = j;
        }
        if(k == -1) {
            error = true;
            break;
        }
        vis[k] = true;
        ans += key[k]; // modify
        rep(j,n) {
            if(!vis[j] and a[k][j] != 0 and a[k][j] < key[j])
                par[j] = k, key[j] = a[k][j];
        }
    }
    if(error) ans = -1;
    return ans;
}