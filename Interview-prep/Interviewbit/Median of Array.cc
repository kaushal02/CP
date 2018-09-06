/*
https://www.interviewbit.com/problems/median-of-array/

O(log(m) * log(n))
*/

double Solution::findMedianSortedArrays(const vector<int> &A, const vector<int> &B) {
    int N = A.size(), M = B.size();
    int Ai = 0, Aj = N - 1;
    int Bi = 0, Bj = M - 1;
    while (Ai < Aj and Bi < Bj) {
        if (A[Ai] < B[Bi]) Ai++; else Bi++;
        if (A[Aj] > B[Bj]) Aj--; else Bj--;
    }
    vector<int> V;
    while (Ai <= Aj) V.push_back(A[Ai++]);
    while (Bi <= Bj) V.push_back(B[Bi++]);
    sort(V.begin(), V.end());
    int Vn = V.size();
    return (Vn % 2 ? V[Vn / 2] : (V[Vn / 2] + V[Vn / 2 - 1]) / 2.);
    int T = M + N, ANS, fl = 0;
    int l = 0, r = N - 1, m;
    while (l <= r) {
        m = (l + r) >> 1;
        int x = lower_bound(B.begin(), B.end(), A[m]) - B.begin() + m;
        int y = upper_bound(B.begin(), B.end(), A[m]) - B.begin() + m;
        if (y < (T - 1) / 2) l = m + 1;
        else if (x > T / 2) r = m - 1;
        else if (T & 1) return A[m];
        else if (fl) return (ANS + A[m]) / 2.;
        else {
            fl++;
            ANS = A[m];
            if (x == T / 2) r = m - 1;
            else l = m + 1;
        }
    }
    l = 0, r = M - 1;
    while (l <= r) {
        m = (l + r) >> 1;
        int x = lower_bound(A.begin(), A.end(), B[m]) - A.begin() + m;
        int y = upper_bound(A.begin(), A.end(), B[m]) - A.begin() + m;
        if (y < (T - 1) / 2) l = m + 1;
        else if (x > T / 2) r = m - 1;
        else if (T & 1) return B[m];
        else if (fl) return (ANS + B[m]) / 2.;
        else {
            fl++;
            ANS = B[m];
            if (x == T / 2) r = m - 1;
            else l = m + 1;
        }
    }
    assert(0);
    return ANS;
}
