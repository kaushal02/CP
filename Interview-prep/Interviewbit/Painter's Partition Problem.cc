/*
https://www.interviewbit.com/problems/painters-partition-problem/

O(N * log |V|) where V is the maximum allowed array-sum
*/
int Valid(vector<int> &A, int P, int L) {
    int X = 0;
    for(int a : A) {
        if (a > L) return 0; 
        
        X += a;
        if (X > L) {
            X = a;
            P--;
        }
    }
    if (X) P--;
    return P >= 0;
}
 
int Solution::paint(int A, int B, vector<int> &C) {
    int l = 1, r = 1E9, m;
    while (l < r) {
        m = (l + r) >> 1;
        if (Valid(C, A, m)) r = m;
        else l = m + 1;
    }
    return (long long)B * l % 10000003;
}