//
// Created by 孙鹏 on 2020/12/23.
//

#ifndef FILE_SYSTEM_DESIGN_FORMAT
#define FILE_SYSTEM_DESIGN_FORMAT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fs.h"
#include "group_link_operator.c"
#include "inode_operator.c"
#include "my_ls.c"

void my_format()
{
    char *char_temp = NULL;
    int *int_temp = NULL;
    S_free = NULL;
    free_block_stack = (char *)malloc(BLOCK_SIZE);
    virtualDisk = (char *)malloc(SIZE);

    printf("----------Begin initial group link----------\n");
    S_free = free_block_stack;
    *S_free = 250;
    printf("%p %d\n",S_free,*S_free);
    S_free++;
    for (int i = 249; i >= 0; i--)
    {
        *S_free = i;
        printf("%p %d\n",S_free,*S_free);
        S_free++;
    }

    printf("\n\n");
    printf("%p\n",virtualDisk);
    /*initial No.249*/
    char_temp = virtualDisk + 249*BLOCK_SIZE;
    int_temp = char_temp;
    *int_temp = 250;
    printf("%p %d\n",int_temp,*int_temp);
    int_temp++;
    for (int i = 499; i>= 250; i--)
    {
        *int_temp = i;
        printf("%p %d\n",int_temp,*int_temp);
        int_temp++;
    }

    printf("\n\n");
    printf("%p\n",virtualDisk);
    /*initial No.499*/
    char_temp = virtualDisk + 499*BLOCK_SIZE;
    int_temp = char_temp;
    *int_temp = 250;
    printf("%p %d\n",int_temp,*int_temp);
    int_temp++;
    for (int i = 749; i>=500; i--)
    {
        *int_temp = i;
        printf("%p %d\n",int_temp,*int_temp);
        int_temp++;
    }

    printf("\n\n");
    printf("%p\n",virtualDisk);
    /*initial No.749*/
    char_temp = virtualDisk + 749*BLOCK_SIZE;
    int_temp = char_temp;
    *int_temp = 250;
    printf("%p %d\n",int_temp,*int_temp);
    int_temp++;
    for (int i = 999; i>=750; i--)
    {
        *int_temp = i;
        printf("%p %d\n",int_temp,*int_temp);
        int_temp++;
    }
    printf("----------End initial group link----------\n\n");

    int request_block0_id;
    int super_block_id;
    int inode_table_id;
    int inode_table_id2;
    int root_id;

    request_block0_id = request_block();    //No.0 distribute to block0
    printf("No.%d distribute to block0\n",request_block0_id);
    super_block_id = request_block();       //N0.1 distribute to super_block
    printf("N0.%d distribute to super_block\n",super_block_id);
    inode_table_id = request_block();       //No.2 distribute to inode_table
    inode_table_id2 = request_block();      //No.3 distribute to inode_table
    printf("No.%d distribute to inode_table\n",inode_table_id);
    printf("No.%d distribute to inode_table\n",inode_table_id2);
    root_id = request_block();              //No.4 distribute to root_dir
    printf("No.%d distribute to root_dir\n\n",root_id);

    block0 block0_temp;
    block0 *block0_point = NULL;
    block0_temp.block_size = BLOCK_SIZE;
    block0_temp.block_num = SIZE/BLOCK_SIZE;
    block0_temp.root = root_id;
    block0_temp.super_block = super_block_id;
    block0_temp.inode_table = inode_table_id;
    block0_temp.root_start = virtualDisk + root_id*BLOCK_SIZE;
    block0_temp.super_start = virtualDisk + super_block_id*BLOCK_SIZE;
    block0_temp.inode_table_start = virtualDisk + inode_table_id*BLOCK_SIZE;
    block0_temp.data_start = virtualDisk + (root_id+1)*BLOCK_SIZE;
    memcpy(virtualDisk, &block0_temp, sizeof(block0));
    block0_point = virtualDisk;
    printf("block0.block_size is %d\n",block0_point->block_size);
    printf("block0.block_num is %d\n",block0_point->block_num);
    printf("block0.super_block is %d\n",block0_point->super_block);
    printf("block0.inode_table is %d\n",block0_point->inode_table);
    printf("block0.root is %d\n",block0_point->root);
    printf("block0.super_start is %p\n",block0_point->super_start);
    printf("block0.inode_table_start is %p\n",block0_point->inode_table_start);
    printf("block0.root_start is %p\n",block0_point->root_start);
    printf("block0.data_start is %p\n\n",block0_point->data_start);

    int root_dir_inode;
    int root_dir_index_label;
    inode *root_dir_inode_point;
    root_dir_inode = create_inode();
    root_dir_index_label = request_block();
    printf("the id of Root_dir's inode is %d\n",root_dir_inode);
    printf("Request No.%d block as root_dir's index_label\n",root_dir_index_label);
    root_dir_inode_point = get_inode_point(root_dir_inode);
    root_dir_inode_point->direction_chart_id = root_dir_index_label;
    root_dir_inode_point->attribute = 1;
    root_dir_inode_point->length = 0;

    index_element *index_label_start;
    index_label_start = virtualDisk + root_dir_index_label*BLOCK_SIZE;
    index_label_start->logical_id = 0;
    index_label_start->physical_id = root_id;

    curr_dir_inode = root_dir_inode;
    fcb *fcb_temp;
    char *fname1 = ".";
    char *fname2 = "..";
    fcb_temp = virtualDisk + root_id*BLOCK_SIZE;
    memcpy(fcb_temp->filename, fname1, sizeof(char));
    fcb_temp->i_ino = root_dir_inode;
    fcb_temp++;
    memcpy(fcb_temp->filename, fname2, sizeof(char)*2);
    fcb_temp->i_ino = root_dir_inode;
    root_dir_inode_point->length = sizeof(fcb)*2;
    printf("Root_dir_inode's i_ino is %d\n",root_dir_inode_point->i_ino);
    printf("Root_dir_inode's attribute is %d\n",root_dir_inode_point->attribute);
    printf("Root_dir_inode's time is %lu\n",root_dir_inode_point->time);
    printf("Root_dir_inode's date is %lu\n",root_dir_inode_point->date);
    printf("Root_dir_inode's length is %lu\n",root_dir_inode_point->length);
    printf("Root_dir_inode's direction_chart_id is %d\n\n",root_dir_inode_point->direction_chart_id);

    printf("logical_id  physical_id\n");
    printf("%-8d     %-8d\n\n",index_label_start->logical_id,index_label_start->physical_id);

    my_ls();
    char *text = "root_dir";
    memcpy(USEROPENS[0].filename, text, sizeof(char)*strlen(text));
    USEROPENS[0].time = root_dir_inode_point->time;
    USEROPENS[0].date = root_dir_inode_point->date;
    USEROPENS[0].attribute = root_dir_inode_point->attribute;
    USEROPENS[0].direction_chart_id = root_dir_inode_point->direction_chart_id;
    USEROPENS[0].openlabel = 1;
    USEROPENS[0].length = root_dir_inode_point->length;
    printf("\n%s is opened\n\n",USEROPENS[0].filename);

}

#endif
