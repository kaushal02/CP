struct dsu {
    vi par, sz;
    dsu(int n): par(n), sz(n) { rep(i,n) par[i] = i, sz[i] = 1;}
    void merge(int a, int b) {
        a = dad(a);
        b = dad(b);
        if(sz[a] < sz[b]) swap(a,b);
        
        sz[a] += sz[b];
        par[b] = a;
    }
    int dad(int a) { return a == par[a] ? a : par[a] = dad(par[a]);}
    bool diff(int a, int b) { return dad(a) != dad(b);}
};

template <typename T>
struct dsu {
    map<T,T> par, sz;
    void merge(int a, int b) {
        a = dad(a);
        b = dad(b);
        if(sz[a] < sz[b]) swap(a,b);
        
        sz[a] += sz[b];
        par[b] = a;
    }
    T dad(T a) {
        if(par.find(a) == par.end() or par[a] == a)
            return par[a] = a;
        return par[a] = dad(par[a]);
    }
    bool diff(T a, T b) { return dad(a) != dad(b);}
};