#ifndef NFA_NFA_H
#define NFA_NFA_H

#include <string>
#include <set>
#include <map>

using namespace std;

class nfa {
private:
    set<string> alphabet, states, final;
    string initial;

    map< pair<string, string>, set<string> > transitions;
    map< set<string>, set<string> > epsilon_closures;
public:
    void set_states(const set<string>& states, const set<string>& initial, const set<string>& final);
    void set_alphabet(const set<string>& alphabet);

    void add_transition(const string& current_state, const string& alphabet, const set<string>& result);
    const set<string> get_states(const string& state, const string& alphabet);
    const set<string> get_epsilon_closure(const string& state);
    const set<string> get_epsilon_closure(const set<string>& states);

    const string tostring();
};


#endif //NFA_NFA_H
