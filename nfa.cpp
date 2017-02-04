#include <queue>
#include <iostream>
#include "nfa.h"
#include "utils.cpp"

string error_message = "NFA Creation Error : ";

void verify_state_set(const set<string>& states, const set<string>& state_set) {

    set<string>::const_iterator it;
    for (it = state_set.begin(); it != state_set.end(); ++it) {
        if(!states.count(*it))
            throw error_message + "State '" + *it + "' does not belong to Q!";
    }
}


void verify_states(set<string> states, set<string> initial, set<string> final) {
    if(initial.size() != 1)
        throw error_message + "There should be one and only one initial state!";

    if(final.size() < 1 || final.size() > states.size() )
        throw error_message + "Final states should be between 1 and total number of states!";

    // Verify if all the states in initial and final belong to state vector

    if (!states.count(*initial.begin()))
        throw error_message + "Initial state '" + *initial.begin() + "' does not belong to Q!";

    try {
        verify_state_set(states, final);
    } catch (const string& message) {
        cout << "Invalid Final State!" << endl;
        throw;
    }
}

void nfa::set_states(const set<string> &states, const set<string> &initial, const set<string> &final) {
    verify_states(states, initial, final);

    this->states = states;
    this->final = final;
    this->initial = *initial.begin();
}

void nfa::set_alphabet(const set<string> &alphabet) {
    if(alphabet.count("e"))
        throw "NFA Parse Error : Language alphabet 'e' clashes with keyword for epsilon!";

    this->alphabet = alphabet;
}

void nfa::add_transition(const string& current_state, const string& alphabet, const set<string>& result) {
    verify_state_set(states, result);
    transitions[make_pair(current_state, alphabet)] = result;
}

const set<string> nfa::get_states(const string& state, const string& alphabet) {
    pair<string, string> key = make_pair(state, alphabet);
    if(!transitions.count(key))
        throw "NFA Error : Invalid Transition!";

    return transitions[key];
}

const set<string> nfa::get_states(const set<string> &states, const string &alphabet) {
    set<string> compound_states;

    set<string>::const_iterator it;
    for(it = states.begin(); it != states.end(); ++it) {
        set<string> out_state = get_states(*it, alphabet);
        compound_states.insert(out_state.begin(), out_state.end());
    }

    return compound_states;
}

const set<string> nfa::get_epsilon_closure(const string &state) {
    set<string> key;
    key.insert(state);

    if(epsilon_closures.count(key))
        return epsilon_closures[key];

    set<string> epsilon_states;

    queue<string> remaining;
    remaining.push(state);

    while (!remaining.empty()) {
        string current = remaining.front();

        epsilon_states.insert(current);

        set<string> epsilon_moves = get_states(current, "e");
        set<string>::const_iterator it;
        for(it = epsilon_moves.begin(); it != epsilon_moves.end(); ++it) {
            if(!epsilon_states.count(*it))
                remaining.push(*it);
        }

        remaining.pop();
    }

    epsilon_closures[key] = epsilon_states;

    return epsilon_states;
}

const set<string> nfa::get_epsilon_closure(const set<string> &states) {
    if (epsilon_closures.count(states))
        return epsilon_closures[states];

    set<string> epsilon_states;

    set<string>::const_iterator it;
    for(it = states.begin(); it != states.end(); ++it) {
        set<string> current_states = get_epsilon_closure(*it);
        epsilon_states.insert(current_states.begin(), current_states.end());
    }

    epsilon_closures[states] = epsilon_states;

    return epsilon_states;
}

bool nfa::is_final(const set<string> &states) {
    set<string>::const_iterator it;

    for(it = states.begin(); it != states.end(); ++it) {
        if(contains(final, *it))
            return true;
    }

    return false;
}

void nfa::to_dfa() {
    cout << "DFA Conversion : \n" << endl;
    set<string> initial = get_epsilon_closure(this->initial);

    queue< set<string> > remaining;
    remaining.push(initial);

    vector< set<string> > dfa_states;

    set<string>::const_iterator it;

    while(!remaining.empty()) {
        set<string> current = remaining.front();
        remaining.pop();

        if(contains(dfa_states, current))
            continue;

        cout << "For state : { " << to_string(current, ',') << " }" << endl;
        for (it = alphabet.begin(); it != alphabet.end(); ++it) {
            set<string> epsilon_state = get_epsilon_closure(get_states(current, *it));
            cout << "    " << *it << " -> { " << to_string(epsilon_state, ',') << " }" << endl;

            if (!contains(dfa_states, epsilon_state) && !epsilon_state.empty())
                remaining.push(epsilon_state);
        }

        dfa_states.push_back(current);
        cout << endl;
    }

    cout << "\nInitial State : " << endl;
    cout << "{ " << to_string(dfa_states[0], ',') << " }" << endl;

    cout << "Final States : " << endl;
    for (int i = 0; i < dfa_states.size(); ++i) {
        set<string> current = dfa_states[i];

        if(is_final(current))
            cout << "{ " << to_string(current, ',') << " }" << endl;
    }

}

const string get_transition_string(const map< pair<string, string>, set<string> > m) {
    string output;
    map< pair<string, string>, set<string> >::const_iterator it;

    for(it = m.begin(); it != m.end(); ++it) {
        output += "(" + it->first.first + ", " + it->first.second + ") -> { " + to_string(it->second) + " }\n";
    }

    return output;
}

string nfa::tostring() {
    return "Alphabet:\n" +
            to_string(alphabet) +
            "\nStates:\n" +
            to_string(states) +
            "\nInitial State : \n" +
            initial +
            "\nFinal States:\n" +
            to_string(final) +
            "\nTransitions:\n" +
            get_transition_string(transitions);
}