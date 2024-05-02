/*
https://www.interviewbit.com/problems/redundant-braces/

Linear
*/

inline int what(char c) {
    // 0: var
    // 1: op
    // 2: (
    // 3: )
    if (c == '+' or c == '-' or c == '*' or c == '/') return 1;
    if (c == '(') return 2;
    if (c == ')') return 3;
    return 0;
}
int Solution::braces(string A) {
    stack<int> B;
    int i = 0, N = A.size();
    while (i < N) {
        int var = 0;
        while (i < N and what(A[i]) == 0) {
            var = 1;
            i++;
        }
        
        if (var) B.push(0);
        else if (what(A[i]) != 3) B.push(what(A[i++]));
        else {
            if (B.empty() or B.top() != 0) return 1; B.pop();
            if (B.empty() or B.top() != 1) return 1; B.pop();
            if (B.empty() or B.top() != 0) return 1; B.pop();
            if (B.empty() or B.top() != 2) return 1; B.pop();
            B.push(0);
            i++;
        }
    }
    return 0;
}
