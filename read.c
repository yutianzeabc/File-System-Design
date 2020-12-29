//
// Created by 孙夏恩 on 2020/12/29.
//
#include "common.h"
#include "fs.h"
#include "inode.h"
#include <string.h>
#include <stdio.h>
#include "group_link_operator.c"

int my_read(int fd,int len){
    
    int id=openlist[fd].direction_chart_id;
    int ori_length=openlist[fd].length;
    if(ori_length<len){
        printf("Error [In my_read()]: Read bytes error! Out of range!\n");
        return 0;
    }
    int num_block_allocated=openlist[fd].length/BLOCK_SIZE;
    int * begin_addr=virtualDisk+BLOCK_SIZE*id;


    
    

}