/*
https://www.interviewbit.com/problems/numbers-of-length-n-and-value-less-than-k/

_digit_dp _dp
*/
int Solution::solve(vector<int> &A, int B, int C) {
    int allowed[10] = {};
    for (int a: A) allowed[a] = 1;
    
    int p[12];
    for(int i = 0; i < 12; i++) {
        if (i == 0) p[i] = 1;
        else if (i == 1) p[i] = A.size();
        else p[i] = p[i-1] * p[1];
    }
    
    int dC[10], n = 0, C1 = C;
    while (C1) {
        dC[n++] = C1 % 10;
        C1 /= 10;
    }
    if (n < B) return 0;
    if (n > B) return p[B] - (B > 1) * allowed[0] * p[B - 1];
    
    int Ans = B == 1 and allowed[0];
    for (int i = n; i--; ) {
        for (int j = 0; j < dC[i]; j++) {
            if (allowed[j] and (j or i < n - 1)) {
                Ans += p[i];
            }
        }
        if (not allowed[dC[i]]) break;
    }
    return Ans;
}
