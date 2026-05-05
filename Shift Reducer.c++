#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

class ShiftReduceParser {
private:
    map<string, vector<string>> grammar;
    vector<string> stack;
    vector<char> input;

public:
    ShiftReduceParser(map<string, vector<string>> g, const string& input_string) {
        grammar = g;
        for (char c : input_string) {
            input.push_back(c);
        }
        input.push_back('$'); // end marker
    }

    bool reduce() {
        for (const auto& rule : grammar) {
            string lhs = rule.first;

            for (const string& rhs : rule.second) {
                if (stack.size() >= rhs.size()) {
                    string top = "";
                    for (size_t i = stack.size() - rhs.size(); i < stack.size(); i++) {
                        top += stack[i];
                    }

                    if (top == rhs) {
                        // Remove RHS
                        stack.resize(stack.size() - rhs.size());
                        // Push LHS
                        stack.push_back(lhs);
                        return true;
                    }
                }
            }
        }
        return false;
    }

    bool parse() {
        while (!input.empty()) {
            // Shift
            stack.push_back(string(1, input.front()));
            input.erase(input.begin());

            // Reduce repeatedly
            while (reduce()) {}
        }

        return (stack.size() == 1 && stack[0] == "S");
    }
};

int main() {
    map<string, vector<string>> grammar = {
        {"S", {"aSb", "ab"}}
    };

    string input = "aabb";

    ShiftReduceParser parser(grammar, input);

    if (parser.parse())
        cout << "Accepted\n";
    else
        cout << "Rejected\n";

    return 0;
}
