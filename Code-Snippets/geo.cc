4// Do I wanna know
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;

#define X first
#define Y second
#define sz(c) (int)c.size()
#define rep(i,n) for(int i = 0, _n = (n); i < _n; i++)
#define rep1(i,a,b) for(int i = a, _b = (b); i <= _b; i++)
#define rep2(i,b,a) for(int i = b, _a = (a); i >= _a; i--)
#define mem(a,val) memset(a, (val), sizeof a)
#define mp make_pair
#define eb emplace_back // tie, ignore, get<i>(a)
#define all(c) (c).begin(), (c).end()
#define uni(c) c.resize(distance(c.begin(), unique(all(c))))
#define case(ans) cout<<"Case #"<<_t<<": "<<ans<<"\n"
#define cout(d) cout<<fixed<<setprecision(d)
#define err(x) cerr << #x << " = " << x << '\n'
const ll mod = 1e9 + 7, N = 1e6 + 10;
const double eps = 1e-9;
//==================================================================================
struct point {
    double x, y;
    point() {}
    point(double _x, double _y): x(_x), y(_y) {}
    
    double dis(point a = point()){return sqrt((a.x-x)*(a.x-x) + (a.y-y)*(a.y-y));}
    
    double operator * (point a){return x*a.x + y*a.y;} // Dot product
    double operator % (point a){return x*a.y - y*a.x;} // Cross product
    
    point operator + (point a){return point(x+a.x, y+a.y);}
    point operator - (point a){return point(x-a.x, y-a.y);}
    point operator * (double k){return point(x*k, y*k);}
    point operator / (double k){assert(k > eps);return point(x/k, y/k);}
};
typedef vector<point> vp;
ostream& operator << (ostream& os, point& p) {
  os << "(" << p.x << ", " << p.y << ")\n";
  return os;
}
istream& operator >> (istream& is, point& p) {
  is >> p.x >> p.y;
  return is;
}
bool operator < (const point &a, const point& b) {
    if(fabs(a.x-b.x) < eps) return a.y < b.y;
    return a.x < b.x;
}
point operator * (double n, point p){
    return p*n;
}
point dir(point p) {
    // Direction Vector of p
    if(p.dis() < eps) return point();
    return p/p.dis();
}

//==================================================================================
double area(point a, point b, point c = point()) {
    return fabs((a%b)+(b%c)+(c%a))/2;
}
double peri(point a, point b, point c = point()) {
    return a.dis(b)+b.dis(c)+c.dis(a);
}

//==================================================================================
// Centers
//==================================================================================
point foot(point p1, point p2, point p3 = point()) {
    // Foot on the line p1<->p2 from p3
    if(area(p1, p2, p3) < eps) return p3;
    return p1 + ((p3-p1)*dir(p2-p1))*dir(p2-p1);
}
bool line_line(point p1, point p2, point p3, point p4, point& p) {
    // two lines given by p1<->p2, p3<->p4. p is the intersection point
    double d = (p2-p1)%(p4-p3);
    if(fabs(d) < eps) return false;
    d = ((p4-p3)%(p1-p3))/d;// using sine rule.
    p = p1 + (p2-p1)*d;
    return true;
}
bool orthocentre(point p1, point p2, point p3, point& p) {
    if(area(p1, p2, p3) < eps) return false;
    return line_line(p1, foot(p2, p3, p1), p2, foot(p1, p3, p2), p);
}
bool circumcentre(point p1, point p2, point p3, point& p) {
    if(area(p1, p2, p3) < eps) return false;
    point a1, a2, b1, b2;
    a1 = (p2+p3)/2;
    a2 = (p1+p3)/2;
    b1.x = a1.x - (p3.y-p2.y);
    b1.y = a1.y + (p3.x-p2.x);
    b2.x = a2.x - (p3.y-p1.y);
    b2.y = a2.y + (p3.x-p1.x);
    return line_line(a1, b1, a2, b2, p);
}
bool incentre(point p1, point p2, point p3, point& p) {
    if(area(p1, p2, p3) < eps) return false;
    double s1, s2, s3, w;
    s1 = p2.dis(p3);
    s2 = p1.dis(p3);
    s3 = p1.dis(p2);
    point a1,a2;
    w = s2/(s2+s3);
    a1 = p2*w + p3*(1-w);
    w = s1/(s1+s3);
    a2 = p1*w + p3*(1-w);
    return line_line(a1, p1, a2, p2, p);
}

//==================================================================================
// Angles
//==================================================================================
double angle(point p1, point p2, point p3) {
    // angle from p1->p2 to p1->p3 in (-M_PI, M_PI]
    point va = dir(p2-p1);
    point vb(-va.y, va.x);
    return(atan2((p3-p1)*vb, (p3-p1)*va));
}
double angle(double s1, double s2, double s3) {
    // included angle of s2 and s3 in [0, M_PI]
    assert(s1+s2>s3+eps && s2+s3>s1+eps && s3+s1>s2+eps);
    return acos((s2*s2 + s3*s3 - s1*s1)/(2*s2*s3));
}
point rotate(point p1, point p0, double a) {
    // rotate p1 around p0 anti-clockwise, by angle a
    p1 = p1-p0;
    point ans;
    ans.x = cos(a)*p1.x - sin(a)*p1.y;
    ans.y = sin(a)*p1.x + cos(a)*p1.y;
    return p0 + ans;
}
double deg(double a) {
    return (180/acos(-1)) * a;
}
double rad(double a) {
    return (acos(-1)/180) * a;
}

//==================================================================================
// Location code
//==================================================================================
int p_line(point p1, point p2, point p) {
    // (0) Without (1) Within (-1) Extended+Endpoint
    point f = foot(p1,p2,p);
    if(p.dis(f) > eps) return 0;
    return dir(f-p1).dis(dir(p2-f)) < eps ? 1:-1;
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

inline void MAIN(int _t) {
    
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    
    int Tests = 1;
    //scanf("%d", &Tests);
    rep1(i,1,Tests) MAIN(i);
    return 0;
}