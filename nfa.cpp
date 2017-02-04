#include "nfa.h"
#include "textutils.cpp"

void verify_states(set<string> states, set<string> initial, set<string> final) {
    string error_message = "NFA Creation Error : ";

    if(initial.size() != 1)
        throw error_message + "There should be one and only one initial state!";

    if(final.size() < 1 || final.size() > states.size() )
        throw error_message + "Final states should be between 1 and total number of states!";

    // Verify if all the states in initial and final belong to state vector

    if (!states.count(*initial.begin()))
        throw error_message + "Initial state '" + *initial.begin() + "' does not belong to Q!";

    set<string>::const_iterator it;
    for (it = final.begin(); it != final.end(); ++it) {
        if(!states.count(*it))
            throw error_message + "Final state '" + *it + "' does not belong to Q!";
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
    transitions[make_pair(current_state, alphabet)] = result;
}

const set<string> nfa::get_states(string state, string alphabet) {
    pair<string, string> key = make_pair(state, alphabet);
    if(!transitions.count(key))
        throw "NFA Error : Invalid Transition!";

    return transitions[key];
}

const string get_transition_string(const map< pair<string, string>, set<string> > m) {
    string output;
    map< pair<string, string>, set<string> >::const_iterator it;

    for(it = m.begin(); it != m.end(); ++it) {
        output += it->first.first + "," + it->first.second + " -> " + to_string(it->second);
    }

    return output;
}

const string nfa::tostring() {
    return "Alphabet:\n" +
            to_string(alphabet) +
            "States:\n" +
            to_string(states) +
            "Initial State : \n" +
            initial + "\n" +
            "Final States:\n" +
            to_string(final) +
            "Transitions:\n" +
            get_transition_string(transitions);
}