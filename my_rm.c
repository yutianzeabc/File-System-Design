//
// Created by 马钵涛 on 2021/1/8
//

#ifndef FILE_SYSTEM_DESIGN_MY_RM
#define FILE_SYSTEM_DESIGN_MY_RM

#include "fs.h"
#include "inode.h"
#include "c_operator.h"
#include <stdio.h>
#include <string.h>

int my_rm(char *filename)
{
    int i = 0;
    for (i = 0; i < 10; ++i)
    {
        if(USEROPENS[i].openlabel==1)
        {
            if (strcmp(filename, USEROPENS[i].filename)==0)
                break;
        }
    }
    if (i<10)
    {
        printf("Error:%s is opening\n",filename);
        return -1;
    }   //文件已经打开，无法删除

    inode *curr_dir_point = NULL;
    curr_dir_point = get_inode_point(curr_dir_inode); //得到当前目录文件的索引节点

    int curr_dir_index;
    curr_dir_index = curr_dir_point->direction_chart_id; //文件索引表所在磁盘块号

    index_element *curr_dir_index_start = NULL;
    curr_dir_index_start = virtualDisk + curr_dir_index * BLOCK_SIZE; //找到磁盘块头

    fcb *curr_dir_fcb = NULL;
    curr_dir_fcb = virtualDisk + curr_dir_index_start->physical_id * BLOCK_SIZE;  //

    for (i = 0; i < curr_dir_point->length / sizeof(fcb); ++i)
    {
        if (strcmp(filename, curr_dir_fcb->filename) == 0)
        {
            inode *temp = get_inode_point(curr_dir_fcb->i_ino);
            if (temp->attribute==0)
                break;
        }
        curr_dir_fcb++;
    }

    if (i == curr_dir_point->length / sizeof(fcb))
    {
        printf("\n%s is not exist\n ", filename);
        return -1;
    }

    inode *target = get_inode_point(curr_dir_fcb->i_ino);
    index_element *index_start = virtualDisk + target->direction_chart_id*BLOCK_SIZE;

    int j = 0;
    if ((target->length%BLOCK_SIZE)==0)
    {
        if (target->length<BLOCK_SIZE)
        {
            for(j=0; j<(target->length/BLOCK_SIZE+1);j++)
            {
                printf("Recycle No.%d\n",index_start->physical_id);
                recycle_block(index_start->physical_id);
                index_start++;
            }
        }
        else
        {
            for(j=0; j<(target->length/BLOCK_SIZE);j++)
            {
                printf("Recycle No.%d\n",index_start->physical_id);
                recycle_block(index_start->physical_id);
                index_start++;
            }
        }
    }
    for(j=0; j<(target->length/BLOCK_SIZE+1);j++)
    {
        printf("Recycle No.%d\n",index_start->physical_id);
        recycle_block(index_start->physical_id);
        index_start++;
    }

    printf("Recycle No.%d\n",target->direction_chart_id);
    recycle_block(target->direction_chart_id);

    int number = (curr_dir_point->length/ sizeof(fcb)-i)-1;   //位于删除目录项后面的目录项个数
    fcb *temp = curr_dir_fcb + 1;
    memcpy(curr_dir_fcb,temp, sizeof(fcb)*number);            //目录下向上移动
    curr_dir_point->length -= sizeof(fcb)*1;
    return 0;
}

#endif
