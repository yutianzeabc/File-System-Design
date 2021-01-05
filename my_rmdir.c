//
// Created by 孙鹏 on 2021/1/5.
//

#ifndef FILE_SYSTEM_DESIGN_MY_RMDIR
#define FILE_SYSTEM_DESIGN_MY_RMDIR

#include "fs.h"
#include "inode.h"
#include "inode_operator.c"
#include "group_link_operator.c"
#include <string.h>

void my_rmdir(char *dirname)
{
    inode *curr_dir_point = NULL;
    curr_dir_point = get_inode_point(curr_dir_inode);

    int curr_dir_index;
    curr_dir_index = curr_dir_point->direction_chart_id;

    index_element *curr_dir_index_start = NULL;
    curr_dir_index_start = virtualDisk + curr_dir_index*BLOCK_SIZE;

    fcb *curr_dir_fcb = NULL;
    curr_dir_fcb = virtualDisk + curr_dir_index_start->physical_id*BLOCK_SIZE;

    int i;
    for (i = 0; i < curr_dir_point->length/ sizeof(fcb); ++i)
    {
        if(strcmp(dirname, curr_dir_fcb->filename)==0)
        {
                break;
        }
        curr_dir_fcb++;
    }
    if (i==curr_dir_point->length/ sizeof(fcb))
    {
        printf("\n%s Not exist\n",dirname);
        return;
    }

    int target_dir = curr_dir_fcb->i_ino;
    inode *target_dir_inode = get_inode_point(target_dir);
    if(target_dir_inode->length > 2* sizeof(fcb))
    {
        printf("/n%s Folder Not Empty\n",dirname);
        return;
    }
    index_element *index_temp = virtualDisk + (target_dir_inode->direction_chart_id)*BLOCK_SIZE;
    recycle_block(index_temp->physical_id);               //回收分配的盘块
    recycle_block(target_dir_inode->direction_chart_id);  //回收索引表

    int number = (curr_dir_point->length/ sizeof(fcb)-i)-1;   //位于删除目录项后面的目录项个数
    fcb *temp = curr_dir_fcb + 1;
    memcpy(curr_dir_fcb,temp, sizeof(fcb)*number);            //目录下向上移动
    curr_dir_point->length -= sizeof(fcb)*1;
}
#endif
