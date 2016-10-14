/*
_floyd_warshall _graph
snake & ladder simulation which determines the minimum steps to complete the game

O(N^3)
*/
#include <iostream>
#include <cassert>
using namespace std;
const int inf = 0xf7f7f7f, N = 100;

int t[N+1][N+1];
int main() {
    for(int i = 1; i <= N; i++)
        for(int j = 1; j <= N; j++)
            t[i][j] = inf; // Impossible without dice roll
    
    int k; cin >> k;
    for(int j = 1; j <= k; j++)
        for(int i = 1; i <= N - j; i++)
            t[i][i+j] = 1; // Dice rolls allowed
    
    int m, n, x, y;
    cin >> m >> n;
    for(int i = 1; i <= m; i++) {
        cin >> x >> y;
        assert(x < y); // Ladders
        t[x][y] = 1;
    }
    for(int i = 1; i <= n; i++) {
        cin >> x >> y;
        assert(x > y); // Snakes
        t[x][y] = 1;
    }
    
    for(int k = 1; k <= N; k++)
        for(int i = 1; i <= N; i++)
            for(int j = 1; j <= N; j++)
                t[i][j] = min(t[i][j], t[i][k] + t[k][j]);
    
    cout << t[1][100];
}
