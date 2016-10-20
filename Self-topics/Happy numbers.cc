/*
A number is called Happy Number if when repeatedly replaced by the sum of squares of its digit, it becomes unity at some point.
e.g: Let n = 19,
	19	-> 82 (1 + 81)
		-> 68 (64 + 4)
		-> 100 (36 + 64)
		-> 1 (1 + 0 + 0)
More can be found out from the book "A Gateway to Modern Mathematics: Vol-1" by Shailesh A. Shirali

We are interested in reporting whether a given number is Happy or not. We want to perform lots of queries in very less time.
To do this we observe that any number keeps on shrinking till it reaches the range [1,162] and then it is stuck in some loop forever.
Let's define one operation as n -> ssq(n)
Consider n <= 10^100,
		ssq(n) <= 100 * 81 = 8100 <= 10000
		ssq(ssq(n)) <= 4 * 81 = 324
		ssq(ssq(ssq(n))) <= 4 + 81 + 81 = 166
		ssq(ssq(ssq(ssq(n)))) <= 81 + 81 = 162.
And now we are trapped in the range [1,162] in just four steps. Observe that step 3 is because 299 <= 324 gives maximum ssq().
Similarly step 4 arises because 99 <= 166 gives maximum ssq().
Hence we conclude that however big a number be, it is bound to get trapped in range [1,162] in very small number of iterations.

So, the key idea of below algorithm is to solve the problem for numbers in the range [1,162]. Using these values, we report for any general n.
*/
#include <iostream>
const int N = 162;

int a[N+1];
inline long long ssq(long long n) {
    long long sumsq = 0;
    while(n > 0) {
        sumsq += (n%10) * (n%10);
        n /= 10;
    }
    return sumsq;
}
inline bool happy(long long n, int repeat) {
    while(n > N) n = ssq(n);
    if(a[n] + 1) return a[n];
    if(repeat > N) return a[n] = 0;
    return a[n] = happy(ssq(n), repeat + 1);
}

int main() {
    for(int i = 1; i <= N; i++) a[i] = -1;
    a[1] = 1;
    
    long long input;
    // Takes input number in the range of [1,1E18] and prints 1 if it is a happy number
    // Stops when a non-positive number is given as input. 
    std::cin >> input;
    while(input > 0) {
        std::cout << happy(input, 0) << '\n';
        std::cin >> input;
    }
    return 0;
}
