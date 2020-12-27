#include <iostream>
#include <sstream>
#include <string>
#include <cstdio>
#include <vector>
#include <algorithm>
#include "term.hpp"

using namespace std;

vector<string> spilt_s(string in) {
    string in_s;
    stringstream ss(in);
    vector<string> in_vec;

    transform(in.begin(),in.end(),in.begin(),::tolower);
    while(ss>>in_s) {
        in_vec.push_back(in_s);
    }
    return in_vec;
}

command parse_command(string cmd) {
    if (cmd == "exit") return EXIT;
    return UNKNOWN;
} 