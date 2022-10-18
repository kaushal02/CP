#include <algorithm>
#include <cassert>
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
    int n;
    vector <int> p10;
    string maskToString(long long mask) {
        string ans = "";
        while (mask) {
            ans += (char) ('0' + (mask & 1));
            mask >>= 1;
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
public:
    Solution(int _n): n(_n) {
        p10.resize(n, 1);
        for (int i = 1; i < n; i++) {
            p10[i] = p10[i - 1] * 10 % n;
        }
    }
    string solve() {
        // if residue_mask[r] = m
        // where m = (b_x .. b_2 b_1 b_0) in base 2
        // then \sum{p10[i] * b_i} == r
        vector <long long> residue_mask(n, 0);
        unordered_set <int> check_residues;
        check_residues.insert(0);

        int next_power = 0; // next_residue = p10[next_power]
        while (!residue_mask[0]) {
            vector <pair <int, long long> > new_residue_mask_pairs;
            for (int r : check_residues) {
                int nr = (r + p10[next_power]) % n;
                if (!residue_mask[nr]) {
                    new_residue_mask_pairs.emplace_back(nr, (residue_mask[r] | (1LL << next_power)));
                }
            }
            for (auto& rm : new_residue_mask_pairs) {
                residue_mask[rm.first] = rm.second;
                check_residues.insert(rm.first);
            }
            next_power++;
        }
        return maskToString(residue_mask[0]);
    }
    static void unittests() {
        assert(Solution(1).solve() == "1");
        assert(Solution(2).solve() == "10");
        assert(Solution(3).solve() == "111");
        assert(Solution(4).solve() == "100");
        assert(Solution(17).solve() == "11101");
        assert(Solution(11011).solve() == "11011");
    }
};

int main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    Solution::unittests();

    int cases; cin >> cases;
    while (cases--) {
        int n; cin >> n;
        cout << Solution(n).solve() << '\n';
    }
    return 0;
}