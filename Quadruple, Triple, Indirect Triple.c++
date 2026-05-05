#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

struct Quadruple {
    string op;
    string arg1;
    string arg2;
    string result;
};

// Generate quadruples
vector<Quadruple> generate_quadruples(const string& expr) {
    vector<string> st;
    vector<Quadruple> quads;
    int temp_count = 1;

    for (char ch : expr) {
        if (isalnum(ch)) {
            st.push_back(string(1, ch));
        } else {
            if (st.size() < 2) continue; // safety check

            string op2 = st.back(); st.pop_back();
            string op1 = st.back(); st.pop_back();

            string temp = "t" + to_string(temp_count++);

            quads.push_back({string(1, ch), op1, op2, temp});

            st.push_back(temp);
        }
    }

    return quads;
}

// Print quadruples
void print_quads(const vector<Quadruple>& quads) {
    cout << "Operator | Arg1 | Arg2 | Result\n";
    cout << "---------------------------------\n";

    for (const auto& q : quads) {
        cout << "   " << q.op
             << "     |  " << q.arg1
             << "   |  " << q.arg2
             << "   |  " << q.result << endl;
    }
}

int main() {
    string expr = "ab+c*";

    auto quads = generate_quadruples(expr);

    print_quads(quads);

    return 0;
}
