#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>

using namespace std;

// Compute LEADING
map<string, set<char>> compute_leading(const map<string, vector<string>>& grammar) {
    map<string, set<char>> leading;

    for (const auto& rule : grammar) {
        leading[rule.first] = {};
    }

    for (const auto& rule : grammar) {
        string nt = rule.first;

        for (const string& prod : rule.second) {
            if (!prod.empty() && islower(prod[0])) {
                leading[nt].insert(prod[0]);
            }
        }
    }

    return leading;
}

// Compute TRAILING
map<string, set<char>> compute_trailing(const map<string, vector<string>>& grammar) {
    map<string, set<char>> trailing;

    for (const auto& rule : grammar) {
        trailing[rule.first] = {};
    }

    for (const auto& rule : grammar) {
        string nt = rule.first;

        for (const string& prod : rule.second) {
            if (!prod.empty() && islower(prod.back())) {
                trailing[nt].insert(prod.back());
            }
        }
    }

    return trailing;
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
        {"E", {"E+T", "T"}},
        {"T", {"T*F", "F"}},
        {"F", {"(E)", "i"}}
    };

    auto leading = compute_leading(grammar);
    auto trailing = compute_trailing(grammar);

    print_sets(leading, "LEADING");
    print_sets(trailing, "TRAILING");

    return 0;
}
