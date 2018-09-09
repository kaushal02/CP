/*
https://www.interviewbit.com/problems/rain-water-trapped/

Linear
*/
void Max(int &a, int b) { if (a < b) a = b;}
int Solution::trap(const vector<int> &A) {
    int N = A.size();
    vector<int> L(A), R(A);
    for (int i = 0; i < N; i++) {
        Max(L[i], (i ? L[i - 1] : 0));
    }
    for (int i = N; i--; ) {
        Max(R[i], (i + 1 < N ? R[i + 1] : 0));
    }
    
    int Ans = 0;
    for (int i = 0; i < N; i++) {
        Ans += min(L[i], R[i]) - A[i];
    }
    return Ans;
}
