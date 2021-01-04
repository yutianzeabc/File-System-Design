#include <iostream>
#include <sstream>
#include <string>
#include <cstdio>
#include <vector>
#include <algorithm>
#include "cmd.hpp"

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

command parse_command(string cmd) {
    if (cmd == "exit") return EXIT;
    return UNKNOWN;
} 

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