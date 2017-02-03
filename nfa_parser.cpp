#include "nfa_parser.h"

#include <fstream>
#include <iostream>
#include "textutils.cpp"

nfa_parser::nfa_parser(const string& filename) {
    ifstream file(filename.c_str());

    if (!file.is_open())
        throw "File I/O error : Error opening file!";

    string line;
    while ( getline(file,line) ) {
        if(strip(line).length() <= 0)
            continue;

        vector<string> splitted = split(line, ':');
        if(splitted.size() != 2)
            throw "Parse Error : A single line must consist one and only one ':' symbol!";

        string label = strip(splitted[0]);
        string contained = get_contained(splitted[1], '{', '}');

        symbolmap[label] = strip(contained);
    }

    file.close();
    create_nfa();

}

string get_item(const map<string, string>& m, const string& key) {
    string error_message = "NFA Parse Error : '" + key + "' label not found!";

    if(m.count(key))
        return m.at(key);
    else
        throw error_message;
}

set<string> nfa_parser::get_set_items(const string& key) {
    vector<string> items = split(get_item(symbolmap, key), ',');

    set<string> item_set(items.begin(), items.end());
    symbolmap.erase(key);

    return item_set;
}

template <typename T>
void print(T container) {
    typename T::const_iterator pos;

    for (pos=container.begin(); pos!=container.end(); ++pos) {
        cout << *pos << ' ';
    }
    cout << endl;
}

void verify_states(set<string> states, set<string> initial, set<string> final) {
    string error_message = "NFA Parse Error : ";

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

void nfa_parser::create_nfa() {
    string error_message = "NFA Parse Error : ";

    set<string> states = get_set_items("Q");
    set<string> language = get_set_items("E");
    set<string> initial = get_set_items("Q0");
    set<string> final = get_set_items("F");

    verify_states(states, initial, final);

    // Verifying Language
    if(language.count("e"))
        throw error_message + "Language alphabet 'e' clashes with keyword for epsilon!";

    set<string>::const_iterator i, j;

    language.insert("e"); // Add epsilon move in alphabet
    for (i = states.begin(); i != states.end(); ++i) {
        for (j = language.begin(); j != language.end(); ++j) {
            cout << *i << "," << *j << " -> ";
            try {
                print(get_set_items("T(" + *i + "," + *j + ")"));
            } catch (const string& message) {
                cout << "Transition Error : Required Transition for state '"
                << *i << "' on alphabet '" << *j << "' not defined!" << endl;
                throw;
            }
        }
    }
    language.erase("e"); // Remove epsilon move from alphabet

    if(symbolmap.size()>0) {
        cout << "Input File contains the  following undefined transitions :" << endl;
        map<string, string>::const_iterator iter;
        for (iter = symbolmap.begin(); iter!=symbolmap.end(); ++iter) {
            cout << iter->first << " -> " << iter->second << endl;
        }

        throw error_message + "Undefined transitions!";
    }

}

void nfa_parser::test() {
    try {
        nfa_parser parser("nfa.txt");

    } catch (char const* message) {
        cout << message << endl;
    } catch (const string& message) {
        cout << message << endl;
    }
}