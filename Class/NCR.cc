#include <vector>

/*
 * NCR(N).choose(n, r) returns choose(n, r) for n, r < N
 * Time : O(1) amortized, O(N^2) total
 * Space: O(N^2)
 */
template <class T>
class NCR {
    int N;
    vector <vector <T> > value;
public:
    NCR(int n): N(n) {
        value.resize(n, vector <T> (n));
    }
    T choose(int n, int r) {
        if (n < 0 or r < 0 or n < r) {
            return 0;
        }
        if (r == 0) {
            return 1;
        }
        if (value[n][r]) {
            return value[n][r];
        }
        return value[n][r] = choose(n - 1, r - 1) + choose(n - 1, r);
    }
    static void unittests() {
        NCR <int> ncr(100);
        assert(ncr.choose(0, 0) == 1);
        assert(ncr.choose(1, 0) == 1);
        assert(ncr.choose(10, 0) == 1);
        assert(ncr.choose(1, 1) == 1);
        assert(ncr.choose(10, 1) == 10);
        assert(ncr.choose(10, 10) == 1);
        assert(ncr.choose(6, 3) == 20);
    }
};
