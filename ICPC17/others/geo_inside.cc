int p_poly(vp pv, pt p) {
    // (0) Without (1) Within (-1) At
    bool error;
    int n=pv.size();
    pv.pb(pv[0]);
    rep(i,n) if(p_line(pv[i], pv[i+1], p) == 1) return -1;
    rep(i,n) pv[i]=pv[i]-p;
    p=pt();
    dbl a, y;
    while(true) {
        a = (dbl)rand()/1e5;
        error = false;
        rep(i,n) {
            pv[i] = rotate(pv[i], p, a);
            if(fabs(pv[i].x) < eps) error = true;
        }
        if(!error) {
            pv[n] = pv[0];
            rep(i,n) if(pv[i].x * pv[i+1].x < -eps) {
                y = pv[i+1].y - pv[i+1].x * (pv[i].y - pv[i+1].y) / (pv[i].x - pv[i+1].x);
                if(y > 0) error = !error;
            }
            return error;
        }
    }
    return 1;
}
