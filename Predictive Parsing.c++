#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>

using namespace std;

// Predictive Parsing Table
map<pair<string, char>, string> predictive_table(
    const map<string, vector<string>>& grammar,
    const map<string, set<char>>& first) {

    map<pair<string, char>, string> table;

    for (const auto& rule : grammar) {
        string nt = rule.first;

        for (const string& prod : rule.second) {
            for (char symbol : prod) {
                if (first.at(nt).count(symbol)) {
                    table[{nt, symbol}] = prod;
                    break;
                }
            }
        }
    }

    return table;
}

// Helper to print table
void print_table(const map<pair<string, char>, string>& table) {
    cout << "Predictive Parsing Table:\n";
    for (const auto& entry : table) {
        cout << "(" << entry.first.first << ", " << entry.first.second << ") -> "
             << entry.second << endl;
    }
}

int main() {
    map<string, vector<string>> grammar = {
        {"E", {"TR"}},
        {"R", {"+TR", "ε"}}
    };

    map<string, set<char>> first = {
        {"E", {'i'}},
        {"R", {'+'}}
    };

    auto table = predictive_table(grammar, first);

    print_table(table);

    return 0;
}
