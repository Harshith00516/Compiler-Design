#include <iostream>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// INFIX → POSTFIX
string infix_to_postfix(const string& expr) {
    stack<char> st;
    string output;

    for (char ch : expr) {
        if (isalnum(ch)) {
            output += ch;
        }
        else if (ch == '(') {
            st.push(ch);
        }
        else if (ch == ')') {
            while (!st.empty() && st.top() != '(') {
                output += st.top();
                st.pop();
            }
            if (!st.empty()) st.pop();
        }
        else { // operator
            while (!st.empty() && precedence(st.top()) >= precedence(ch)) {
                output += st.top();
                st.pop();
            }
            st.push(ch);
        }
    }

    while (!st.empty()) {
        output += st.top();
        st.pop();
    }

    return output;
}

// INFIX → PREFIX
string infix_to_prefix(string expr) {
    reverse(expr.begin(), expr.end());

    for (char& ch : expr) {
        if (ch == '(') ch = ')';
        else if (ch == ')') ch = '(';
    }

    string postfix = infix_to_postfix(expr);
    reverse(postfix.begin(), postfix.end());

    return postfix;
}

int main() {
    string expr = "a+b*c";

    cout << "Postfix: " << infix_to_postfix(expr) << endl;
    cout << "Prefix : " << infix_to_prefix(expr) << endl;

    return 0;
}
