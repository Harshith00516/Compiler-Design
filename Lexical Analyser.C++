#include <iostream>
#include <regex>
#include <vector>
#include <string>

using namespace std;

struct Token {
    string type;
    regex pattern;
};

void lexer(const string& code) {
    vector<Token> tokens = {
        {"NUMBER", regex(R"(\d+)")},
        {"ID", regex(R"([a-zA-Z_]\w*)")},
        {"OP", regex(R"([+\-*/=])")},
        {"LPAREN", regex(R"(\()")},
        {"RPAREN", regex(R"(\))")},
        {"SKIP", regex(R"([ \t\n]+)")}
    };

    size_t pos = 0;

    while (pos < code.length()) {
        bool matchFound = false;

        for (const auto& token : tokens) {
            smatch match;
            string remaining = code.substr(pos);

            if (regex_search(remaining, match, token.pattern, regex_constants::match_continuous)) {
                string text = match.str(0);

                if (token.type != "SKIP") {
                    cout << token.type << " : " << text << endl;
                }

                pos += text.length();
                matchFound = true;
                break;
            }
        }

        if (!matchFound) {
            cerr << "SyntaxError: Illegal character: " << code[pos] << endl;
            return;
        }
    }
}

int main() {
    string input = "a = b + 10";
    lexer(input);
    return 0;
}
