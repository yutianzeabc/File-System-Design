#include "fs.h"
#include "inode.h"
#include "inode_operator.c"

int my_open(char *filename)
{
    inode *curr_dir_point = NULL;
    curr_dir_point = get_inode_point(curr_dir_inode);

    int curr_dir_index;
    curr_dir_index = curr_dir_point->direction_chart_id;

    index_element *curr_dir_index_start = NULL;
    curr_dir_index_start = virtualDisk + curr_dir_index * BLOCK_SIZE;

    fcb *curr_dir_fcb = NULL;
    curr_dir_fcb = virtualDisk + curr_dir_index_start->physical_id * BLOCK_SIZE;

    int i = 0;
    for (i = 0; i < curr_dir_point->length / sizeof(fcb); ++i)
    {
        if (strcmp(filename, curr_dir_fcb->filename) == 0)
        {
            int j = 0;
            for (int j = 0; j < 10; j++)
            {
                if (USEROPENS[i].openlabel == 0)
                {
                    break;
                }
            }
            if (j == 10)
            {
                printf("[In my_open()]:The Number of open files reached the limit!\n");
                return -1;
            }

            inode *target_file_inode = get_inode_point(curr_dir_fcb->i_ino);
            //初始化USEROPEN
            memcpy(USEROPENS[j].filename, filename, sizeof(char) * 20);
            USEROPENS[j].inode_id = curr_dir_fcb->i_ino;
            USEROPENS[j].attribute = target_file_inode->attribute;
            USEROPENS[j].access = target_file_inode->access;
            USEROPENS[j].time = target_file_inode->time;
            USEROPENS[j].date = target_file_inode->date;
            USEROPENS[j].length = target_file_inode->length;
            //memcpy(USEROPENS[j].dir, curr_dir_name);
            USEROPENS[j].direction_chart_id = target_file_inode->direction_chart_id;
            USEROPENS[j].count = 0;
            USEROPENS[j].inodestate = 0; //索引节点打开时设置为未修改
            USEROPENS[j].openlabel = 1;
            printf("Open %s with fd %d.\n", filename, j);
            return j;
        }
        curr_dir_fcb++;
    }

    printf("[In my_open()]:No such file!\n");
    return -2;
}

int my_close(int fd)
{
    if ((fd < 0) || (fd > 9))
    {
        printf("[In my_close()]:Illegal fd!\n");
        return -1;
    }
    if (USEROPENS[fd].openlabel == 0)
    {
        printf("[In my_close()]:fd not in use!\n");
        return -2;
    }

    if (USEROPENS[fd].inodestate == 0)
    {
        USEROPENS[fd].openlabel = 0;
        printf("Close %s with fd %d (Not Modified).\n", USEROPENS[fd].filename, fd);
        return 0;
    }
    else
    {
        inode *target_file_inode = get_inode_point(USEROPENS[fd].inode_id);
        // 更新INODE
        target_file_inode->attribute = USEROPENS[fd].attribute;
        target_file_inode->access = USEROPENS[fd].access;
        target_file_inode->time = USEROPENS[fd].time;
        target_file_inode->date = USEROPENS[fd].date;
        target_file_inode->length = USEROPENS[fd].length;

        USEROPENS[fd].openlabel = 0;
        printf("Close %s with fd %d (Modified).\n", USEROPENS[fd].filename, fd);
        return 1;
    }
}