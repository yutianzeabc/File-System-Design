#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include "fs.h"
#include "my_cd.c"
#include "my_ls.c"
#include "my_mkdir.c"
//#include "my_rmdir.c"
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
            case CD:
                if (in_vec.size() == 2)
                {
                    char *dirname = (char *)(in_vec[1]).c_str();
                    my_cd(dirname);
                }
                else
                {
                    cout << "Illegal Command" << endl;
                }
                break;

            case LS:
                if (in_vec.size() == 1)
                {
                    my_ls();
                }
                else
                {
                    cout << "Illegal Command" << endl;
                }
                break;

            case MKDIR:
                if (in_vec.size() == 2)
                {
                    char *dirname = (char *)(in_vec[1]).c_str();
                    my_mkdir(dirname);
                }
                else
                {
                    cout << "Illegal Command" << endl;
                }
                break;

            case RMDIR:
                if (in_vec.size() == 2)
                {
                    // TODO:no my_rmdir
                    char *dirname = (char *)(in_vec[1]).c_str();
                    //my_rmdir(dirname);
                }
                else
                {
                    cout << "Illegal Command" << endl;
                }
                break;
            case CREATE:
                if (in_vec.size() == 2)
                {
                    // TODO:no my_create
                    char *filename = (char *)(in_vec[1]).c_str();
                    //my_create(filename);
                }
                else
                {
                    cout << "Illegal Command" << endl;
                }
                break;
            case EXIT:
                // TODO: Exit & Cleanup
                break;

            case UNKNOWN:
                cout << "Unknown Command" << endl;
                break;
            default:
                break; // INPOSSIBLE
            }
        }
    }
    return 0;
}
