#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

map<string, vector<string>> remove_left_recursion(
    const map<string, vector<string>>& grammar) {

    map<string, vector<string>> new_grammar;

    for (const auto& rule : grammar) {
        string A = rule.first;
        vector<string> alpha, beta;

        for (const string& prod : rule.second) {
            // Check if production starts with A
            if (prod.substr(0, A.size()) == A) {
                alpha.push_back(prod.substr(A.size()));
            } else {
                beta.push_back(prod);
            }
        }

        if (!alpha.empty()) {
            string A_dash = A + "'";

            // A → βA'
            for (const string& b : beta) {
                new_grammar[A].push_back(b + A_dash);
            }

            // A' → αA' | ε
            for (const string& a : alpha) {
                new_grammar[A_dash].push_back(a + A_dash);
            }
            new_grammar[A_dash].push_back("ε");
        } else {
            new_grammar[A] = rule.second;
        }
    }

    return new_grammar;
}

// Helper to print grammar
void print_grammar(const map<string, vector<string>>& grammar) {
    for (const auto& rule : grammar) {
        cout << rule.first << " -> ";
        for (size_t i = 0; i < rule.second.size(); i++) {
            cout << rule.second[i];
            if (i != rule.second.size() - 1)
                cout << " | ";
        }
        cout << endl;
    }
}

int main() {
    map<string, vector<string>> grammar = {
        {"A", {"Aa", "b"}}
    };

    auto new_grammar = remove_left_recursion(grammar);

    print_grammar(new_grammar);

    return 0;
}
