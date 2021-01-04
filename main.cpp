#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include "fs.h"
#include "my_mkdir.c"
#include "my_start_exit.c"
#include "term.cpp"
#include "cmd.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    string in;
    while (1)
    {
        getline(cin, in);
        if (in.size() > 0)
        {
            vector<string> in_vec = spilt_s(in);
            command cmd = parse_commands(in_vec[0]);

            //TODO: Command Parse & Run
            switch (cmd)
            {
            case MKDIR:
                if (in.size() > 1) {
                    char *dirname =  (char *)(in_vec[1]).c_str();
                    my_mkdir(dirname);
                } 
                break;
            case EXIT:
                // TODO: Exit & Cleanup
                break;
            case UNKNOWN:
                break;
            default:
                break; // INPOSSIBLE
            }
        }
    }
    return 0;
}
