#include <iostream>
using namespace std;

class Node {
public:
    int id;
    Node* left;
    Node* right;
    Node(int id_, Node* left_, Node* right_)
        : id(id_), left(left_), right(right_) {}

    int size() {
        if (left == NULL and right == NULL) return 1;
        if (left == NULL) return 1 + right->size();
        if (right == NULL) return 1 + left->size();
        return 1 + left->size() + right->size();
    }

    void addToAll(int val) {
        id += val;
        if (left != NULL) left->addToAll(val);
        if (right != NULL) right->addToAll(val);
    }

    string parse(int bracketId=0) {
        string ret = to_string(id);
        if (left != NULL) {
            ret += "\n";
            for (int i = 0; i <= bracketId; i++) {
                ret += "\t";
            }
            ret += left->parse(bracketId + 1);
            ret += "\n";
            for (int i = 0; i < bracketId; i++) {
                ret += "\t";
            }
        } else {
            ret += " ";
        }
        if (right != NULL) {
            ret += right->parse(bracketId);
        }
        return ret;
    }
};

Node* solve(int attempts, int breakLimit) {
    // solve(9,1) : [1 2 3 ... 9]
    // solve(10,2) : val=1+solve(9,1).size() : val [solve(9,1)] val+solve(9,2)

    if (attempts < 1 or breakLimit < 1) {
        return NULL;
    }
    if (attempts == 1) {
        Node* ret = new Node(1, NULL, NULL);
        return ret;
    }
    
    Node* left = solve(attempts - 1, breakLimit - 1);
    Node* right = solve(attempts - 1, breakLimit);

    int value = 1 + (left != NULL ? left->size() : 0);
    right->addToAll(value);

    Node* ret = new Node(value, left, right);
    return ret;
}

signed main() {
    // your code goes here
    while(true) {
        int n, k;
        cout << "Enter the number of attempts and eggs separated by space:\n";
        cin >> n >> k;
        cout << solve(n, k)->parse() << "\n\n";
    }
    return 0;
}
