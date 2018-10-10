/*
https://www.interviewbit.com/problems/4-sum/

Most probably O(N^2 * log N).. gotta check though
*/

vector<vector<int>> Solution::fourSum(vector<int> &A, int B) {
    sort(A.begin(), A.end());
    map<int,vector<int>> C;
    set<vector<int>> D;
    int N = A.size();
    for (int i = 0; i < N; i++) { // c
        for (int j = i + 1; j < N; j++) { // d
            int R = B - A[i] - A[j]; // a + b
            for (int a : C[R]) {
                D.insert({a, R - a, A[i], A[j]});
            }
        }
        for (int j = 0; j < i; j++) {
            C[A[j] + A[i]].push_back(A[j]);
        }
    }
    vector<vector<int>> E;
    for (auto d : D) E.push_back(d);
    return E;
}