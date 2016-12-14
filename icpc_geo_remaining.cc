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

bool better(pt p1, pt p2, pt p) {
    // From p, if p1 is better than p2
    dbl cp = (p2-p)%(p1-p);
    if(fabs(cp) < eps)//When either p1 or p2 matches p
        return p.dis(p1) > p.dis(p2);
    return cp < 0;
}
//convex hull in n*n
void vex(vp& pol, vp& pol1) {
    pol1.clear();
    int n = (int)pol.size();
    int st(min_element(all(pol)) - pol.begin());
    int idx(st), next;
    do{
        pol1.pb(pol[idx]);
        next = 0;
        rep(i,n)
            if(better(pol[i], pol[next], pol[idx]))
                next = i;
        idx = next;
    }while(idx != st);
}
//convex hull in n*log n
void vex2(vp pol, vp& pol1) {
    vp().swap(pol1);
    int n = sz(pol), cur, i;
    vp temp(n);
    if(n < 3) { pol1 = pol; return;}
    
    sort(all(pol));
    temp[0] = pol[0]; temp[1] = pol[1]; cur = 2;
    rep1(i,2,n-1) {
        if(pol[i].dis(pol[i-1]) < eps) continue;
        while(cur > 1 and better(pol[i], temp[cur-1], temp[cur-2]))
            cur--;
        temp[cur++] = pol[i];
    }
    rep(i,cur) pol1.pb(temp[i]);
    // turn 180 degree
    rep(i,n) pol[i] = -1*pol[i];
    
    sort(all(pol));
    temp[0] = pol[0]; temp[1] = pol[1]; cur = 2;
    rep1(i,2,n-1) {
        if(pol[i].dis(pol[i-1]) < eps) continue;
        while(cur > 1 and better(pol[i], temp[cur-1], temp[cur-2]))
            cur--;
        temp[cur++] = pol[i];
    }
    rep1(i,1,cur-2) pol1.pb(-1*temp[i]);// rotating 180 again
}
