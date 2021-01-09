//
// Created by 滕雨轩 on 2020/12/26.
//

#ifndef FILE_SYSTEM_DESIGN_FS_START_EXIT
#define FILE_SYSTEM_DESIGN_FS_START_EXIT

#include "fs.h"
#include "inode.h"
#include "c_operator.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int start_sys()
{
    FILE *fpoint = fopen("./store_file_system", "r");
    if(fpoint == NULL)
    {
        printf("Call my_format()\n");
        my_format();
    }
    else     //文件存在的情况
    {
        free_block_stack = (char *)malloc(BLOCK_SIZE);
        virtualDisk = (char *)malloc(SIZE);

        size_t count = 0;
        count = fread(virtualDisk, sizeof(char), SIZE, fpoint);
        printf("%lu Bytes successfully read\n",count);

        memcpy(free_block_stack, virtualDisk+1*BLOCK_SIZE, sizeof(char)*BLOCK_SIZE);
        printf("\nFree Block Stack situation\n");
        S_free = free_block_stack;
        printf("%p %d\n",S_free,*S_free);
        int number = *S_free;
        S_free++;

        for (int i = 0; i < number; ++i)
        {
            printf("%p %d\n",S_free,*S_free);
            S_free++;
        }

        int *temp = virtualDisk + 2*BLOCK_SIZE;
        temp--;
        inode_id = *temp;
        printf("inode_id is %d\n",inode_id);

        curr_dir_inode = 0;

        for (int i=0; i<10; i++)
        {
            USEROPENS[i].openlabel = 0;
        }
    }
    return 0;
}

int exit_sys()
{
    for (int i = 0; i < MAX_OPEN_FILE; ++i)
    {
        if (USEROPENS[i].openlabel==1)
                my_close(i);
    }
    printf("\nFree Block Stack situation\n");
    S_free = free_block_stack;
    printf("%p %d\n",S_free,*S_free);
    int number = *S_free;
    S_free++;

    for (int i = 0; i < number; ++i)
    {
        printf("%p %d\n",S_free,*S_free);
        S_free++;
    }

    printf("Write free_block_stack into Super_block\n");
    memcpy(virtualDisk+1*BLOCK_SIZE, free_block_stack, sizeof(char)*BLOCK_SIZE);

    int *temp = virtualDisk + 2*BLOCK_SIZE;
    temp--;
    *temp = inode_id;
    printf("inode_id is %d\n",inode_id);

    FILE *fpoint = NULL;
    fpoint = fopen("./store_file_system", "wb+");

    size_t count = 0;
    count = fwrite(virtualDisk, sizeof(char), SIZE, fpoint);

    free(free_block_stack);
    free(virtualDisk);
    printf("%lu Bytes successfully write\n",count);
    printf("File system successfully exit!!!!\n");
    return 0;
}

#endif
