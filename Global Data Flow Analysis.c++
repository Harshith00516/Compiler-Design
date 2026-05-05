#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>

using namespace std;

struct Block {
    set<string> gen;
    set<string> kill;
    vector<string> pred;
};

// Reaching Definitions Analysis
pair<map<string, set<string>>, map<string, set<string>>>
reaching_definitions(map<string, Block>& blocks) {

    map<string, set<string>> IN, OUT;

    // Initialize
    for (auto& b : blocks) {
        IN[b.first] = {};
        OUT[b.first] = {};
    }

    bool changed = true;

    while (changed) {
        changed = false;

        for (auto& b : blocks) {
            string name = b.first;
            Block& block = b.second;

            // IN[b] = union of OUT[pred]
            set<string> new_in;

            for (const string& p : block.pred) {
                new_in.insert(OUT[p].begin(), OUT[p].end());
            }

            IN[name] = new_in;

            // OUT[b] = gen ∪ (IN - kill)
            set<string> new_out = block.gen;

            for (const string& d : IN[name]) {
                if (block.kill.find(d) == block.kill.end()) {
                    new_out.insert(d);
                }
            }

            if (new_out != OUT[name]) {
                OUT[name] = new_out;
                changed = true;
            }
        }
    }

    return {IN, OUT};
}

// Helper printer
void print_map(const map<string, set<string>>& m, const string& title) {
    cout << title << ":\n";
    for (const auto& p : m) {
        cout << p.first << " = { ";
        for (const auto& v : p.second) {
            cout << v << " ";
        }
        cout << "}\n";
    }
    cout << endl;
}

int main() {
    map<string, Block> blocks = {
        {"B1", {{"d1"}, {"d2"}, {}}},
        {"B2", {{"d2"}, {"d1"}, {"B1"}}}
    };

    auto result = reaching_definitions(blocks);

    print_map(result.first, "IN");
    print_map(result.second, "OUT");

    return 0;
}
