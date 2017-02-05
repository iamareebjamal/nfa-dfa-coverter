#include <iostream>
#include "nfa_parser.h"

using namespace std;

int main() {
    try {
        nfa_parser parser("nfa1.txt");
        nfa automata = parser.create_nfa();

        cout << "NFA:\n\n" << automata.tostring() << endl << endl;
        cout << automata.to_dfa() << endl;
    } catch (char const* message) {
        cout << message << endl;
    } catch (const string& message) {
        cout << message << endl;
    }

    return 0;
}