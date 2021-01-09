//
// Created by 马钵涛 on 2020/1/3
//

#ifndef FILE_SYSTEM_DESIGN_FS_CREATE
#define FILE_SYSTEM_DESIGN_FS_CREATE

#include "fs.h"
#include "inode.h"
#include "c_operator.h"
#include <stdio.h>
#include <string.h>

int my_create(char *filename)
{

    inode *curr_dir_point = NULL;
    curr_dir_point = get_inode_point(curr_dir_inode); //得到当前目录文件的索引节点

    int curr_dir_index;
    curr_dir_index = curr_dir_point->direction_chart_id; //文件索引表所在磁盘块号

    index_element *curr_dir_index_start = NULL;
    curr_dir_index_start = virtualDisk + curr_dir_index * BLOCK_SIZE; //找到磁盘块头

    fcb *curr_dir_fcb = NULL;
    curr_dir_fcb = virtualDisk + curr_dir_index_start->physical_id * BLOCK_SIZE;  //

    int i = 0;
    for (i = 0; i < curr_dir_point->length / sizeof(fcb); ++i)
    {
        if (strcmp(filename, curr_dir_fcb->filename) == 0)
        {
            break;
        }
        curr_dir_fcb++;
    }

    if (i < curr_dir_point->length / sizeof(fcb)){
        printf("/n%s is already exist/n ", filename);
        return -1;
    }
    //

    int New_node_id;
    inode *New_node;

    New_node_id = create_inode();
    New_node = get_inode_point(New_node_id);

    New_node->attribute = 0;
    New_node->access = 7;
    New_node->direction_chart_id = request_block();
    New_node->length = 0;
    printf("No.%d distribute to file as index_label\n",New_node->direction_chart_id);
    //

    index_element *index_start = virtualDisk + New_node->direction_chart_id*BLOCK_SIZE;
    index_start->logical_id = 0;
    index_start->physical_id = request_block();
    printf("No.%d distribute to file\n",index_start->physical_id);
    memcpy(curr_dir_fcb->filename, filename, sizeof(char)*strlen(filename));
    curr_dir_fcb->i_ino = New_node_id;

    curr_dir_point->length += sizeof(fcb);
    return 0;
}

#endif
