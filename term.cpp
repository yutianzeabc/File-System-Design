//
// Created by 余天泽 on 2020/12/26.
//

#ifndef FILE_SYSTEM_DESIGN_FS_TERM
#define FILE_SYSTEM_DESIGN_FS_TERM

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "cmd.hpp"
#include "cpp_operator.h"

using namespace std;

vector<string> spilt_s(string in) {
    string in_s;
    stringstream ss(in);
    vector<string> in_vec;
    while(ss>>in_s) {
        in_vec.push_back(in_s);
    }
    return in_vec;
}

command parse_commands(string cmd) {
    if (cmd == "cd") return CD;
    else if (cmd == "ls") return LS;
    else if (cmd == "mkdir") return MKDIR;
    else if (cmd == "rmdir") return RMDIR;
    else if (cmd == "create") return CREATE;
    else if (cmd == "rm") return RM;
    else if (cmd == "open") return OPEN;
    else if (cmd == "close") return CLOSE;
    else if (cmd == "read") return READ;
    else if (cmd == "write") return WRITE;
    else if (cmd == "exit") return EXIT;
    return UNKNOWN;
}

#endif

#ifdef TERM_DEBUG
int main(int argc, char const *argv[])
{
    string s;
    getline(cin,s);
    vector<string> vec = spilt_s(s);
//    cout<<vec.size();
    for (string i:vec) {
        cout<<i<<endl;
    }
    return 0;
}
#endif

