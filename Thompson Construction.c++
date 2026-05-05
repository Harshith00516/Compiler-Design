#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

struct State {
    unordered_map<char, vector<State*>> edges;
};

State* regex_to_nfa(const string& regex) {
    State* start = new State();
    State* current = start;

    for (char ch : regex) {
        State* next_state = new State();
        current->edges[ch].push_back(next_state);
        current = next_state;
    }

    return start;
}

// Helper function to print transitions (1-level for demo)
void print_nfa(State* state) {
    for (const auto& pair : state->edges) {
        char symbol = pair.first;
        cout << symbol << " -> " << pair.second.size() << " state(s)" << endl;
    }
}

int main() {
    string regex = "ab*";
    State* nfa = regex_to_nfa(regex);

    print_nfa(nfa);

    return 0;
}
