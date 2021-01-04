#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include "fs.h"
#include "my_start_exit.c"
#include "term.cpp"
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
            command cmd = parse_command(in_vec[0]);

            //TODO: Command Parse & Run
            switch (cmd)
            {
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
