#include <iostream>
using namespace std;
const double E4 = 1E4;

// (12, 8) -> (8, 4) -> (4, 0) -> 4
inline int getGCD(int a, int b) {
    return (b ? getGCD(b, a % b) : a);
}

int main() {
    // your code goes here
    int run_count = 0;
    cin >> run_count;
    while (run_count--) {
        double average_score = 0;
        cin >> average_score;
        double fractional_part = average_score - (int)(average_score);
        double fractional_part_e4 = fractional_part * E4;
        int fractional_part_e4_rounded_off = fractional_part_e4;
        if (fractional_part_e4 - fractional_part_e4_rounded_off > 0.5) {
            fractional_part_e4_rounded_off++;
        }
        int gcd = getGCD(fractional_part_e4_rounded_off, 10000);
        cout << (10000 / gcd) << '\n';
    }
    return 0;
}
