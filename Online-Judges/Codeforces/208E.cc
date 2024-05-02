#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

class Forest {
    const static int L = 20; // number of nodes should be less than 2**L

    int n; // n is the number of nodes
    vector <int> anc[L]; // anc[l][i] represents (2**l)'th parent of node i
    vector <int> depth; // depth[i] represents depth of node i
    vector <vector <int>> tr; // tr[i] has children of node i
    vector <int> id; // id[i] represents masked ID of node i
    vector <int> exit_id; // for each node j in the subtree of node i, id[i] <= id[j] < exit_id[i]
    vector <vector <int>> ids; // ids[d] has id's of all nodes at depth 'd' across all trees

    void dfs(int u, int p, int& next_id, int d) {
        // set depth and ancestors
        anc[0][u] = p;
        for (int l = 1; l < L; l++) {
            anc[l][u] = anc[l - 1][anc[l - 1][u]];
        }
        depth[u] = d;

        // set id and push to ids
        id[u] = next_id++;
        ids[d].push_back(id[u]);

        // recursively call dfs for each child
        for (int ch : tr[u]) {
            dfs(ch, u, next_id, d + 1);
        }

        // set exit_id
        exit_id[u] = next_id;

#ifdef LOCAL
        cout << "\n\n--------------";
        cout << "\nNode " << u;
        cout << "\nAncestors ";
        for (int l = 0; l < L; l++) {
            cout << anc[l][u] << " ";
        }
        cout << "\nDepth " << depth[u];
        cout << "\nChildren ";
        for (int ch : tr[u]) {
            cout << ch << " ";
        }
        cout << "\nID " << id[u];
        cout << "\nExit ID " << exit_id[u];
#endif
    }

  public:
    Forest(int _n, vector <int>& par) {
        n = _n;
        for (int l = 0; l < L; l++) {
            anc[l].resize(n + 1);
        }
        depth.resize(n + 1);
        tr.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            tr[par[i]].push_back(i);
        }
        id.resize(n + 1);
        exit_id.resize(n + 1);
        ids.resize(n + 1);

        int next_id = 0;
        // nodes in tr[0] are the roots.
        for (int r : tr[0]) {
            dfs(r, r, next_id, 0);
        }

#ifdef LOCAL
        for (int d = 0; d <= n; d++) {
            cout << "\nDepth " << d << " node IDs: ";
            for (int u : ids[d]) {
                cout << u << " ";
            }
        }
#endif
    }

    int getKthAncestor(int u, int k) {
        for (int l = 0; l < L; l++) {
            if (k >> l & 1) {
                u = anc[l][u];
            }
        }
        return u;
    }

    int countKthCousins(int u, int k) {
        if (k > depth[u]) {
            return 0;
        }
        int a = getKthAncestor(u, k);
        // count x in ids[depth[u]] where id[a] <= x < exit_id[a]
        return lower_bound(ids[depth[u]].begin(), ids[depth[u]].end(), exit_id[a]) - lower_bound(ids[depth[u]].begin(), ids[depth[u]].end(), id[a]) - 1;
    }

    static void unittests() {
        vector <int> parents({0, 0, 1, 1, 1, 3, 3, 0, 7, 8, 0});
        Forest forest(10, parents);
        for (int i = 1; i <= 10; i++) {
            assert(forest.getKthAncestor(i, 0) == i);
        }
        assert(forest.getKthAncestor(2, 1) == 1);
        assert(forest.getKthAncestor(3, 1) == 1);
        assert(forest.getKthAncestor(4, 1) == 1);
        assert(forest.getKthAncestor(5, 1) == 3);
        assert(forest.getKthAncestor(6, 1) == 3);
        assert(forest.getKthAncestor(5, 2) == 1);
        assert(forest.getKthAncestor(6, 2) == 1);
        assert(forest.getKthAncestor(8, 1) == 7);
        assert(forest.getKthAncestor(9, 1) == 8);
        assert(forest.getKthAncestor(9, 2) == 7);
        assert(forest.getKthAncestor(10, 1) == 10);
        assert(forest.getKthAncestor(10, 2) == 10);
        assert(forest.getKthAncestor(10, 11) == 10);

        assert(forest.countKthCousins(2, 1) == 2);
        assert(forest.countKthCousins(3, 1) == 2);
        assert(forest.countKthCousins(4, 1) == 2);
        assert(forest.countKthCousins(5, 1) == 1);
        assert(forest.countKthCousins(5, 2) == 1);
        assert(forest.countKthCousins(8, 1) == 0);
        assert(forest.countKthCousins(9, 1) == 0);
    }
};

int main() {
#ifdef LOCAL
    Forest::unittests();
#endif

    // input
    int n; cin >> n;
    vector <int> parents(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> parents[i];
    }

    // create DS with input
    Forest forest(n, parents);

    // queries i/o
    int q; cin >> q;
    while (q--) {
        int v, p; cin >> v >> p;
        cout << forest.countKthCousins(v, p) << endl;
    }
    return 0;
}