#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

class Solution {
    int n;
    vector <vector <int> > graph;
    bool isValid(int cur, vector <int>& color) {
        for (int ch : graph[cur]) {
            if (color[ch] == -1) {
                color[ch] = !color[cur];
                if (!isValid(ch, color)) {
                    return false;
                }
            } else if (color[ch] == color[cur]) {
                return false;
            }
        }
        return true;
    }
public:
    Solution(int _n, vector <pair <int, int> > edges): n(_n) {
        graph.resize(n);
        for (auto& edge : edges) {
            graph[edge.first - 1].push_back(edge.second - 1);
            graph[edge.second - 1].push_back(edge.first - 1);
        }
    }
    bool check() {
        vector <int> color(n, -1);
        for (int i = 0; i < n; i++) {
            if (color[i] == -1) {
                color[i] = 0;
                if (!isValid(i, color)) {
                    return false;
                }
            }
        }
        return true;
    }
    string verdict() {
        return (check() ? "No suspicious bugs found!" : "Suspicious bugs found!");
    }
    static void unittests() {
        assert(Solution(1, {}).check());
        assert(Solution(10, {}).check());
        assert(Solution(2, {{1,2}}).check());
        assert(Solution(5, {{1,2}, {2,3}, {3,4}, {4,5}}).check());
        assert(!Solution(3, {{1,2}, {2,3}, {3,1}}).check());
        assert(Solution(4, {{1,2}, {2,3}, {3,4}, {4,1}}).check());
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    Solution::unittests();

    int cases; cin >> cases;
    for (int i = 1; i <= cases; i++) {
        int n, m; cin >> n >> m;
        vector <pair <int, int> > edges(m);
        for (auto& edge : edges) {
            cin >> edge.first >> edge.second;
        }
        cout << "Scenario #" << i << ":\n";
        cout << Solution(n, edges).verdict() << '\n';
    }
    return 0;
}