#ifndef TEXT_UTILS_CPP
#define TEXT_UTILS_CPP

#include <sstream>
#include <vector>
#include <iostream>

using namespace std;

template<typename T>
void split(const string &s, const char delim, T result) {
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim)) {
        *(result++) = item;
    }
}


inline vector<string> str_split(const string &s, const char delim) {
    vector<string> elems;
    split(s, delim, back_inserter(elems));
    return elems;
}

inline string get_contained(string& str, const char start, const char end) {
    size_t first = str.find_first_of(start);
    size_t last = str.find_last_of(end);

    if(first == string::npos || last == string::npos)
        throw "Parse Error : All NFA arguments must be enclosed within {}";

    return str.substr(first+1, last-first-1);
}

inline string strip(string& str, const char c) {
    for (int i = 0; i < str.length(); ++i) {
        char current = str[i];
        if(current == c) {
            str.erase(str.begin() + i);
            i--;
        }
    }

    return str;
}

inline string strip(string& str) {
    return strip(str, ' ');
}


#endif //TEXT_UTILS_CPP