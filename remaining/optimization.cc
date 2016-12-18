vll M, B; // Y = MX + B
int sz = 0; // size of the above vectors
inline void add(ll m, ll b) {
    // Summon in strictly monotonic order w.r.t. slope 'm'
    while(sz>1 and (dbl)(b-B[sz-2])/(M[sz-2]-m) < (dbl)(B[sz-1]-B[sz-2])/(M[sz-2]-M[sz-1])) {
        M.pop_back();
        B.pop_back();
        sz--;
    }
    M.pb(m);
    B.pb(b);
    sz++;
}

// When queries are non - decreasing
int pt = 0;
inline ll query(ll x) {
    while(pt<sz-1 and x > (dbl)(B[pt]-B[pt+1])/(M[pt+1]-M[pt]))
        pt++;
    return M[pt]*x+B[pt];
}
// When queries are random
inline ll query(ll x) {
    int l=0, r=sz-1;
    while(l<r) {
        m1 = (l+l+r)/3, m2 = (l+r+r)/3;
        // if slopes in add() are increasing, use '<'
        if(x*M[m1]+B[m1] operator x*M[m2]+B[m2]) l = m1;
        else r = m2;
    }
    return x*M[l]+B[l];
}