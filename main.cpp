//
// Created by 余天泽 on 2020/12/26.
//

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include "fs.h"
#include "my_cd.c"
#include "my_ls.c"
#include "my_mkdir.c"
//#include "my_rmdir.c"
//#include "my_rm.c"
#include "my_open_close.c"
#include "my_read.c"
#include "my_write.c"
#include "my_start_exit.c"
#include "term.cpp"
#include "cmd.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    start_sys();

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
                    char *dirname = (in_vec[1]).c_str();
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
                    char *dirname = (in_vec[1]).c_str();
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
                    char *dirname = (in_vec[1]).c_str();
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
                    char *filename = (in_vec[1]).c_str();
                    my_create(filename);
                }
                else
                {
                    cout << "Illegal Command" << endl;
                }
                break;

            case RM:
                if (in_vec.size() == 2)
                {
                    // TODO:no my_rm
                    char *filename = (in_vec[1]).c_str();
                    //my_rm(filename);
                }
                else
                {
                    cout << "Illegal Command" << endl;
                }
                break;

            case OPEN:
                if (in_vec.size() == 2)
                {
                    char *filename = (in_vec[1]).c_str();
                    my_open(filename);
                }
                else
                {
                    cout << "Illegal Command" << endl;
                }
                break;

            case CLOSE:
                if (in_vec.size() == 2)
                {
                    char *fd_s = (in_vec[1]).c_str();
                    int fd = atoi(fd_s);
                    my_close(fd);
                }
                else
                {
                    cout << "Illegal Command" << endl;
                }
                break;

            case READ:
                if (in_vec.size() == 3)
                {
                    char *fd_s = (in_vec[1]).c_str();
                    char *len_s = (in_vec[2]).c_str();
                    int fd = atoi(fd_s);
                    int len = atoi(len_s);
                    my_read(fd, len_s);
                }
                else
                {
                    cout << "Illegal Command" << endl;
                }
                break;

            case WRITE:
                if (in_vec.size() == 3)
                {
                    char *fd_s = (in_vec[1]).c_str();
                    char *mode_s = (in_vec[2]).c_str();
                    int fd = atoi(fd_s);
                    int mode = atoi(mode_s);
                    my_write(fd, mode);
                }
                else
                {
                    cout << "Illegal Command" << endl;
                }
                break;

            case UNKNOWN:
                cout << "Unknown Command" << endl;
                break;

            case EXIT:
                // TODO: Exit & Cleanup
                exit_sys();
                return 0;

            default:
                break; // INPOSSIBLE
            }
        }
    }
    return -1;
}
