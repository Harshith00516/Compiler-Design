#include <iostream>
#include <vector>

using namespace std;

class StackMemory {
private:
    vector<int> stack;

public:
    // Allocate (push)
    void allocate(int value) {
        stack.push_back(value);
    }

    // Deallocate (pop)
    int deallocate() {
        if (stack.empty()) {
            return -1; // or handle underflow properly
        }
        int val = stack.back();
        stack.pop_back();
        return val;
    }

    // Utility: display stack
    void display() {
        cout << "Stack (top -> bottom): ";
        for (int i = stack.size() - 1; i >= 0; i--) {
            cout << stack[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    StackMemory mem;

    mem.allocate(10);
    mem.allocate(20);

    cout << "Deallocated: " << mem.deallocate() << endl;

    return 0;
}
