//
// Created by 孙鹏 on 2020/12/22.
//

#ifndef FILE_SYSTEM_DESIGN_FS_H
#define FILE_SYSTEM_DESIGN_FS_H

#endif //FILE_SYSTEM_DESIGN_FS_H

#define BLOCK_SIZE 1024      //1KB
#define SIZE 1024000         //1000KB
#define BLOCK0_NUM 2         //引导块初始占1个盘块
#define ROOT_BLOCK_NUM 2     //根目录初始占2个盘块
#define INODE_TABLE_NUM 2    //索引节点共占2个盘块
#define SUPER_BLOCK_NUM 1    //超级块共占1个盘块
#define MAX_OPEN_FILE 10     //最多同时打开文件个数

typedef struct BLOCK0
{
    int block_size;          //磁盘块大小
    int block_num;           //磁盘块数量
    int root;                //根目录的起始盘块号
    char *inode_table_start; //虚拟磁盘上索引节点开始位置
    char *root_start;        //虚拟磁盘上根目录开始位置
    char *data_start;        //虚拟磁盘上数据区开始位置
    char *super_start;       //虚拟磁盘上超级快开始位置
    char information[200];   //描述信息
}block0;

typedef struct USEROPEN
{
    char filename[20];
    int attribute;
    int access;
    unsigned short time;
    unsigned short date;
    unsigned long length;
    char dir[80];             //文件打开路径
    int count;                //读写指针位置
    int inodestate;          //索引节点是否修改
    int openlabel;           //系统打开文件表表项是否被占用
}useropen;