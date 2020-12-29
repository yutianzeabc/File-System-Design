//
// Created by 孙鹏 on 2020/12/22.
//

#ifndef FILE_SYSTEM_DESIGN_INODE_H
#define FILE_SYSTEM_DESIGN_INODE_H

typedef struct FCB
{
    char filename[20];
    unsigned long i_ino;
} fcb;

typedef struct INODE
{
    int i_ino;         //索引节点号
    int attribute;              //文件属性 1为目录文件，0为普通文件
    int access;                 //文件权限
    unsigned long time;         //文件创建时间
    unsigned long date;         //文件创建日期
    int direction_chart_id;      //文件索引表对应的磁盘块号
    unsigned long length;        //文件长度（字节数）
    char username[8];            //文件所属用户名
} inode;
at

#endif //FILE_SYSTEM_DESIGN_INODE_H
