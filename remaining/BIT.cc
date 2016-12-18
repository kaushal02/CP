ll bt[N][N], a[N][N], nb;
inline void upd(int x, ll val) {
    x++;
    for(int i=x; i<=n; i+=i&-i)
            bt[i][j]+=val;
}
inline ll sumh(int x, int y) {
    ll sum=0;
    for(int i=x; i>0; i^=i&-i)
        for(int j=y; j>0; j^=j&-j)
            sum+=bt[i][j];
    return sum;
}
inline ll sum(int x, int y, int X, int Y) {
    X++, Y++;
    return sumh(X,Y) - sumh(X,y) - sumh(x,Y) + sumh(x,y);
}
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

template<class T>
struct bit {
    T *bt; int n;
    bit() {}
    bit(int n_):n(n_) { bt=(T*)calloc(n+1,sizeof(T));}
    void cons(int n_) { n = n_; bt=(T*)calloc(n+1,sizeof(T));}
    void reset() {memset(bt,0,sizeof(T)*(n+1));}
    void add(int l,int r,T v=1) {
        l+=1,r+=2;
        while(l<=n)bt[l]+=v,l+=l&-l;
        while(r<=n)bt[r]-=v,r+=r&-r;
    } // add v to arr[l..r]
    T get(int u) {T r=0;u++;while(u)r+=bt[u],u^=u&-u;return r;} // arr[u]
};

template<class T>
struct bit {
    T *b1,*b2; int n;
    bit() {}
    bit(int n_): n(n_) {
        b1=(T*)calloc(n+1,sizeof(T));
        b2=(T*)calloc(n+1,sizeof(T));
    }
    void cons(int n_) {
        n = n_;
        b1=(T*)calloc(n+1,sizeof(T));
        b2=(T*)calloc(n+1,sizeof(T));
    }
    void reset() {
        memset(b1,0,sizeof(T)*(n+1));
        memset(b2,0,sizeof(T)*(n+1));
    }
    void add_helper(T*bt,int u,T v) {while(u<=n)bt[u]+=v,u+=u&-u;}
    void add(int l,int r,T v) {
        l++,r++;        
        add_helper(b1,l,v);
        add_helper(b1,r+1,-v);
        add_helper(b2,l,v*(l-1));
        add_helper(b2,r+1,-v*r);
    } // add v to arr[l..r]
    T sum_helper(T*bt,int u) {T r=0;while(u)r+=bt[u],u^=u&-u;return r;}
    T sum_left(int u) {return sum_helper(b1,u)*u-sum_helper(b2,u);} // sum[0..u-1]
    T sum(int l,int r) {return sum_left(r+1)-sum_left(l);} // sum[l..r]
    T get(int u) {return sum_helper(b1,u+1);} // arr[u]
};