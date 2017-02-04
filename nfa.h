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
public:
    void set_states(const set<string>& states, const set<string>& initial, const set<string>& final);
    void set_alphabet(const set<string>& alphabet);

    void add_transition(const string& current_state, const string& alphabet, const set<string>& result);
    const set<string> get_states(string state, string alphabet);

    const string tostring();
};


#endif //NFA_NFA_H
