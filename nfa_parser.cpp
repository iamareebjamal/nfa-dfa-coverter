#include "nfa_parser.h"

#include <fstream>
#include <iostream>
#include "utils.cpp"

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
        string contained = splitted[1];

        if(label != "Q0") // Initial state is not a set
            contained = get_contained(contained, '{', '}');

        symbolmap[label] = strip(contained);
    }

    file.close();
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

nfa nfa_parser::create_nfa() {
    string error_message = "NFA Parse Error : ";

    set<string> states = get_set_items("Q");
    set<string> alphabet = get_set_items("E");
    set<string> initial = get_set_items("Q0");
    set<string> final = get_set_items("F");

    nfa automata;
    automata.set_states(states, initial, final);
    automata.set_alphabet(alphabet);

    alphabet.insert("e"); // Add epsilon move in alphabet
    set<string>::const_iterator i, j;
    for (i = states.begin(); i != states.end(); ++i) {

        for (j = alphabet.begin(); j != alphabet.end(); ++j) {
            string key = "T(" + *i + "," + *j + ")";

            try {
                automata.add_transition(*i, *j, get_set_items(key));
            } catch (const string& message) {
                cout << "Transition Error : Required Transition for state '"
                << *i << "' on alphabet '" << *j << "' not defined!" << endl;
                throw;
            }
        }

    }
    alphabet.erase("e"); // Remove epsilon move from alphabet

    if(symbolmap.size()>0) {
        cout << "Input File contains the  following undefined transitions :" << endl;
        map<string, string>::const_iterator iter;
        for (iter = symbolmap.begin(); iter!=symbolmap.end(); ++iter) {
            cout << iter->first << " -> " << iter->second << endl;
        }

        throw error_message + "Undefined transitions!";
    }


    return automata;
}