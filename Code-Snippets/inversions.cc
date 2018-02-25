template<class T>
struct bit {
    T *bt; int n;
    bit() {}
    bit(int n_):n(n_) { bt=(T*)calloc(n+1,sizeof(T));}
    void cons(int n_) { n = n_; bt=(T*)calloc(n+1,sizeof(T));}
    void reset() {memset(bt,0,sizeof(T)*(n+1));}
    void add(int u,T v=1) {u++;while(u<=n)bt[u]+=v,u+=u&-u;} // arr[u] += v
    T sum(int l,int r) {
        T ans=0;r++;
        while(r)ans+=bt[r],r^=r&-r;
        while(l)ans-=bt[l],l^=l&-l;
        return ans;
    } // arr[l]+..+arr[r]
};
template <typename T>
inline ll inversions(vector<T> a) {
    int n = sz(a);
    vector<T> c(a); sort(all(c));

    map<T,int> pos;
    int k(0); for(T x: c) if(!pos.count(x)) pos[x] = k++;

    ll ans(0);
    bit<int> b(k);
    for(T x: a) b.add(pos[x]), ans += b.sum(pos[x] + 1, k - 1);
    return ans;
}
