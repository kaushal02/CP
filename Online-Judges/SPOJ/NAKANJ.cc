#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
using namespace std;

class ChessBoardKnights {
    const int dx[8] = {-1, 1, -2, 2, -2, 2, -1, 1};
    const int dy[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
    struct node {
        int x, y, steps;
        node(int _x, int _y, int _steps): x(_x), y(_y), steps(_steps) {}
        bool invalid(int n) {
            return x < 0 or x >= n or y < 0 or y >= n;
        }
    };
    int n;
    vector <vector <int> > ans;
    int getId(int i, int j) {
        return i * n + j;
    }
    int getIdFromName(string name) {
        return getId(name[1] - '1', name[0] - 'a');
    }
    void bfs(int x, int y, vector <int>& visited) {
        queue <node> q;
        visited[getId(x, y)] = 0;
        q.push(node(x, y, 0));
        while (!q.empty()) {
            node cur = q.front();
            q.pop();
            for (int d = 0; d < 8; d++) {
                node next(cur.x + dx[d], cur.y + dy[d], cur.steps + 1);
                if (next.invalid(n)) {
                    continue;
                }
                int id = getId(next.x, next.y);
                if (visited[id] == -1) {
                    visited[id] = next.steps;
                    q.push(next);
                }
            }
        }
    }
    void initHelper(int x, int y) {
        int id = getId(x, y);
        ans[id][id] = 0;
        bfs(x, y, ans[id]);
    }
public:
    ChessBoardKnights(int _n): n(_n) {
        ans.resize(n * n, vector <int>(n * n, -1));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                initHelper(i, j);
            }
        }
    }
    int minimumMoves(string pos1, string pos2) {
        return ans[getIdFromName(pos1)][getIdFromName(pos2)];
    }
    static void unittests() {
        assert(ChessBoardKnights(8).minimumMoves("a1", "a1") == 0);
        assert(ChessBoardKnights(8).minimumMoves("a1", "c2") == 1);
        assert(ChessBoardKnights(8).minimumMoves("a1", "b3") == 1);
        assert(ChessBoardKnights(8).minimumMoves("a1", "a3") == 2);
        assert(ChessBoardKnights(8).minimumMoves("a1", "a5") == 2);
        assert(ChessBoardKnights(8).minimumMoves("a1", "c3") == 4);
    }
};

int main() {
    ChessBoardKnights::unittests();

    ChessBoardKnights board(8);
    int cases; cin >> cases;
    while (cases--) {
        string pos1, pos2;
        cin >> pos1 >> pos2;
        cout << board.minimumMoves(pos1, pos2) << '\n';
    }
    return 0;
}