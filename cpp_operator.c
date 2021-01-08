//
// Created by 孙鹏 on 2021/1/5.
//

#ifndef FILE_SYSTEM_DESIGN_CPP_OPERATOR_H
#define FILE_SYSTEM_DESIGN_CPP_OPERATOR_H

#include "cmd.hpp"
#include <string>
#include <vector>

using namespace std;

vector<string> spilt_s(string in);
command parse_commands(string cmd);

#endif //FILE_SYSTEM_DESIGN_CPP_OPERATOR_H
