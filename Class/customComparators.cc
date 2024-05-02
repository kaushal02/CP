#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>

class Node {
  public:
    int v;
    int w;
    Node(): v(0), w(0) {}
    Node(int v_, int w_): v(v_), w(w_) {}
    std::string toString() {
        std::string data = "(";
        data += std::to_string(v);
        data += ", ";
        data += std::to_string(w);
        data += ")";
        return data;
    }
};

class Node3 {
  public:
    int u;
    int v;
    int w;
    Node3(): u(0), v(0), w(0) {}
    Node3(int u_, int v_, int w_): u(u_), v(v_), w(w_) {}
    std::string toString() {
        std::string data = "(";
        data += std::to_string(u);
        data += ", ";
        data += std::to_string(v);
        data += ", ";
        data += std::to_string(w);
        data += ")";
        return data;
    }
};

bool cmp_w_inc(const Node& l, const Node& r) {
    return l.w < r.w;
}
bool cmp_w_dec(const Node& l, const Node& r) {
    return l.w > r.w;
}
struct cmp_v_dec {
    bool operator()(const Node& l, const Node& r) const {
        return l.v > r.v;
    }
    bool operator()(const Node3& l, const Node3& r) const {
        return l.v > r.v;
    }
};

void printArray(std::vector<Node>& v) {
    for (Node& n: v) {
        std::cout << n.toString() << " ";
    }
    std::cout << "\n";
}

int main() {
    std::vector<Node> v;
    v.emplace_back(1, 2);
    v.emplace_back(3, 4);
    v.emplace_back(3, 3);
    sort(v.begin(), v.end(), cmp_w_inc);
    printArray(v);
    sort(v.begin(), v.end(), cmp_w_dec);
    printArray(v);

    std::set<Node, cmp_v_dec> s;
    s.insert(Node(1, 2));
    s.insert(Node(3, 4));
    s.insert(Node(4, 3));
    for (Node n: s) {
        std::cout << n.toString() << " ";
    }
    std::cout << "\n";

    std::set<Node3, cmp_v_dec> s3;
    s3.insert(Node3(0, 1, 2));
    s3.insert(Node3(1, 3, 4));
    s3.insert(Node3(2, 4, 3));
    for (Node3 n3: s3) {
        std::cout << n3.toString() << " ";
    }
    std::cout << "\n";

    std::priority_queue<Node, std::vector<Node>, cmp_v_dec> q;
    q.push(Node(1, 2));
    q.push(Node(3, 4));
    q.push(Node(4, 3));
    while (!q.empty()) {
        Node n = q.top(); q.pop();
        std::cout << n.toString() << " ";
    }
    std::cout << "\n";

    std::priority_queue<Node3, std::vector<Node3>, cmp_v_dec> q3;
    q3.push(Node3(4, 1, 2));
    q3.push(Node3(2, 3, 4));
    q3.push(Node3(3, 4, 3));
    while (!q3.empty()) {
        Node3 n3 = q3.top(); q3.pop();
        std::cout << n3.toString() << " ";
    }
    std::cout << "\n";

    std::map<Node, int, cmp_v_dec> m;
    return 0;
}