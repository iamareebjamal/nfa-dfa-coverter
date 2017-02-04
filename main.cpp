#include <iostream>
#include "nfa_parser.h"
#include "textutils.cpp"

using namespace std;

int main() {
    try {
        nfa_parser parser("nfa.txt");
        nfa automata = parser.create_nfa();
        cout << automata.tostring() << endl;

        set<string> seti;
        seti.insert("q");
        seti.insert("r");
        seti.insert("p");
        cout << "Epsilon : " << to_string(automata.get_epsilon_closure(seti)) << endl;
    } catch (char const* message) {
        cout << message << endl;
    } catch (const string& message) {
        cout << message << endl;
    }
    return 0;
}