/*
https://www.interviewbit.com/problems/sorted-permutation-rank-with-repeats/

Linear Solution
*/

const long long MOD = 1E6 + 3;

long long pwr(long long A, long long N) {
    // Binary Exponentiation
    if (N == 0) return 1;
    long long X = pwr(A, N >> 1);
    X = X * X % MOD;
    return (N % 2 ? X * A % MOD : X);
}

int Solution::findRank(string A) {
    int N = A.size(), C[256] = {};
    long long NUM = 1, DEN = 1, ANS = 1;
    
    // F[i]: i! % MOD
    vector<long long> F(N + 1);
    F[0] = 1;
    for (int i = 1; i <= N; i++) {
        F[i] = F[i - 1] * i % MOD;
    }
    
    // I[i]: i^-1 % MOD
    vector<long long> I(N + 1);
    I[N] = pwr(F[N], MOD - 2);
    for (int i = N; i--; ) {
        I[i] = I[i + 1] * (i + 1) % MOD;
    }
    for (int i = 1; i <= N; i++) {
        I[i] = I[i] * F[i - 1] % MOD;
    }
    
    // Cumulate in reverse order since it doesn't matter
    for (int i = N; i--; ) {
        DEN = DEN * I[++C[A[i]]] % MOD;
        for (int j = 'A'; j < A[i]; j++) {
            ANS += NUM * DEN % MOD * C[j] % MOD;
        }
        NUM = NUM * (N - i) % MOD;
        ANS %= MOD;
    }
    return ANS;
}