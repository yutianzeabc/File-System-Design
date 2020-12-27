//
// Created by 孙鹏 on 2020/12/26.
//


#ifndef FILE_SYSTEM_DESIGN_FS_INODE_OPERATOR
#define FILE_SYSTEM_DESIGN_FS_INODE_OPERATOR

#include <string.h>
#include <time.h>
#include "inode.h"
#include "fs.h"

/*获取当前时间*/
unsigned long get_time()
{
    unsigned long result = 0;
    time_t timer;
    struct tm *tblock;
    time(&timer);
    tblock = gmtime(&timer);

    result = (result+tblock->tm_hour+8)*100;
    result = (result+tblock->tm_min)*100;
    result = (result+tblock->tm_sec);

    return result;
}

/*获取当前日期*/
unsigned long get_date()
{
    unsigned long result = 0;
    time_t timer;
    struct tm *tblock;
    time(&timer);
    tblock = gmtime(&timer);

    result = (tblock->tm_year+1900)*100;
    result = (result+tblock->tm_mon+1)*100;
    result = (result+tblock->tm_mday);

    return result;
}

/*创建一个索引节点并返回该索引节点编号*/
int create_inode()
{
    char *next_inode_start = NULL;
    next_inode_start = virtualDisk + 2*BLOCK_SIZE + inode_id*sizeof(inode);

    inode inode_temp;
    inode_temp.i_ino = inode_id;
    inode_temp.time = get_time();
    inode_temp.date = get_date();

    memcpy(next_inode_start, &inode_temp, sizeof(inode)*1);
    return inode_id++;
}

/*根据索引节点编号获取该索引节点的起始位置*/
inode *get_inode_point(int id)
{
    inode *point_temp = NULL;
    point_temp = virtualDisk + 2*BLOCK_SIZE + id*sizeof(inode);
    return point_temp;
}

/*根据索引节点编号获取该索引节点*/
inode find_inode(int id)
{
    inode temp;
    memcpy(&temp,virtualDisk+2*BLOCK_SIZE+id*sizeof(inode),sizeof(inode)*1);
    return temp;
}
#endif //FILE_SYSTEM_DESIGN_FS_INODE_OPERATOR