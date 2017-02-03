#include "nfa_parser.h"

#include <fstream>
#include <iostream>
#include "textutils.cpp"

nfa_parser::nfa_parser(const string& filename) {
    ifstream file(filename.c_str());

    if (!file.is_open())
        throw "File I/O error : Error opening file!";

    string line;
    while ( getline(file,line) ) {
        if(strip(line).length() <= 0)
            continue;

        vector<string> splitted = str_split(line, ':');
        if(splitted.size() != 2)
            throw "Parse Error : A single line must consist one and only one ':' symbol!";

        string contained = get_contained(splitted[1], '{', '}');
        linemap[strip(splitted[0])] = strip(contained);
    }

    file.close();

}

void nfa_parser::test() {
    try {
        nfa_parser parser("nfa.txt");

        map<string, string>::const_iterator iter = parser.linemap.begin();
        for (; iter!=parser.linemap.end(); ++iter) {
            cout << "'"<<iter->first << "' " << iter->second << endl;
        }
    } catch (char const* message) {
        cout << message << endl;
    }
}