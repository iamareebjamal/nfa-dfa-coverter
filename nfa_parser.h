#ifndef NFA_NFA_PARSER_H
#define NFA_NFA_PARSER_H

#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

class nfa_parser {
public:
    map<string, string> symbolmap;

    nfa_parser(const string& filename);
    void create_nfa();
    set<string> get_set_items(const string& key);

    static void test();

};


#endif //NFA_NFA_PARSER_H
