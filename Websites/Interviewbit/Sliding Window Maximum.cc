/*
https://www.interviewbit.com/problems/sliding-window-maximum/

Linear
*/
vector<int> Solution::slidingMaximum(const vector<int> &A, int B) {
    deque<int> Q;
    vector<int> C;
    int i = 0, N = A.size();
    while (i < N) {
        while (!Q.empty() and A[Q.back()] <= A[i]) {
            Q.pop_back();
        }
        Q.push_back(i++);
        if (i - Q.front() > B) Q.pop_front();
        if (i >= B) C.push_back(A[Q.front()]);
    }
    return C;
}