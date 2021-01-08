//
// Created by 孙鹏 on 2020/12/27.
//

#ifndef FILE_SYSTEM_DESIGN_FS_LS
#define FILE_SYSTEM_DESIGN_FS_LS

#include "fs.h"
#include "inode.h"
#include "c_operator.h"
#include <stdio.h>

void my_ls()
{
    inode *inode_temp;
    inode_temp = get_inode_point(curr_dir_inode);
    
    int index_temp;
    index_temp = inode_temp->direction_chart_id;
    
    index_element *element_temp;
    element_temp = virtualDisk + index_temp* BLOCK_SIZE;
    
    int physical;
    physical = element_temp->physical_id;
    
    fcb *fcb_temp;
    fcb_temp = virtualDisk + physical*BLOCK_SIZE;

    printf("\nfilename  i_ino\n");
    for (int i = 0; i < inode_temp->length/sizeof(fcb); ++i)
    {
        printf("%-8s   %-8lu\n",fcb_temp->filename,fcb_temp->i_ino);
        fcb_temp++;
    }
    printf("\n");
}

#endif
