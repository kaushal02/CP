#include <vector>

class Tree {
    const static int L = 20; // number of nodes should be less than 2**L

    int indexing; // 0 if 0-based indexing, otherwise 1
    int n; // n is the number of nodes
    vector <int> anc[L]; // anc[l][i] represents (2**l)'th parent of node i
    vector <int> depth; // depth[i] represents depth of node i
    vector <vector <int>> tr; // tr[i] has children of node i

    void dfs(int u, int p, int d) {
        // set depth and ancestors
        depth[u] = d;
        anc[0][u] = p;
        for (int l = 1; l < L; l++) {
            anc[l][u] = anc[l - 1][anc[l - 1][u]];
        }

        // recursively call dfs for each child
        for (int ch : tr[u]) {
            if (ch != p) {
                dfs(ch, u, d + 1);
            }
        }
    }

  public:
    Tree(int _n, int _indexing, vector <pair<int, int>>& edges, bool directed) {
        indexing = _indexing;
        n = _n + _indexing;
        for (int l = 0; l < L; l++) {
            anc[l].resize(n);
        }
        depth.resize(n);
        tr.resize(n);
        for (auto& edge : edges) {
            tr[edge.first].push_back(edge.second);
            if (!directed) {
                tr[edge.second].push_back(edge.first);
            }
        }
        // root at 'indexing'
        dfs(indexing, indexing, 0);
    }

    int getKthAncestor(int u, int k) {
        for (int l = 0; l < L; l++) {
            if (k >> l & 1) {
                u = anc[l][u];
            }
        }
        return u;
    }

    int getLCA(int u, int v) {
        if (depth[u] < depth[v]) {
            swap(u, v);
        }
        u = getKthAncestor(u, depth[u] - depth[v]);
        for (int l = L; l--; ) {
            if (anc[l][u] != anc[l][v]) {
                u = anc[l][u];
                v = anc[l][v];
            }
        }
        return (u == v ? u : anc[0][u]);
    }

    static void unittests() {
        vector <pair<int, int>> edges;
        edges.push_back(make_pair(1, 2));
        edges.push_back(make_pair(1, 3));
        edges.push_back(make_pair(1, 4));
        edges.push_back(make_pair(2, 5));
        edges.push_back(make_pair(2, 6));
        edges.push_back(make_pair(3, 7));
        edges.push_back(make_pair(3, 8));
        edges.push_back(make_pair(7, 9));
        Tree tree(9, 1, edges, false);

        for (int i = 1; i <= 9; i++) {
            assert(tree.getKthAncestor(i, 0) == i);
        }
        assert(tree.getKthAncestor(2, 1) == 1);
        assert(tree.getKthAncestor(3, 1) == 1);
        assert(tree.getKthAncestor(4, 1) == 1);
        assert(tree.getKthAncestor(5, 1) == 2);
        assert(tree.getKthAncestor(5, 2) == 1);
        assert(tree.getKthAncestor(6, 1) == 2);
        assert(tree.getKthAncestor(6, 2) == 1);
        assert(tree.getKthAncestor(7, 1) == 3);
        assert(tree.getKthAncestor(7, 2) == 1);
        assert(tree.getKthAncestor(8, 1) == 3);
        assert(tree.getKthAncestor(8, 2) == 1);
        assert(tree.getKthAncestor(9, 1) == 7);
        assert(tree.getKthAncestor(9, 2) == 3);
        assert(tree.getKthAncestor(9, 3) == 1);

        for (int i = 1; i <= 9; i++) {
            assert(tree.getLCA(2, i) == (i == 2 or i == 5 or i == 6 ? 2 : 1));
            assert(tree.getLCA(3, i) == (i == 3 or i == 7 or i == 8 or i == 9 ? 3 : 1));
            assert(tree.getLCA(4, i) == (i == 4 ? 4 : 1));
        }
        assert(tree.getLCA(5, 6) == 2);
        assert(tree.getLCA(8, 9) == 3);
        assert(tree.getLCA(9, 6) == 1);
    }
};
