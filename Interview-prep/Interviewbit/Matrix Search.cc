/*
https://www.interviewbit.com/problems/matrix-search/

O(log N + log M)
*/
int Solution::searchMatrix(vector<vector<int>> &A, int B) {
    int N = A.size(), M = A.back().size(), l, r, m;
    
    l = 0, r = N - 1;
    while (l < r) {
        m = (l + r + 1) / 2;
        if (A[m][0] <= B) l = m;
        else r = m - 1;
    }
    if (A[l][0] > B) return 0;
    int row = l;
    
    l = 0, r = M - 1;
    while (l <= r) {
        m = (l + r) / 2;
        if (A[row][m] < B) l = m + 1;
        else if (A[row][m] > B) r = m - 1;
        else return 1;
    }
    return 0;
}
