double angle(point p1, point p2, point p3) {
    // angle from p1->p2 to p1->p3 in (-M_PI, M_PI]
    point va = dir(p2-p1);
    point vb(-va.y, va.x);
    return(atan2((p3-p1)*vb, (p3-p1)*va));
}

int p_poly(vp pv, point p) {
    // (0) Without (1) Within (-1) At
    bool error;
    int n = pv.size();
    pv.push_back(pv[0]);
    rep(i,n)
        if(p_line(pv[i], pv[i+1], p) == 1)
            return -1;
    rep(i,n)
        pv[i] = pv[i] - p;
    p = point();
    double a, y;
    while(true) {
        a = (double)rand()/1e5;
        error = false;
        rep(i,n) {
            pv[i] = rotate(pv[i], p, a);
            if(fabs(pv[i].x) < eps) error = true;
        }
        if(!error) {
            pv[n] = pv[0];
            rep(i,n)
                if(pv[i].x * pv[i+1].x < -eps) {
                y = pv[i+1].y - pv[i+1].x * (pv[i].y - pv[i+1].y) / (pv[i].x - pv[i+1].x);
                if(y > 0) error = !error;
            }
            return error;
        }
    }
    return 1;
}
int sense(point p1, point p2, point p) {
    // (0) at (1) left (-1) right
    double cp = (p1-p)%(p2-p);
    if(fabs(cp) < eps) return 0;
    return cp > 0;
}

bool better(point p1, point p2, point p) {
    // From p, if p1 is better than p2
    double cp = (p2-p)%(p1-p);
    if(fabs(cp) < eps)//When either p1 or p2 matches p
        return p.dis(p1) > p.dis(p2);
    return cp < 0;
}
//convex hull in n*n
void vex(vp& pol, vp& pol1) {
    pol1.clear();
    int n = pol.size();
    int st(min_element(all(pol)) - pol.begin());
    int idx(st), next;
    do{
        pol1.eb(pol[idx]);
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
    rep(i,cur) pol1.eb(temp[i]);
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
    rep1(i,1,cur-2) pol1.eb(-1*temp[i]);// rotating 180 again
}

void cutPoly(vp& pol, point& p1, point& p2, vp& pol1, vp& pol2) {
    // (pol1) + (pol2) = (pol)
    vp pp, pn;
    pp.clear(); pn.clear();
    int i, sg, n = pol.size();
    point q1,q2,r;
    rep(i,n) {
        q1 = pol[i]; q2 = pol[(i+1)%n];
        sg = sense(p1, p2, q1);
        if(sg >= 0) pp.eb(q1);
        if(sg <= 0) pn.eb(q1);
        if(line_line(p1, p2, q1, q2, r))
            if(p_line(q1, q2, r) == 1) {
                pp.eb(r);
                pn.eb(r);
            }
    }
    pol1.clear(); pol2.clear();
    if(pp.size() > 2) vex2(pp, pol1);
    if(pn.size() > 2) vex2(pn, pol2);
}

int isvex(vp& v) {
    // (0) concave (1) convex (-1) convex with some PI angle
    // If the polygon is self intersecting, compute the convex hull and see if both have the same area
    int c[3];
    int n(v.size());
    rep(i,n)
        ++c[sense(v[i], v[(i+1)%n], v[(i+2)%n]) + 1];
    if(c[0] && c[2]) return 0;
    if(c[1]) return -1;
    return 1;
}

struct CP {
    vp p;
    CP(vp& a) {p = a;};
    double stripClosest(vp& strip, double d) {
        sort(all(strip), [](point a, point b){return a.y < b.y;});
        double ans = d;
        int n = strip.size();
        rep(i,n)rep1(j,i+1,min(n-1,i+4))
            ans = min(ans, strip[i].dis(strip[j]));
        return ans;
    }
    double closestUtil(int l, int r) {
        if(l == r) return 1e18; // Inf
        
        int mid = (l + r)/2;
        double dl = closestUtil(l, mid);
        double dr = closestUtil(mid + 1, r);
        double d = min(dl, dr);
        
        vp strip;
        rep1(i,l,r) if(abs(p[i].x - p[mid].x) < d) strip.eb(p[i]);
        return stripClosest(strip, d);
    }
    double closest() {
        sort(all(p));
        return closestUtil(0, sz(p)-1);
    }
};
