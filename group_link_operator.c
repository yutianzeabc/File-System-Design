//
// Created by 孙鹏 on 2020/12/23.
//

#ifndef FILE_SYSTEM_DESIGN_FS_GROUP_LINK_OPERATOR
#define FILE_SYSTEM_DESIGN_FS_GROUP_LINK_OPERATOR

#include <string.h>
#include "fs.h"

int request_block()
{
    int *temp = free_block_stack;
    int count = *temp;
    int result;
    S_free--;
    result = *S_free;
    if (count > 1)
    {
        count--;
        *temp = count;
        return result;
    }
    else if (count==1)
    {
        if(result == 999)
        {
            return -1;
        }
        else
        {
            memcpy(free_block_stack, virtualDisk+result*1024, sizeof(char)*1024);
            temp = free_block_stack;
            count = *temp;
            S_free = temp + count + 1;
            return result;
        }
    }
}

void recycle_block(int id)
{
    int *temp = free_block_stack;
    int count = *temp;
    if (count<250)
    {
        *S_free = id;
        count++;
        S_free++;
        *temp = count;
    }
    else if (count==250)
    {
        memcpy(virtualDisk+id*1024, free_block_stack, sizeof(char)*1024);
        S_free = free_block_stack;
        *S_free = 1;
        S_free++;
        *S_free = id;
        S_free++;
    }
}
#endif
/*

int request_block()
{
    int *temp = free_block_stack;
    int count = *temp;
    int result;
    S_free--;
    result = *S_free;
    if (count > 1)
    {
        count--;
        *temp = count;
        return result;
    }
    else if (count==1)
    {
        if(result == 999)
        {
            return -1;
        }
        else
        {
            memcpy(free_block_stack, virtualDisk+result*1024, sizeof(char)*1024);
            temp = free_block_stack;
            count = *temp;
            S_free = temp + count + 1;
            return result;
        }
    }
}

void recycle_block(int id)
{
    int *temp = free_block_stack;
    int count = *temp;
    if (count<250)
    {
        *S_free = id;
        count++;
        S_free++;
        *temp = count;
    }
    else if (count==250)
    {
        memcpy(virtualDisk+id*1024, free_block_stack, sizeof(char)*1024);
        S_free = free_block_stack;
        *S_free = 1;
        S_free++;
        *S_free = id;
        S_free++;
    }
}

 */