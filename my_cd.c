//
// Created by 孙鹏 on 2021/1/4.
//

#ifndef FILE_SYSTEM_DESIGN_CD
#define FILE_SYSTEM_DESIGN_CD

#include "fs.h"
#include "inode.h"
#include "inode_operator.c"
#include "group_link_operator.c"

void my_cd(char *dirname)
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
    if (i==(curr_dir_point->length/ sizeof(fcb)))
    {
        printf("%s Not exist\n",dirname);
        return;
    }
    curr_dir_inode = curr_dir_fcb->i_ino;
}


#endif