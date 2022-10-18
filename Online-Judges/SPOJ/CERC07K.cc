#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
using namespace std;

class Solution {
    const int COLORS = 4;
    const int dx[4] = {1, 0, -1, 0};
    const int dy[4] = {0, 1, 0, -1};
    int n, m;
    vector <string> val;
    bool isSymbolBegin(int i, int j) {
        return val[i][j] == '*';
    }
    bool isSymbolEnd(int i, int j) {
        return val[i][j] == 'X';
    }
    bool isSymbolWall(int i, int j) {
        return val[i][j] == '#';
    }
    int getSymbolDoors(int i, int j) {
        return (val[i][j] == 'R')
                + ((val[i][j] == 'Y') << 1)
                + ((val[i][j] == 'G') << 2)
                + ((val[i][j] == 'B') << 3);
    }
    int getSymbolKeys(int i, int j) {
        return (val[i][j] == 'r') + 2 * (val[i][j] == 'y') + 4 * (val[i][j] == 'g') + 8 * (val[i][j] == 'b');
    }
    struct node {
        int x, y;
        int mask;
        int steps;
        node() {}
        node(int _x, int _y, int _mask, int _steps): x(_x), y(_y), mask(_mask), steps(_steps) {}
    };
public:
    Solution(vector <string> grid) {
        n = grid.size();
        m = (n ? grid[0].size() : 0);
        val = grid;
    }
    int solve() {
        int bi, bj;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (isSymbolBegin(i, j)) {
                    bi = i;
                    bj = j;
                }
            }
        }
        vector <vector <vector <int> > > steps(n, vector <vector <int> >(m, vector <int>((1 << COLORS), -1)));
        queue <node> q;
        q.push(node(bi, bj, 0, 0));
        steps[bi][bj][0] = 0;
        while (!q.empty()) {
            node cur = q.front();
            q.pop();
            if (isSymbolEnd(cur.x, cur.y)) {
                return cur.steps;
            }
            for (int d = 0; d < 4; d++) {
                int x = cur.x + dx[d];
                int y = cur.y + dy[d];
                if (x < 0 or x >= n or y < 0 or y >= m or isSymbolWall(x, y)) {
                    continue;
                }
                int mask = getSymbolDoors(x, y);
                if ((cur.mask & mask) != mask) {
                    continue;
                }
                mask = (cur.mask | getSymbolKeys(x, y));
                if (steps[x][y][mask] == -1) {
                    q.push(node(x, y, mask, cur.steps + 1));
                    steps[x][y][mask] = cur.steps + 1;
                }
            }
        }
        return -1;
    }
    string verdict() {
        int ans = solve();
        if (ans == -1) {
            return "The poor student is trapped!";
        }
        return "Escape possible in " + to_string(ans) + " steps.";
    }
    static void unittests() {
        assert(Solution({"*"}).solve() == -1);
        assert(Solution({"*X"}).solve() == 1);
        assert(Solution({"*#X"}).solve() == -1);
        assert(Solution({"*.........X"}).solve() == 10);
        assert(Solution({"...X.*....X"}).solve() == 2);
        assert(Solution({"...X#*....X"}).solve() == 5);
        assert(Solution({"...XR*....X"}).solve() == 5);
    }
};

int main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    Solution::unittests();

    int n, m; cin >> n >> m;
    while (n or m) {
        vector <string> grid(n);
        for (string& row : grid) {
            cin >> row;
        }
        cout << Solution(grid).verdict() << '\n';
        cin >> n >> m;
    }
    return 0;
}
