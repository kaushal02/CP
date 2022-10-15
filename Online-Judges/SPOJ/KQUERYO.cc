#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <class T>
class MergeSortTree {
    struct node {
        node* left;
        node* right;
        vector <T> val;

        node() {}
        node(node* l, node* r, T v): left(l), right(r) {
            setValue(v);
        }
        void setValue(T v) {
            val.push_back(v);
        }
        void update() {
            val.clear();
            val = merge(left, right);
        }
        int countGreater(T k) {
            return val.end() - upper_bound(val.begin(), val.end(), k);
        }
    };

    static vector <T> merge(node* a, node* b) {
        int na = a->val.size(), nb = b->val.size();
        vector <T> merged(na + nb);
        int i = 0, j = 0, k = 0;
        while (i < na and j < nb) {
            if (a->val[i] < b->val[j]) {
                merged[k++] = a->val[i++];
            } else {
                merged[k++] = b->val[j++];
            }
        }
        while (i < na) {
            merged[k++] = a->val[i++];
        }
        while (j < nb) {
            merged[k++] = b->val[j++];
        }
        return merged;
    }

    int n;
    node* root;
    void initHelper(vector <T>& data, node* cur, int lo, int hi) {
        if (lo == hi) {
            cur->setValue(data[lo]);
            return;
        }
        int mi = (lo + hi) / 2;
        cur->left = new node();
        cur->right = new node();
        initHelper(data, cur->left, lo, mi);
        initHelper(data, cur->right, mi + 1, hi);
        cur->update();
    }
    int getHelper(node* cur, int lo, int hi, int l, int r, T k) {
        if (r < lo or hi < l or hi < lo) {
            return 0;
        }
        if (l <= lo and hi <= r) {
            return cur->countGreater(k);
        }
        int mi = (lo + hi) / 2;
        return getHelper(cur->left, lo, mi, l, r, k) + getHelper(cur->right, mi + 1, hi, l, r, k);
    }
public:
    MergeSortTree(vector <T>& data) {
        n = data.size();
        root = new node();
        initHelper(data, root, 0, n - 1);
    }
    int get(int l, int r, T k) {
        return getHelper(root, 0, n - 1, l, r, k);
    }
};

int main() {
    // your code goes here
    int n; cin >> n;
    vector <int> data(n);
    for (int i = 0; i < n; i++) {
        cin >> data[i];
    }

    MergeSortTree <int> merge_sort_tree(data);
    int ans = 0;
    int q; cin >> q;
    while (q--) {
        int a, b, c; cin >> a >> b >> c;
        a ^= ans;
        b ^= ans;
        c ^= ans;
        ans = merge_sort_tree.get(a - 1, b - 1, c);
        cout << ans << '\n';
    }
    return 0;
}