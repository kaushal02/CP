#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

class Solution {
    struct node {
        int value;
        node* left;
        node* right;
        vector <int> sorted;
        node(): left(NULL), right(NULL) {}
        node(node* l, node* r, int v): left(l), right(r) {
            set(v);
        }
        void set(int v) {
            value = v;
            sorted.clear();
            sorted.push_back(v);
        }
        void update(int v) {
            value = v;
            sorted.clear();
            sorted = merge(left, right, value);
        }
        int countInRange(int l, int r) {
            // number of elements with value in [l,r]
            return upper_bound(sorted.begin(), sorted.end(), r) - lower_bound(sorted.begin(), sorted.end(), l);
        }
    };

    static vector <int> merge(node* a, node* b, int v) {
        int na = a->sorted.size();
        int nb = b->sorted.size();
        vector <int> sorted(na + nb);
        int i = 0, j = 0, k = 0;
        while (i < na and j < nb) {
            if (a->sorted[i] < b->sorted[j]) {
                sorted[k++] = a->sorted[i++];
            } else {
                sorted[k++] = b->sorted[j++];
            }
        }
        while (i < na) {
            sorted[k++] = a->sorted[i++];
        }
        while (j < nb) {
            sorted[k++] = b->sorted[j++];
        }
        sorted.insert(lower_bound(sorted.begin(), sorted.end(), v), v);
        return sorted;
    }

    void unittests() {
        node* n = new node();
        assert(n->countInRange(1, 1) == 0);

        n->sorted = {1, 2, 4, 50, 51, 60};
        assert(n->countInRange(0, 100) == 6);
        assert(n->countInRange(1, 60) == 6);
        assert(n->countInRange(1, 1) == 1);
        assert(n->countInRange(60, 60) == 1);
        assert(n->countInRange(5, 5) == 0);
        assert(n->countInRange(50, 50) == 1);
        assert(n->countInRange(50, 51) == 2);
        assert(n->countInRange(50, 60) == 3);
        assert(n->countInRange(51, 60) == 2);
        assert(n->countInRange(61, 62) == 0);
        assert(n->countInRange(6, 66) == 3);

        node* n2 = new node();
        n2->sorted = {3, 55};
        vector <int> merged = merge(n, n2, 10);
        vector <int> expected = {1, 2, 3, 4, 10, 50, 51, 55, 60};
        assert(merged == expected);
    }

    int n;
    node* root;
    void initHelper(node* cur, vector <int>& values, int l, int r) {
        if (l > r) {
            return;
        }
        if (l == r) {
            cur->set(values[l]);
            return;
        }
        int m = (l + r) / 2;
        cur->left = new node();
        cur->right = new node();
        initHelper(cur->left, values, l, m - 1);
        initHelper(cur->right, values, m + 1, r);
        cur->update(values[m]);
    }

    int getKthElement(node* cur, int l, int r, int k) {
        int count_left = 0;
        if (cur->left) {
            count_left = cur->left->countInRange(l, r);
        }
        if (count_left >= k) {
            return getKthElement(cur->left, l, r, k);
        }
        int count_this = (l <= cur->value and cur->value <= r);
        if (count_left == k - 1 and count_this == 1) {
            return cur->value;
        }
        return getKthElement(cur->right, l, r, k - count_left - count_this);
    }

    long long solveHelper(int lo, int hi) {
        if (lo >= hi) {
            return 0;
        }
        int cur = getKthElement(root, lo, hi, 1 + (hi - lo) / 2);
        return (hi - lo + 1) + solveHelper(lo, cur - 1) + solveHelper(cur + 1, hi);
    }

public:
    Solution(vector <int>& perm) {
        unittests();
        n = perm.size();
        root = new node();
        initHelper(root, perm, 0, n - 1);
    }
    long long solve() {
        return solveHelper(1, n);
    }
};

int main() {
    // your code goes here
    int n; cin >> n;
    vector <int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    Solution solution(a);
    cout << solution.solve();
    return 0;
}