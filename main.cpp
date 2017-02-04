#include <iostream>
#include "nfa_parser.h"

using namespace std;

int main() {
    try {
        nfa_parser parser("nfa1.txt");
        nfa automata = parser.create_nfa();

        cout << "NFA:\n\n" << automata.tostring() << endl;
        automata.to_dfa();
    } catch (char const* message) {
        cout << message << endl;
    } catch (const string& message) {
        cout << message << endl;
    }

    return 0;
}