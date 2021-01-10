//
// Created by 余天泽 on 2020/12/26.
//

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include "c_operator.h"
#include "cpp_operator.h"
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

            switch (cmd)
            {
            case CD:
                if (in_vec.size() == 2)
                {
                    char *dirname = const_cast<char *>((in_vec[1]).c_str());
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
                    char *dirname = const_cast<char *>((in_vec[1]).c_str());
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
                    char *dirname = const_cast<char *>((in_vec[1]).c_str());
                    my_rmdir(dirname);
                }
                else
                {
                    cout << "Illegal Command" << endl;
                }
                break;

            case CREATE:
                if (in_vec.size() == 2)
                {
                    char *filename = const_cast<char *>((in_vec[1]).c_str());
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
                    char *filename = const_cast<char *>((in_vec[1]).c_str());
                    my_rm(filename);
                }
                else
                {
                    cout << "Illegal Command" << endl;
                }
                break;

            case OPEN:
                if (in_vec.size() == 2)
                {
                    char *filename = const_cast<char *>((in_vec[1]).c_str());
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
                    char *fd_s = const_cast<char *>((in_vec[1]).c_str());
                    if (isdigit(fd_s[0]))
                    {
                        int fd = atoi(fd_s);
                        my_close(fd);
                        break;
                    }  
                }
                cout << "Illegal Command" << endl;
                break;

            case READ:
                if (in_vec.size() == 3)
                {
                    char *fd_s = const_cast<char *>((in_vec[1]).c_str());
                    char *len_s = const_cast<char *>((in_vec[2]).c_str());
                    if (isdigit(fd_s[0]) && isdigit(len_s[0])) 
                    {
                        int fd = atoi(fd_s);
                        int len = atoi(len_s);
                        my_read(fd, len);
                        break;
                    }
                }
                cout << "Illegal Command" << endl;
                break;

            case WRITE:
                if (in_vec.size() == 3)
                {
                    char *fd_s = const_cast<char *>((in_vec[1]).c_str());
                    char *mode_s = const_cast<char *>((in_vec[2]).c_str());
                    if (isdigit(fd_s[0]) && isdigit(mode_s[0])) 
                    {
                        int fd = atoi(fd_s);
                        int mode = atoi(mode_s);
                        my_write(fd, mode);
                        break;
                    }
                }
                cout << "Illegal Command" << endl;
                break;

            case UNKNOWN:
                cout << "Unknown Command" << endl;
                break;

            case EXIT:
                exit_sys();
                return 0;

            default:
                break; // IMPOSSIBLE
            }
        }
    }
    return -1;
}
