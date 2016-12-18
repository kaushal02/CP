int pref[1001000];
template <typename T>
void prefixarr(T& s) {
    // pref[i] denotes 'j' such that s[0..j-1] == s[i-j+1..i]
    int i = 1, j = 0, n = s.size();
    rep(k,n) pref[k] = 0;
    while(i < n)
        if(s[i] == s[j]) pref[i++] = ++j;
        else if(j) j = pref[j-1];
        else i++;
}

template <typename T>
vi kmp(T& s, T t) {
    // finds list of occurrences of t in s
    int m = s.size(), n = t.size(), i, j;
    prefixarr(t);
        
    vi occur_pos;
    i = j = 0;
    while(i < m) {
        if(s[i] == t[j]) i++, j++;
        else if(j > 0) j = pref[j-1];
        else i++;
        
        if(j == n) occur_pos.pb(i-n), j = pref[j-1];
    }
    return occur_pos;
}

template <typename T>
vi manacher(T& s) {
    // len[i] denotes length of maximal palindrome centered at i-1>>1
    int n = s.size();
    n = n<<1|1;
    vi len(n);
    len[0] = 0, len[1] = 1;
    
    bool expand;
    int c = 1, r = 2, ii, diff;
    
    for(int i = 2; i < n; i++) {
        ii = 2*c - i;
        expand = false;
        diff = r - i;
        
        if(diff > 0)
            if(len[ii] < diff) len[i] = len[ii];
            else if(len[ii] > diff) len[i] = diff, expand = true;
            else if(i == n-1) len[i] = len[ii];
            else len[i] = len[ii], expand = true;
        else len[i] = 0, expand = true;
        
        if(expand)
            while(i + len[i] + 1 < n and i > len[i] and ((i + len[i]) % 2 \
                    or s[i + len[i] + 1 >> 1] == s[i - len[i] - 1 >> 1]))
                len[i]++;
        
        if(i + len[i] > r) r = i + len[i], c = i;
    }
    return len; // start = (id - len[id]) / 2, len[id] being maximum
}

int suff[N], srank[N];
template <typename T>
inline void suffixarr(T& s) {
    // srank[i] denotes the rank of s[i..end]
    // suff[i] denotes id such that s[id..end] is i'th best suffix
    int n = s.size(), lvl(20); // increase lvl if size > 1e6
    vector<pair<pii,int>> id(n);
    vi ranks[lvl]; rep(i,lvl) ranks[i].reserve(n);
    
    rep(i,n) ranks[0][i] = s[i];
    for(int len = 1, cur = 1; len < n; len <<= 1, cur++) {
        rep(i,n) {
            id[i].X.X = ranks[cur-1][i];
            id[i].X.Y = (i + len < n ? ranks[cur-1][i+len]:-1);
            id[i].Y = i;
        }
        sort(all(id));
        
        int rk(0);
        ranks[cur][id[0].Y] = rk;
        rep1(i,1,n-1) {
            if(id[i].X > id[i-1].X) rk++;
            ranks[cur][id[i].Y] = rk;
        }
    }
    rep(i,n) suff[i] = id[i].Y;
    rep(i,n) srank[suff[i]] = i;
}