#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

class Solution {
    int n;
    vector <vector <int> > tree;
    void dfs(int cur, vector <bool>& visited) {
        visited[cur] = true;
        for (int ch : tree[cur]) {
            if (!visited[ch]) {
                dfs(ch, visited);
            }
        }
    }
public:
    Solution(int _n, vector <pair <int, int> > edges): n(_n) {
        tree.resize(n);
        for (auto& edge : edges) {
            tree[edge.first].push_back(edge.second);
            tree[edge.second].push_back(edge.first);
        }
    }
    int components() {
        int ans(0);
        vector <bool> visited(n, false);
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(i, visited);
                ans++;
            }
        }
        return ans;
    }
    static void unittests() {
        assert(Solution(10, {}).components() == 10);
        assert(Solution(10, {{0,1}}).components() == 9);
        assert(Solution(10, {{0,1}, {2,3}}).components() == 8);
        assert(Solution(10, {{0,1}, {1,2}}).components() == 8);
        assert(Solution(10, {{0,1}, {1,2}, {2,0}}).components() == 8);
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    Solution::unittests();

    int cases; cin >> cases;
    while (cases--) {
        int n, m; cin >> n >> m;
        vector <pair <int, int> > edges(m);
        for (auto& edge : edges) {
            cin >> edge.first >> edge.second;
        }
        cout << Solution(n, edges).components() << '\n';
    }
    return 0;
}