#ifndef NFA_NFA_PARSER_H
#define NFA_NFA_PARSER_H

#include <string>
#include <vector>
#include <map>

using namespace std;

class nfa_parser {
public:
    vector<string> lines;
    map<string, string> linemap;

    nfa_parser(const string& filename);

    static void test();

};


#endif //NFA_NFA_PARSER_H
