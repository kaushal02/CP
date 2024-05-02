/*
https://www.interviewbit.com/problems/valid-number/

Linear Solution
*/

/* Skips the number starting at index i in given string
 * Returns 1 if a number was found
 */
bool num(const string A, int &i) {
    int j = i, N = A.size();
    while (j < N and isdigit(A[j])) j++;
    int Ans = j > i;
    return i = j, Ans;
}

/* VALID string is identified as " PA.BeQC "
 * P and Q are signs + or -
 * A B C are numbers
 * 
 * Following observations act as constraints:
 * e -> C
 * . -> B
 * A or . must exist
 */
int Solution::isNumber(const string A) {
    int N = A.size(), i = 0;
    
    // stand for A . B e C respectively
    int f1 = 0, f2 = 0, f3 = 0, f4 = 0, f5 = 0;
    
    while (i < N and iswspace(A[i])) i++; // Eat whitespaces
    if (i < N and A[i] == '+' or A[i] == '-') i++; // P
    if (num(A, i)) f1++; // A
    if (i < N and A[i] == '.') i++, f2++; // .
    if (num(A, i)) f3++; // B
    if (i < N and A[i] == 'e') i++, f4++; // e
    if (A[i] == '+' or A[i] == '-') i++; // Q
    if (num(A, i)) f5++; // C
    while (i < N and iswspace(A[i])) i++; // Eat whitespaces
    
    // Check all constraints as mentioned above
    return (i == N) and (not f4 or f5) and (not f2 or f3) and (f1 or f2);
}
