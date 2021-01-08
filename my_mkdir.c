//
// Created by 孙鹏 on 2020/12/26.
//

#ifndef FILE_SYSTEM_DESIGN_FS_MKDIR
#define FILE_SYSTEM_DESIGN_FS_MKDIR

#include <string.h>
#include <stdio.h>
#include "fs.h"
#include "inode.h"
#include "c_operator.h"

void my_mkdir(char *dirname)
{
    inode *curr_dir_point = NULL;
    curr_dir_point = get_inode_point(curr_dir_inode);

    int curr_dir_index;
    curr_dir_index = curr_dir_point->direction_chart_id;

    index_element *curr_dir_index_start = NULL;
    curr_dir_index_start = virtualDisk + curr_dir_index*BLOCK_SIZE;

    fcb *curr_dir_fcb = NULL;
    curr_dir_fcb = virtualDisk + curr_dir_index_start->physical_id*BLOCK_SIZE;

    for (int i = 0; i < curr_dir_point->length/ sizeof(fcb); ++i)
    {
        if (strcmp(dirname, curr_dir_fcb->filename)==0)
        {
            printf("\n%s is already existed\n",dirname);
            return;
        }
        curr_dir_fcb++;
    }

    int new_inode;
    int new_index_label;
    new_inode = create_inode();                      //为新的目录文件创建索引节点
    new_index_label = request_block();               //为新的目录文件创建索引表

    inode *new_inode_point = NULL;
    new_inode_point = get_inode_point(new_inode);    //获取新索引节点的指针
    new_inode_point->attribute = 1;
    new_inode_point->direction_chart_id = new_index_label;
    new_inode_point->length = 0;

    int new_block;
    index_element *index_label_start;
    new_block = request_block();
    index_label_start = virtualDisk + new_index_label*BLOCK_SIZE;
    index_label_start->logical_id = 0;
    index_label_start->physical_id = new_block;

    fcb *fcb_temp;
    fcb_temp = virtualDisk + new_block*BLOCK_SIZE;
    char *fname1 = ".";
    char *fname2 = "..";
    memcpy(fcb_temp->filename, fname1, sizeof(char)*strlen(fname1));
    fcb_temp->i_ino = new_inode;
    fcb_temp++;
    memcpy(fcb_temp->filename, fname2, sizeof(char)*strlen(fname2));
    fcb_temp->i_ino = curr_dir_inode;
    new_inode_point->length = sizeof(fcb)*2;

    memcpy(curr_dir_fcb->filename, dirname, sizeof(char)*strlen(dirname));
    curr_dir_fcb->i_ino = new_inode;
    curr_dir_point->length += sizeof(fcb);
}
#endif
