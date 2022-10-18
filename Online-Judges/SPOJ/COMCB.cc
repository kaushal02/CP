#include <iostream>
#include <cassert>
#include <vector>
#include <stack>
using namespace std;

class Solution {
    const int dx[8] = {-1, 1, -2, 2, -2, 2, -1, 1};
    const int dy[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int n;
    int m;
    string chessBoardPosition(pair <int, int>& xy) {
        string ans = "";
        ans += (char) ('A' + xy.second);
        ans += to_string(xy.first + 1);
        return ans;
    }
    void dfs(int x, int y, vector <vector <bool> >& visited) {
        visited[x][y] = true;
        for (int d = 0; d < 8; d++) {
            int new_x = x + dx[d];
            int new_y = y + dy[d];
            if (new_x < 0 or new_x >= n or new_y < 0 or new_y >= m or visited[new_x][new_y]) {
                continue;
            }
            dfs(new_x, new_y, visited);
        }
    }
    bool canCover() {
        vector <vector <bool> > visited(n, vector <bool>(m, false));
        dfs(0, 0, visited);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!visited[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
    pair <int, int> dfsWithParent(int x, int y, vector <vector <pair <int, int> > >& parents, int visited) {
        if (visited == n * m) {
            return make_pair(x, y);
        }
        for (int d = 0; d < 8; d++) {
            int new_x = x + dx[d];
            int new_y = y + dy[d];
            if (new_x < 0 or new_x >= n or new_y < 0 or new_y >= m or parents[new_x][new_y] != make_pair(-1, -1)) {
                continue;
            }
            parents[new_x][new_y] = make_pair(x, y);
            pair <int, int> last = dfsWithParent(new_x, new_y, parents, visited + 1);
            if (last != make_pair(-1, -1)) {
                return last;
            }
            parents[new_x][new_y] = make_pair(-1, -1);
        }
        return make_pair(-1, -1);
    }
public:
    Solution(int _n, int _m): n(_n), m(_m) {}
    string getPath() {
        if (n * m == 1) {
            return "A1";
        }
        if (!canCover()) {
            return "-1";
        }

        vector <vector <pair <int, int> > > parents(n, vector <pair <int, int> >(m, pair <int, int>(-1, -1)));
        parents[0][0] = make_pair(0, 0);
        pair <int, int> last = dfsWithParent(0, 0, parents, 1);
        if (last == make_pair(-1, -1)) {
            return "-1";
        }

        stack <pair <int, int> > moves;
        moves.push(last);
        while (last != make_pair(0, 0)) {
            last = parents[last.first][last.second];
            moves.push(last);
        }

        string path = "";
        while (!moves.empty()) {
            path += chessBoardPosition(moves.top());
            moves.pop();
        }
        return path;
    }
    static void unittests() {
        assert(Solution(1,1).getPath() == "A1");
        assert(Solution(1,10).getPath() == "-1");
        assert(Solution(10,1).getPath() == "-1");
        assert(Solution(2,2).getPath() == "-1");
        assert(Solution(3,3).getPath() == "-1");
        assert(Solution(3,4).getPath() == "A1C2A3B1D2B3C1A2C3D1B2D3");
        assert(Solution(4,5).getPath() == "A1B3C1A2B4D3E1C2D4E2C3A4B2D1E3C4A3B1D2E4");
        assert(Solution(4,6).getPath() == "A1B3C1A2B4C2D4E2F4D3E1F3D2B1A3C4B2A4C3E4F2D1E3F1");
    }
};

int main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    Solution::unittests();

    int cases; cin >> cases;
    while (cases--) {
        int n, m; cin >> n >> m;
        cout << Solution(n, m).getPath() << '\n';
    }
    return 0;
}