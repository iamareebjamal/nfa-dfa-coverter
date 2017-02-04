#ifndef NFA_NFA_PARSER_H
#define NFA_NFA_PARSER_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include "nfa.h"

using namespace std;

class nfa_parser {
private:
    map<string, string> symbolmap;
    set<string> get_set_items(const string& key);

public:
    nfa_parser(const string& filename);
    nfa create_nfa();

};


#endif //NFA_NFA_PARSER_H
