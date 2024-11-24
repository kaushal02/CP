#include <iostream>
#include <algorithm>
#include <random>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <string>
#include <memory>
#include <functional>
using namespace std;

// Simplified Node struct
struct Node {
    int l;
    int r;
    int value;
    Node(int left, int right, int value) : l(left), r(right), value(value) {}
    void print() const {
        std::cout << "Node(" << l << ", " << r << ", " << value << ")\n";
    }
};

int main() {
    int bucket = 1;  // Non-const bucket size

    auto myComparator = [&bucket](const Node& lhs, const Node& rhs) {
        if (lhs.r / bucket == rhs.r / bucket) {
            return lhs.l < rhs.l;
        }
        return lhs.r / bucket < rhs.r / bucket;
    };

    auto myRightComparator = [&bucket](const int& lhs, const int& rhs) {
        return lhs / bucket < rhs / bucket;
    };

    // Create set with custom comparator
    set<Node, decltype(myComparator)> nodeSet(myComparator);
    map<int, Node, decltype(myRightComparator)> nodeMap(myRightComparator);
    priority_queue<Node, vector<Node>, decltype(myComparator)> nodePQ(myComparator);

    // Create some Node objects
    vector<Node> nodes;
    nodes.emplace_back(1, 5, 10);
    nodes.emplace_back(7, 9, 11);
    nodes.emplace_back(8, 11, 12);
    nodes.emplace_back(2, 4, 13);
    nodes.emplace_back(6, 9, 14);
    nodes.emplace_back(10, 30, 15);

    // Populate containers
    for (const auto& node : nodes) {
        nodeSet.insert(node);
        nodeMap.emplace(node.r, node);
        nodePQ.push(node);
    }

    // Print set contents
    std::cout << "Set contents:" << std::endl;
    for (auto& node : nodeSet) {
        node.print();
    }
    std::cout << std::endl;

    // Print map contents
    std::cout << "Map contents:" << std::endl;
    for (auto& pair : nodeMap) {
        std::cout << pair.first << " -> ";
        pair.second.print();
    }
    std::cout << std::endl;

    // Print priority queue contents
    std::cout << "Priority Queue contents:" << std::endl;
    while (!nodePQ.empty()) {
        nodePQ.top().print();
        nodePQ.pop();
    }
    std::cout << std::endl;

    // Sort the vector using the custom comparator
    std::shuffle(nodes.begin(), nodes.end(), mt19937(random_device()()));

    // Print sorted vector contents
    std::cout << "Sorted vector contents:" << std::endl;
    for (const auto& node : nodes) {
        node.print();
    }
    std::cout << std::endl;

    auto myValueComparator = [&bucket](const int& value, const Node& n) {
        return value < n.r;
    };

    // Use upper bound in nodeSet with customComparator
    for (int x : {1, 5, 9, 10, 20, 30}) {
        auto it = upper_bound(nodeSet.begin(), nodeSet.end(), x, myValueComparator);
        cout << "Upper bound of " << x << ": ";
        if (it != nodeSet.end()) {
            it->print();
        } else {
            cout << "not found\n";
        }
    }
    std::cout << std::endl;

    return 0;
}
