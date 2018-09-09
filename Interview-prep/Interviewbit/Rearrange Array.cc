/*
https://www.interviewbit.com/problems/rearrange-array/

O(1) space, O(N) time
*/
void Solution::arrange(vector<int> &A) {
    int N = A.size();
    for (int i = 0; i < N; i++) {
        if (A[i] >= N) continue;
        
        int x = A[i], j = i;
        while (A[j] != i) {
            tie(j, A[j]) = make_pair(A[j], N + A[A[j]]);
        }
        A[j] = N + x;
    }
    for (int &a: A) a -= N;
}