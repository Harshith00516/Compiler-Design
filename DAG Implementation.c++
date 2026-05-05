#include <iostream>
#include <map>
#include <tuple>
#include <memory>

using namespace std;

// DAG Node
struct DAGNode {
    string op;
    string left;
    string right;

    DAGNode(string o, string l, string r)
        : op(o), left(l), right(r) {}
};

// Key for DAG uniqueness
using Key = tuple<string, string, string>;

// DAG storage
map<Key, shared_ptr<DAGNode>> dag;

// Get or create node
shared_ptr<DAGNode> get_node(const string& op,
                              const string& left,
                              const string& right) {
    Key key = make_tuple(op, left, right);

    if (dag.find(key) == dag.end()) {
        dag[key] = make_shared<DAGNode>(op, left, right);
    }

    return dag[key];
}

int main() {
    auto node = get_node("+", "a", "b");

    cout << "Node created: ("
         << node->left << " "
         << node->op << " "
         << node->right << ")\n";

    return 0;
}
