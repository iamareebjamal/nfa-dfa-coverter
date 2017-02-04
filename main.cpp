#include <iostream>
#include "nfa_parser.h"
#include "utils.cpp"

using namespace std;

int main() {
    try {
        nfa_parser parser("nfa.txt");
        nfa automata = parser.create_nfa();
        cout << automata.tostring() << endl;
        automata.to_dfa();
    } catch (char const* message) {
        cout << message << endl;
    } catch (const string& message) {
        cout << message << endl;
    }

    return 0;
}