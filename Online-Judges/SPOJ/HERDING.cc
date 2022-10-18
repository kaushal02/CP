#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

class Solution {
    int n, m;
    vector <vector <int> > graph;
    int id(int i, int j) {
        return m * i + j;
    }
    int next_id_offset(char direction) {
        switch (direction) {
            case 'N': return -m;
            case 'S': return m;
            case 'E': return 1;
            case 'W': return -1;
        }
        assert(false);
        return 0;
    }
    void componentsHelper(int cur, vector <bool>& visited) {
        for (int ch : graph[cur]) {
            if (!visited[ch]) {
                visited[ch] = true;
                componentsHelper(ch, visited);
            }
        }
    }
public:
    Solution(vector <string> city) {
        n = city.size();
        m = (n ? city[0].size() : 0);
        graph.resize(n * m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int cur_subsection_id = id(i, j);
                int next_subsection_id = cur_subsection_id + next_id_offset(city[i][j]);
                graph[cur_subsection_id].push_back(next_subsection_id);
                graph[next_subsection_id].push_back(cur_subsection_id);
            }
        }
    }
    int components() {
        int ans(0);
        vector <bool> visited(n * m, false);
        for (int i = 0; i < n * m; i++) {
            if (!visited[i]) {
                ans++;
                visited[i] = true;
                componentsHelper(i, visited);
            }
        }
        return ans;
    }
    static void unittests() {
        assert(Solution({}).components() == 0);
        assert(Solution({""}).components() == 0);
        assert(Solution({"EW"}).components() == 1);
        assert(Solution({"EEEEEWWWWW"}).components() == 1);
        assert(Solution({"EWEW"}).components() == 2);
        assert(Solution({"EEWEWWWEW"}).components() == 3);
        assert(Solution({"SWWW", "SEWN", "EEEN"}).components() == 2);
    }
};

int main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    Solution::unittests();

    int n, m; cin >> n >> m;
    vector <string> city(n);
    for (string& subsection : city) {
        cin >> subsection;
    }
    cout << Solution(city).components() << '\n';
    return 0;
}