#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>

using namespace std;

// Compute FIRST
map<string, set<char>> compute_first(const map<string, vector<string>>& grammar) {
    map<string, set<char>> first;

    // Initialize
    for (const auto& rule : grammar) {
        first[rule.first] = {};
    }

    for (const auto& rule : grammar) {
        string nt = rule.first;

        for (const string& prod : rule.second) {
            if (!prod.empty() && islower(prod[0])) {
                first[nt].insert(prod[0]);
            }
        }
    }

    return first;
}

// Compute FOLLOW
map<string, set<char>> compute_follow(const map<string, vector<string>>& grammar,
                                      const string& start) {
    map<string, set<char>> follow;

    // Initialize
    for (const auto& rule : grammar) {
        follow[rule.first] = {};
    }

    follow[start].insert('$');

    for (const auto& rule : grammar) {
        for (const string& prod : rule.second) {
            for (char symbol : prod) {
                if (isupper(symbol)) {
                    follow[string(1, symbol)].insert('$');
                }
            }
        }
    }

    return follow;
}

// Helper to print sets
void print_sets(const map<string, set<char>>& sets, const string& title) {
    cout << title << ":\n";
    for (const auto& entry : sets) {
        cout << entry.first << " = { ";
        for (char c : entry.second) {
            cout << c << " ";
        }
        cout << "}\n";
    }
    cout << endl;
}

int main() {
    map<string, vector<string>> grammar = {
        {"E", {"TR"}},
        {"R", {"+TR", "ε"}}
    };

    auto first = compute_first(grammar);
    auto follow = compute_follow(grammar, "E");

    print_sets(first, "FIRST");
    print_sets(follow, "FOLLOW");

    return 0;
}
