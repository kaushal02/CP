/*
https://www.interviewbit.com/problems/matrix-median/

This solution works for any matrix input given rows are sorted
O(N * log M * log |V|) where V is the range of values array elements can take
*/
int Solution::findMedian(vector<vector<int>> &A) {
    int l = A[0][0], r = A[0][0], m;
    for (auto a : A) for (auto b : a) l = min(l, b), r = max(r, b);
    int N = A.size(), M = A[0].size(), Q = N * M;
    while (l <= r) {
        m = (l + r) / 2;
        int X = 0, Y = 0;
        for (auto a : A) X += lower_bound(a.begin(), a.end(), m) - a.begin();
        for (auto a : A) Y += upper_bound(a.begin(), a.end(), m) - a.begin();
        if (X > Q / 2) r = m - 1;
        else if (Y <= Q / 2) l = m + 1;
        else return m;
    }
}