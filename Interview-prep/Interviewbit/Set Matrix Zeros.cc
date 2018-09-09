/*
https://www.interviewbit.com/problems/set-matrix-zeros/

O(Linear)
*/
void Solution::setZeroes(vector<vector<int>> &A) {
    int r0=1; for(int j=0; j<A[0].size(); j++) r0 &= A[0][j];
    int c0=1; for(int i=0; i<A.size(); i++) c0 &= A[i][0];
    for(int i=1; i<A.size(); i++) {
        for(int j=1; j<A[i].size(); j++) {
            A[i][0] &= A[i][j];
        }
    }
    for(int j=1; j<A[0].size(); j++) {
        for(int i=1; i<A.size(); i++) {
            A[0][j] &= A[i][j];
        }
    }
    for(int i=1; i<A.size(); i++) {
        for(int j=1; j<A[i].size(); j++) {
            A[i][j] &= A[i][0] & A[0][j];
        }
    }
    for(int j=1; j<A[0].size(); j++) A[0][j] &= r0;
    for(int i=1; i<A.size(); i++) A[i][0] &= c0;
    A[0][0] &= r0 & c0;
}
