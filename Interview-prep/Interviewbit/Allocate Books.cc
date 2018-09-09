/*
https://www.interviewbit.com/problems/allocate-books/

O(N * log |V|) where V is the maximum allowed array-sum
*/
int check(vector<int> &A, int B, int X) {
    int Y = 0;
    for (int a: A) {
        Y += a;
        if (Y > X) {
            Y = a;
            B--;
        }
    }
    if (Y) B--;
    return B >= 0;
}

int Solution::books(vector<int> &A, int B) {
    int N = A.size();
    int M = 0, S = 0;
    for (int a : A) {
        M = max(M, a);
        S += a;
    }
    if (B > N) return -1;
    int l = M, r = S, m;
    while (l < r) {
        m = (l + r) >> 1;
        if (check(A, B, m)) r = m;
        else l = m + 1;
    }
    return (check(A, B, l) ? l : -1);
}
