int bt[N], a[N], nb;
inline void upd(int x, int val) {
    x++;
    for(int i=x; i<=nb; i+=i&-i)
        bt[i]+=val;
}
inline int sumh(int x) {
    int sum=0;
    for(int i=x; i>0; i^=i&-i)
        sum+=bt[i];
    return sum;
}
inline int sum(int x, int X) {
    X++;
    return sumh(X) - sumh(x);
}
/**********************************/
int bt[N], nb;
inline int get(int x) {
    int sum=0; x++;
    for(int i=x; i>0; i^=i&-i)
        sum+=bt[i];
    return sum;
}
inline void updh(int x, int val) {
    x++;
    for(int i=x; i<=nb; i+=i&-i)
        bt[i]+=val;
}
inline void upd(int x, int X, int val) {
    X++;
    updh(X, -val);
    updh(x, val);
}
/**********************************/
int bt1[N], bt2[N], nb;
inline void updh(int x, int val, int *bt) {
    x++;
    for(int i=x; i<=nb; i+=i&-i)
        bt[i]+=val;
}
inline void upd(int x, int X, int val) {
    X++;
    updh(X, -val, bt1); updh(X, -val*X, bt2);
    updh(x, val, bt1); updh(x, val*x, bt2);
}
inline int sumhh(int x, int *bt) {
    int sum=0;
    for(int i=x; i>0; i^=i&-i)
        sum+=bt[i];
    return sum;
}
inline int sumh(int x) {
    return sumhh(x, bt1)*x - sumhh(x, bt2);
}
inline int sum(int x, int X) {
    X++;
    return sumh(X) - sumh(x);
}
