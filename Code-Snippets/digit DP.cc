int k;

map<int,int> memo[20];
inline int f(int len, int sum) {
    if(!len) return sum == k; // modify value
    if(memo[len].find(sum) != memo[len].end())
        return memo[len][sum];
    
    int ans(0);
    rep(i,10) ans += f(len-1, sum+i); // modify 'sum'
    return memo[len][sum] = ans;
}

inline int tot(int n) {
    if(!n) return 0;
    rep(i,20) memo[i].clear();
    
    int d[20], len(0);
    int ncopy = n;
    while(n) d[len++] = n%10, n/=10;
    
    int ans(0), p(0), pcopy;
    for(int i=len; i--; ) {
        pcopy = p;
        rep1(j,0,d[i]) {
            p = pcopy + j; // modify 'p'
            if(j < d[i]) ans += f(i,p);
        }
    }
    return ans;
}