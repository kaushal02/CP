struct nod {
    ll x, y, val;
    nod(ll _x, ll _y, ll _v):
        x(_x), y(_y), val(_v) {}
};
bool comp(nod l, nod r) {
    return l.val < r.val;
}
 
struct dsu {
    vi par, sz;
    dsu(int n): par(n), sz(n) { rep(i,n) par[i] = i, sz[i] = 1;}
    void adopt(int a, int b) {
        a = dad(a);
        b = dad(b);
        if(sz[a] < sz[b]) swap(a,b);
        
        par[b] = a;
    }
    int dad(int a) { return a == par[a] ? a : par[a] = dad(par[a]);}
    bool dogla(int a, int b) { return dad(a) != dad(b);}
};
 
typedef vector<vector<pii>> vvp;
bool mst_kruskal(vvp& g, vvp& gg) {
    // O(E * log E)
    int n = g.size();
    
    vector<nod> edge;
    rep(i,n)for(auto x: g[i])
        edge.pb(nod(i,x.X,x.Y));
    sort(all(edge), comp);
    
    dsu d(n);
    gg.clear(); gg.resize(n);
    int edgeid(0), k(0), m(edge.size());
    while(edgeid < n-1 and k < m) {
        if(d.dogla(edge[k].x, edge[k].y)) {
            edgeid++;
            d.adopt(edge[k].x, edge[k].y);
            gg[edge[k].x].pb(mp(edge[k].y, edge[k].val));
            gg[edge[k].y].pb(mp(edge[k].x, edge[k].val));
        }
        k++;
    }
    return edgeid == n-1;
}

typedef vector<vector<pii>> vvp;
int mst_prim(vector<vi>& g, vvp& gg) {
    // O(V * V) for g being adj matrix
    int n = g.size();
    // Initialization of keys is important
    vi par(n), vis(n,0), key(n,INT_MAX);
    par[0] = key[0] = 0;
    rep(edgeid, n-1) {
        // initialization to be taken care of
        int mi(INT_MAX), ind;
        rep(i,n)
            // symbol toggles for min-max
            if(!vis[i] && key[i] < mi)
                mi = key[i], ind = i;
        vis[ind] = 1;
        rep(i,n)
            // 1st condition changes with PS
            // 3rd only toggles for the symbol
            if(g[ind][i] && !vis[i] && g[ind][i] < key[i])
                par[i] = ind, key[i] = g[ind][i];
    }
    // The most error-prone part
    rep1(i,1,n-1)
        gg[i].pb(mp(par[i], g[i][par[i]]), gg[par[i]].pb(mp(i, g[par[i]][i]);
}