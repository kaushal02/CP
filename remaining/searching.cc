inline ll search_binary(ll l, ll r) {
    ll l = 0, r = 1e18, mid;
    while(l < r) {
        // get minimum ok
        mid = (l + r) / 2;
        if(ok(mid)) r = mid;
        else l = mid + 1;
        
        // get maximum ok
        mid = (l + r + 1) / 2;
        if(ok(mid)) l = mid;
        else r = mid - 1;
    }
}
inline ll search_ternary(ll l, ll r) {
    ll l = 0, r = 1e18;
    while(l < r) {
        if(f((l+l+r)/3) < f((l+r+r)/3))
            l = (l+l+r)/3;
        else
            r = (l+r+r)/3;
    }
}