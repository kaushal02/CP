/*
https://www.interviewbit.com/problems/rotated-sorted-array-search/

O(log N)
*/
int Solution::search(const vector<int> &A, int B) {
    int N = A.size();
    
    int l = 0, r = N - 1, m, i;
    while (l < r) {
        m = (l + r) / 2;
        if (A[m] < A[0]) r = m;
        else l = m + 1;
    }
    if (A[l] < A[0]) {
        // search [begin,l)
        i = lower_bound(A.begin(), A.begin() + l, B) - A.begin();
        if (i < N and A[i] == B) return i;
        // search [l,end)
        i = lower_bound(A.begin() + l, A.end(), B) - A.begin();
        if (i < N and A[i] == B) return i;
    }
    else {
        // search [begin,end)
        i = lower_bound(A.begin(), A.end(), B) - A.begin();
        if (i < N and A[i] == B) return i;
    }
    return -1;
}
