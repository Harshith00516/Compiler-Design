#include <iostream>
#include <set>
#include <map>
#include <stack>
#include <vector>

using namespace std;

// Type aliases for clarity
using State = int;
using StateSet = set<State>;
using TransitionKey = pair<State, char>;

// ε-closure
StateSet epsilon_closure(const StateSet& states,
                         const map<TransitionKey, vector<State>>& transitions) {
    stack<State> st;
    StateSet closure = states;

    for (State s : states)
        st.push(s);

    while (!st.empty()) {
        State state = st.top();
        st.pop();

        auto it = transitions.find({state, 'e'}); // using 'e' for epsilon
        if (it != transitions.end()) {
            for (State nxt : it->second) {
                if (closure.find(nxt) == closure.end()) {
                    closure.insert(nxt);
                    st.push(nxt);
                }
            }
        }
    }
    return closure;
}

// Move function
StateSet move(const StateSet& states, char symbol,
              const map<TransitionKey, vector<State>>& transitions) {
    StateSet result;

    for (State s : states) {
        auto it = transitions.find({s, symbol});
        if (it != transitions.end()) {
            result.insert(it->second.begin(), it->second.end());
        }
    }
    return result;
}

// NFA to DFA conversion
vector<StateSet> nfa_to_dfa(State start,
                           const map<TransitionKey, vector<State>>& transitions) {
    vector<StateSet> dfa_states;
    vector<StateSet> unmarked;

    StateSet start_set = {start};
    unmarked.push_back(start_set);

    while (!unmarked.empty()) {
        StateSet current = unmarked.back();
        unmarked.pop_back();

        dfa_states.push_back(current);

        for (char symbol : {'a', 'b'}) {
            StateSet moved = move(current, symbol, transitions);
            StateSet new_state = epsilon_closure(moved, transitions);

            if (!new_state.empty() &&
                find(dfa_states.begin(), dfa_states.end(), new_state) == dfa_states.end() &&
                find(unmarked.begin(), unmarked.end(), new_state) == unmarked.end()) {
                unmarked.push_back(new_state);
            }
        }
    }

    return dfa_states;
}

int main() {
    map<TransitionKey, vector<State>> transitions;

    // Example: empty transitions like your Python code
    vector<StateSet> dfa = nfa_to_dfa(0, transitions);

    cout << "DFA States:\n";
    for (const auto& stateSet : dfa) {
        cout << "{ ";
        for (int s : stateSet)
            cout << s << " ";
        cout << "}\n";
    }

    return 0;
}
