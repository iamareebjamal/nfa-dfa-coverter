#include <iostream>
#include <fstream>
#include "nfa_parser.h"

using namespace std;

void create_dfa(const string& name) {
    string nfa_filename = "data/" + name + ".txt";
    string dfa_filename = "data/" + name + "_converted.txt";

    try {
        cout << "Loading NFA File : " << nfa_filename << endl;
        nfa_parser parser(nfa_filename);
        nfa automata = parser.create_nfa();

        cout << "NFA:\n\n" << automata.tostring() << endl << endl;

        string dfa = automata.to_dfa();
        ofstream dfa_file(dfa_filename.c_str());
        dfa_file << dfa;
        dfa_file.close();

        cout << "File written to : " << dfa_filename << endl;
        cout << "---------------" << endl;
    } catch (char const* message) {
        cout << message << endl;
    } catch (const string& message) {
        cout << message << endl;
    }
}

int main() {
    cout << "---------------" << endl;
    create_dfa("nfa0");

    /*
    create_dfa("nfa1");
    create_dfa("nfa2");
    create_dfa("nfa3");
    create_dfa("nfa4");
    */
    return 0;
}