#include "fs.h"
#include "inode.h"
#ifndef FILE_SYSTEM_DESIGN_COMMON_H
#define FILE_SYSTEM_DESIGN_COMMON_H
char* nowdir;//当前目录
useropen openlist[10];//运行时文件打开的有序list，下标即为为fd
int openlist_length;
#endif