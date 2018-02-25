template <typename T>
vi kmp(T s, T t) {
    // finds list of occurrences of t in s
    int m = s.size(), n = t.size(), i, j;
    
    vi prefix_arr(n);
    i = j = 0;
    prefix_arr[i++] = 0;
    while(i < n)
        if(t[i] == t[j])
            prefix_arr[i++] = ++j;
        else if(j)
            j = prefix_arr[j-1];
        else
            prefix_arr[i++] = 0, j = 0;
    
    vi occur_pos;
    i = j = 0;
    while(i < m) {
        if(s[i] == t[j])
            i++, j++;
        else if(j > 0)
            j = prefix_arr[j-1];
        else
            i++;
        
        if(j == n) {
            occur_pos.pb(i-n);
            j = prefix_arr[j-1];
        }
    }
    return occur_pos;
}