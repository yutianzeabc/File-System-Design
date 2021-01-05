//
// Created by 马钵涛 on .
//

#include "fs.h"
#include "inode.h"
#include "inode_operator.c"
#include "group_link_operator.c"

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
    }

    if (i < curr_dir_point->length / sizeof(fcb)){
        printf("/n%s is already exist/n ", filename);
        return -1;
    }
    return 0;
}

    







}