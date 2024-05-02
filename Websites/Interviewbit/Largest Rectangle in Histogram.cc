/*
https://www.interviewbit.com/problems/largest-rectangle-in-histogram/

Linear
*/
int Solution::largestRectangleArea(vector<int> &A) {
    int N = A.size();
    vector<int> L(N);
    vector<int> R(N);
    stack<int> ID;
    for (int i = 0; i <= N - 1; i++) {
        while (!ID.empty() and A[ID.top()] >= A[i]) ID.pop();
        L[i] = (ID.empty() ? 0 : ID.top() + 1);
        ID.push(i);
    }
    while (!ID.empty()) ID.pop();
    for (int i = N - 1; i >= 0; i--) {
        while (!ID.empty() and A[ID.top()] >= A[i]) ID.pop();
        R[i] = (ID.empty() ? N - 1 : ID.top() - 1);
        ID.push(i);
    }
    long long Ans = 0;
    for (int i = 0; i < N; i++) {
        Ans = max(Ans, (R[i] - L[i] + 1LL) * A[i]);
    }
    return Ans;
}
