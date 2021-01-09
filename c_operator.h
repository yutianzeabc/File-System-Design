//
// Created by 孙鹏 on 2021/1/5.
//

#ifndef FILE_SYSTEM_DESIGN_C_OPERATOR_H
#define FILE_SYSTEM_DESIGN_C_OPERATOR_H

#include "inode.h"
#include "fs.h"

#ifdef __cplusplus
extern "C" {
#endif
int request_block();
void recycle_block(int id);
unsigned long get_time();
unsigned long get_date();
int create_inode();
inode *get_inode_point(int id);
inode find_inode(int id);
void my_cd(char *dirname);
int my_create(char *filename);
void my_format();
void my_ls();
void my_mkdir(char *dirname);
int my_open(char *filename);
int my_close(int fd);
int my_read(int fd, int len);
void my_rmdir(char *dirname);
int start_sys();
int exit_sys();
int my_write(int fd, int mode);
int my_rm(char *filename);
#ifdef __cplusplus
}
#endif
#endif //FILE_SYSTEM_DESIGN_C_OPERATOR_H

