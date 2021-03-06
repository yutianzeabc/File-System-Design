//
// Created by 孙鹏 on 2021/1/4.
//

#ifndef FILE_SYSTEM_DESIGN_CD
#define FILE_SYSTEM_DESIGN_CD

#include "fs.h"
#include "inode.h"
#include "c_operator.h"
#include <stdio.h>
#include <string.h>

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
              inode *temp;
              temp = get_inode_point(curr_dir_fcb->i_ino);
              if(temp->attribute==1)
                  break;
          }
          curr_dir_fcb++;
    } //遍历当前目录，找到文件名匹配且文件属性为1
    if (i==(curr_dir_point->length/ sizeof(fcb)))
    {
        printf("\n%s Not exist\n",dirname);
        return;
    }
    curr_dir_inode = curr_dir_fcb->i_ino;
}

#endif
