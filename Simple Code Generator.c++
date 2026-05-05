#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Quadruple {
    string op;
    string arg1;
    string arg2;
    string result;
};

// Generate 3-address code from quadruples
void generate_code(const vector<Quadruple>& quadruples) {
    for (const auto& q : quadruples) {
        cout << q.result << " = " 
             << q.arg1 << " " 
             << q.op << " " 
             << q.arg2 << endl;
    }
}

int main() {
    vector<Quadruple> quads = {
        {"+", "a", "b", "t1"},
        {"*", "t1", "c", "t2"}
    };

    generate_code(quads);

    return 0;
}
