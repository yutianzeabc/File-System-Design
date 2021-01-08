//
// Created by 孙夏恩 on 2020/12/29.
//

#ifndef FILE_SYSTEM_DESIGN_FS_READ
#define FILE_SYSTEM_DESIGN_FS_READ

#include "common.h"
#include "fs.h"
#include "inode.h"
#include <string.h>
#include <stdio.h>
#include "c_operator.h"

int my_read(int fd,int len)
{
    if(fd<0||fd>=MAX_OPEN_FILE||USEROPENS[fd].openlabel==0){
        printf("[In my_read()]:Illegal fd!\n");
        return -1;
    }
    char str_buff[BLOCK_SIZE*130];//建立读出缓冲区
    int id=USEROPENS[fd].direction_chart_id;
    int ori_length=USEROPENS[fd].length;
    if(ori_length<len){
        printf("Error [In my_read()]: Read bytes error! Out of range!\n");
        return -1;
    }else if(ori_length<0){
        printf("Error [In my_read()]: Read bytes error! Illegal Range!\n");
        return -1;
    }
    int num_block_allocated=ori_length/BLOCK_SIZE;
    printf("num_block_allocated: %d,id:%d\n",num_block_allocated,id);
    int* begin_addr=(int *)(virtualDisk+BLOCK_SIZE*id);
    int i=0;//逻辑盘块号，从0开始记录

    int already_copy=0;
    int pysic_num;
    char* pysic_addr;
    while(len/BLOCK_SIZE){
        printf("pysic_num?\n");
        pysic_num=*(begin_addr+(2*i+1));
        printf("pysic_num:%d\n",pysic_num);
        pysic_addr=virtualDisk+BLOCK_SIZE*pysic_num;
        memcpy(str_buff+already_copy,pysic_addr,BLOCK_SIZE);
        len=len-BLOCK_SIZE;
        already_copy=already_copy+BLOCK_SIZE;
    }
    printf("pysic_num?\n");
    pysic_num=*(begin_addr+(2*i+1));
    printf("pysic_num:%d\n",pysic_num);
    pysic_addr=virtualDisk+BLOCK_SIZE*pysic_num;
    memcpy(str_buff+already_copy,pysic_addr,len);
    already_copy=already_copy+len;
    printf("%d B read! Finish!\n",already_copy);
    str_buff[already_copy]='\0';
    printf("%s\n",str_buff);
    return 0;

}

#endif
