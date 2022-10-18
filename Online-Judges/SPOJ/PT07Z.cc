#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

class Solution {
    static pair <int, int> dfs(int u, int p, vector <vector <int> >& tree) {
        int ans(-1), maxDepth(-1), maxDepth2(-1);
        for (int ch : tree[u]) {
            if (ch == p) {
                continue;
            }
            pair <int, int> ret = dfs(ch, u, tree);
            ans = max(ans, ret.first);
            if (ret.second >= maxDepth) {
                maxDepth2 = maxDepth;
                maxDepth = ret.second;
            } else if (ret.second >= maxDepth2) {
                maxDepth2 = ret.second;
            }
        }
        if (maxDepth2 != -1) {
            ans = max(ans, maxDepth + maxDepth2 + 2);
        } else if (maxDepth != -1) {
            ans = max(ans, maxDepth + 1);
        } else {
            ans = 0;
        }
        return make_pair(ans, maxDepth + 1);
    }
public:
    static int longestPathLength(vector <vector <int> > tree) {
        int n = tree.size();
        return (n ? dfs(0, 0, tree).first : 0);
    }
    static void unittests() {
        assert(Solution::longestPathLength({}) == 0);
        assert(Solution::longestPathLength({{}}) == 0);
        assert(Solution::longestPathLength({{1}, {0}}) == 1);
        assert(Solution::longestPathLength({{1,2}, {0}, {0}}) == 2);
        assert(Solution::longestPathLength({{1,2,3,4}, {0}, {0}, {0}, {0}}) == 2);
        assert(Solution::longestPathLength({{1,2,3,4}, {0}, {0,5}, {0}, {0}, {2}}) == 3);
        assert(Solution::longestPathLength({{1,2,3,4}, {0}, {0,5}, {0}, {0}, {2,6}, {5}}) == 4);
        assert(Solution::longestPathLength({{1,2,3,4}, {0}, {0,5,7}, {0}, {0}, {2,6}, {5,10}, {2,8}, {7,9}, {8}, {6}}) == 6);
    }
};

int main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    Solution::unittests();

    int n; cin >> n;
    vector <vector <int> > tree(n);
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        tree[u - 1].push_back(v - 1);
        tree[v - 1].push_back(u - 1);
    }
    cout << Solution::longestPathLength(tree) << '\n';
    return 0;
}