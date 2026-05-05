#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>

using namespace std;

using Item = pair<string, string>; // (LHS, RHS with dot)

// Closure function
set<Item> closure(set<Item> items, const map<string, vector<string>>& grammar) {
    set<Item> closure_set = items;
    bool added = true;

    while (added) {
        added = false;

        // Copy to avoid modifying while iterating
        vector<Item> current_items(closure_set.begin(), closure_set.end());

        for (const Item& item : current_items) {
            string lhs = item.first;
            string rhs = item.second;

            size_t dot_pos = rhs.find('.');

            if (dot_pos != string::npos && dot_pos < rhs.size() - 1) {
                char symbol = rhs[dot_pos + 1];

                string sym_str(1, symbol);

                // If symbol is a non-terminal
                if (grammar.find(sym_str) != grammar.end()) {
                    for (const string& prod : grammar.at(sym_str)) {
                        Item new_item = {sym_str, "." + prod};

                        if (closure_set.find(new_item) == closure_set.end()) {
                            closure_set.insert(new_item);
                            added = true;
                        }
                    }
                }
            }
        }
    }

    return closure_set;
}

// Helper to print items
void print_items(const set<Item>& items) {
    cout << "Closure:\n";
    for (const auto& item : items) {
        cout << item.first << " -> " << item.second << endl;
    }
}

int main() {
    map<string, vector<string>> grammar = {
        {"S", {"CC"}},
        {"C", {"cC", "d"}}
    };

    set<Item> items = {
        {"S", ".CC"}
    };

    auto result = closure(items, grammar);

    print_items(result);

    return 0;
}
