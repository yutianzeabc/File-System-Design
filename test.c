//
// Created by 孙鹏 on 2020/12/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "inode.h"
#include "fs.h"

char *free_block_stack;
char *virtualDisk;
int *S_free;

void my_format()
{
    char *char_temp = NULL;
    int *int_temp = NULL;
    S_free = NULL;
    free_block_stack = (char *)malloc(BLOCK_SIZE);
    virtualDisk = (char *)malloc(SIZE);

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
}

int main()
{
    my_format();
    printf("%p\n",virtualDisk);
    printf("%p\n",S_free);
    free(virtualDisk);
    free(free_block_stack);
    return 0;
}
