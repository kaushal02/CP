/*
https://www.interviewbit.com/problems/triplets-with-sum-between-given-range/

Linear Solution
*/

inline int f(double x, double y, double z) {
    // Checks if given numbers add up in the range (1,2)
    // Observe that if any of them does not exist, they are either 10 or -10
    // And hence the sum total can not lie in this range, so we handled corner cases
    // as well as normal cases together without lots of if-else
    double w = x + y + z;
    return 1 < w and w < 2;
}
inline double lo(vector<double> &v, int i=0) {
    // Returns the i'th lowest value from given vector
    double x = 10, y = 10, z = 10;
    for(double w: v) {
        if(w < x) z = y, y = x, x = w;
        else if(w < y) z = y, y = w;
        else if(w < z) z = w;
    }
    return (i>1 ? z : (i ? y : x));
}
inline double hi(vector<double> &v, int i=0) {
    // Returns the i'th highest value from given vector
    double x = -10, y = -10, z = -10;
    for(double w: v) {
        if(w > x) z = y, y = x, x = w;
        else if(w > y) z = y, y = w;
        else if(w > z) z = w;
    }
    return (i>1 ? z : (i ? y : x));
}
/*
make ranges
A=(0,2/3)
B=[2/3,1]
C=(1,2)

possible scenarios:
A A A: take maximums
A A B: solved later
A A C: take minimums
A B B: take minimums
A B C: take minimums

For A A B, divide A in two
A1=(0,1/3)
A2=[1/3,2/3)

possible scenarios:
A1 A1 B: take maximums
A1 A2 B: take minimums
A2 A2 B: take minimums
*/
int Solution::solve(vector<string> &A) {
    vector<double> a1, a2, a, b, c;
    const double e = 1E-12;
    
    for(string s: A) {
        double d = stod(s);
        if(d < 0) continue;
        if(d < 2./3) a.push_back(d);
        if(d < 1./3) a1.push_back(d);
        else if(d < 2./3) a2.push_back(d);
        else if(d < 1 + e) b.push_back(d);
        else if(d < 2) c.push_back(d);
    }
    
    return f(hi(a), hi(a,1), hi(a,2))
            or f(hi(a1), hi(a1,1), hi(b))
            or f(lo(a1), lo(a2), lo(b))
            or f(lo(a2), lo(a2,1), lo(b))
            or f(lo(a), lo(a,1), lo(c))
            or f(lo(a), lo(b), lo(b,1))
            or f(lo(a), lo(b), lo(c));
}