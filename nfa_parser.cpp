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

vector<string> nfa_parser::get_set_items(const string& key) {
    vector<string> items = split(get_item(symbolmap, key), ',');
    symbolmap.erase(key);

    return items;
}

void print_vector(vector<string> v) {
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << endl;
    }
}

void nfa_parser::create_nfa() {

    vector<string> states = get_set_items("Q");
    vector<string> language = get_set_items("E");
    vector<string> initial = get_set_items("Q0");
    vector<string> final = get_set_items("F");

    print_vector(states);
    print_vector(language);
    print_vector(initial);
    print_vector(final);

    map<string, string>::const_iterator iter = symbolmap.begin();
    for (; iter!=symbolmap.end(); ++iter) {
        cout << "'"<<iter->first << "' " << iter->second << endl;
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