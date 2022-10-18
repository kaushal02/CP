#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

class Solution {
    int n;
    vector <vector <pair <int, bool> > > graph;
    int merge(int a, int b) {
        return a == b;
    }
    bool isParadoxHelper(int cur, vector <int>& visited) {
        for (auto& ch : graph[cur]) {
            if (visited[ch.first] == -1) {
                visited[ch.first] = merge(visited[cur], ch.second);
                if (isParadoxHelper(ch.first, visited)) {
                    return true;
                }
            } else if (visited[ch.first] != merge(visited[cur], ch.second)) {
                return true;
            }
        }
        return false;
    }
public:
    Solution(vector <pair <int, bool> > statements) {
        n = statements.size();
        graph.resize(n);
        for (int i = 0; i < n; i++) {
            int j = statements[i].first - 1;
            graph[i].emplace_back(j, statements[i].second);
            graph[j].emplace_back(i, statements[i].second);
        }
    }
    bool isParadox() {
        vector <int> visited(n, -1);
        for (int i = 0; i < n; i++) {
            if (visited[i] == -1) {
                visited[i] = 0;
                if (isParadoxHelper(i, visited)) {
                    return true;
                }
            }
        }
        return false;
    }
    static void unittests() {
        assert(!Solution({}).isParadox());
        assert(!Solution({{1,true}}).isParadox());
        assert(Solution({{1,false}}).isParadox());
        assert(!Solution({{2,true}, {1,true}}).isParadox());
        assert(Solution({{2,true}, {1,false}}).isParadox());
        assert(!Solution({{2,false}, {1,false}}).isParadox());
    }
};

int main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    Solution::unittests();

    int n; cin >> n;
    while (n) {
        vector <pair <int, bool> > statements(n);
        for (auto& s : statements) {
            string truth;
            cin >> s.first >> truth;
            s.second = (truth == "true");
        }
        cout << (Solution(statements).isParadox() ? "PARADOX" : "NOT PARADOX") << '\n';
        cin >> n;
    }
    return 0;
}