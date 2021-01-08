//
// Created by 孙夏恩 on 2020/12/24.
//

#ifndef FILE_SYSTEM_DESIGN_FS_WRITE
#define FILE_SYSTEM_DESIGN_FS_WRITE

#include "fs.h"
#include "inode.h"
#include <string.h>
#include <stdio.h>
#include "c_operator.h"

int my_write(int fd,int mode){

    if(fd<0||fd>=MAX_OPEN_FILE){
        printf("[In my_write() mode 'w']:Illegal fd!\n");
        return -1;
    }
    // for(int kk=0;kk<MAX_OPEN_FILE;kk++){
    //     printf("openlist[%d]:openlabel=%d",kk,USEROPENS[kk].openlabel);
    // }
    if(USEROPENS[fd].openlabel==0){
        printf("[In my_write() mode 'w']:fd not inuse!\n");
        return -1;
    }
    USEROPENS[fd].inodestate=1;
    int id=USEROPENS[fd].direction_chart_id;
    int ori_length=USEROPENS[fd].length;
    int num_block_allocated=ori_length/BLOCK_SIZE;
    char * begin_addr=virtualDisk+BLOCK_SIZE*id;//Be Careful!

    if(mode==0){ //截断写
        printf("[mode:0] W\n");
        int init_blocknum=*((int *)(begin_addr+sizeof(int)));
        char *init_addr=virtualDisk+BLOCK_SIZE*init_blocknum;
        char str[BLOCK_SIZE*128]={'\0'};
        fflush(stdin);
        scanf("%[^\n]",str);
        /////
        //还未做异常处理
        /////
        getchar();
        int str_len=strlen(str);
        int STRLEN=str_len;
        char * cursor_addr=init_addr;
        int i=0;
        while(str_len/BLOCK_SIZE){
            memcpy(cursor_addr,str+BLOCK_SIZE*i,sizeof(char)*BLOCK_SIZE);
            printf("%d B write to fd %d\n",BLOCK_SIZE,fd);
            str_len=str_len-BLOCK_SIZE;
            if(str_len>0){//
                int new_blocknum=request_block();//申请
                *((int *)(begin_addr+(2*(i+1))*sizeof(int)))=i+1;//写到文件索引表 第一列
                *((int *)(begin_addr+(2*(i+1)+1)*sizeof(int)))=new_blocknum;//写到文件索引表 第二列
                i=i+1;
                if(new_blocknum==-1){
                    printf("[In my_write() mode 'w']:Try to allocate one block for writing, but failed!\n");
                    return -1;
                }
                cursor_addr=(char*)virtualDisk+BLOCK_SIZE*new_blocknum;   
                
            }
        }
        if(str_len>0){
            memcpy(cursor_addr,str+BLOCK_SIZE*i,sizeof(char)*str_len);
            printf("%d B write to fd %d\n",str_len,fd); 
        }
        USEROPENS[fd].length=STRLEN;//更新USEROPENS中长度
	           
    }else if(mode==1){//追加写
        printf("[mode:1] A\n");
        //t作用域
        int t=0;
        
        for(t=0;t<num_block_allocated;t++){
            int logic_num=*((int *)(begin_addr+2*t*sizeof(int)));
            printf("logic_block[%d]:%d ;",t,logic_num);
            int physics_blocknum=*((int *)(begin_addr+(2*t+1)*sizeof(int)));
            printf("physics_block[%d]:%d .\n",t,physics_blocknum);
        }
        //end t作用域
        
        //获取之前文件的盘块使用情况和last_pointer位置
        int last_pointer=0;
        if((last_pointer=ori_length%BLOCK_SIZE)==0){   
             printf("Already used blocks %d,last_pointer(in new):%d\n",t,last_pointer);
        }else{
            int logic_num=*((int *)(begin_addr+2*t*sizeof(int)));
            printf("logic_block[%d]:%d ;",t,logic_num);
            int physics_blocknum=*((int *)(begin_addr+(2*t+1)*sizeof(int)));
            printf("physics_block[%d]:%d .\n",t,physics_blocknum);
            printf("Already used blocks %d,last_pointer:%d\n",t+1,last_pointer); 
        }
        
        char str[BLOCK_SIZE*128]={'\0'};
        fflush(stdin);
        scanf("%[^\n]",str);
        getchar();
        int str_len=strlen(str);
        if(str_len==0){
            printf("Exit [In my_write() 'a']: Blank input. Return!\n");
            return -1;
        }
        //total_len作用开始，仅作check用
        int total_len=ori_length+str_len;
        if(total_len>128*BLOCK_SIZE){
            printf("Warning [In my_write() mode 'a']:OverFlow! Will Cut down the tail!\n");
            str_len=BLOCK_SIZE*128-ori_length;
        }
        //total_len作用结束，仅作check用
        
        

        int waiting_len=str_len;
        //t指到逻辑上最后一个盘块号
        int cnt;//cnt指到逻辑上下一盘块号（此时是未分配的，待命）
        char *init_addr=NULL;
        char *cursor_addr=NULL;
        
        //为init_addr和cursor_addr赋值
        if(last_pointer>0){
            cnt=num_block_allocated+1;//指到逻辑上下一盘块号（此时是未分配的，待命）
            int init_blocknum=*((int *)(begin_addr+(num_block_allocated*2+1)*sizeof(int)));
            // printf("resumefrom_blocknum:%d\n",init_blocknum);
            init_addr=virtualDisk+BLOCK_SIZE*init_blocknum;
            cursor_addr=init_addr;
        }else if(last_pointer==0){//文件写至前面盘块恰好用完
            
            cnt=num_block_allocated;//指到逻辑上下一盘块号（此时是未分配的，待命）
            if (t!=0)//特判空文件
            {
                //！此时的这个文件并非刚打开的空文件（逻辑盘块0肯定是已经分配好的了）
                //提前分一个新盘块
                int new_blocknum=request_block();//申请
                *(int *)(begin_addr+(2*cnt)*sizeof(int))=cnt;//写到文件索引表 第一列
                *(int *)(begin_addr+(2*cnt+1)*sizeof(int))=new_blocknum;//写到文件索引表 第二列
                cnt=cnt+1;
                init_addr=virtualDisk+BLOCK_SIZE*new_blocknum;
                cursor_addr=init_addr;
            }
        }else{
            printf("Error [In my_write() mode 'a']: lastpointer Error! Range of [0,+)!\n");
            return -1;
        }
        //为init_addr和cursor_addr赋值结束

        int str_cursor=0;
        int this_time_write_len=0;

        while((waiting_len+last_pointer)>BLOCK_SIZE){
            this_time_write_len=BLOCK_SIZE-last_pointer;
            cursor_addr=cursor_addr+last_pointer;
            memcpy(cursor_addr,str+str_cursor,this_time_write_len*sizeof(char));

            last_pointer=0;
            waiting_len=waiting_len-this_time_write_len;
            str_cursor=str_cursor+this_time_write_len;
            int new_blocknum=request_block();//申请
            *(int *)(begin_addr+(2*cnt)*sizeof(int))=cnt;//写到文件索引表 第一列
            *(int *)(begin_addr+(2*cnt+1)*sizeof(int))=new_blocknum;//写到文件索引表 第二列
            cnt=cnt+1;
            if(new_blocknum==-1){
                printf("Error [In my_write() mode 'a']:Try to allocate one block for writing, but failed!\n");
                return -1;
            }
            cursor_addr=virtualDisk+BLOCK_SIZE*new_blocknum;
        }
        //剩余
        memcpy(cursor_addr+last_pointer,str+str_cursor,waiting_len*sizeof(char));
        USEROPENS[fd].length+=str_len;//更新USEROPENS中长度
        printf("%d B added!",str_len);

    }else if(mode==2){//插入覆盖写
        int pos;
        printf("[mode:2] I Please input the insert position: ");
        scanf("%d",&pos);
        getchar();
        USEROPENS[fd].count=pos;
        int continue_b=USEROPENS[fd].count;//插入指针在总字节的位置 0开始
        if(continue_b+1>ori_length){
            printf("Error [In my_write() mode 'c']: Position of continue bytes error!\n");
            return -1;
        }
        char str[BLOCK_SIZE*128];
        scanf("%[^\n]",str);
        getchar();
        int str_len=strlen(str);
        int total_len=+continue_b;
        if(total_len>128*BLOCK_SIZE){
            printf("Warning [In my_write() mode 'c']:OverFlow! Will Cut down the tail!\n");
            str_len=BLOCK_SIZE*128-continue_b;
        }
        //此时的str_len为最终写入长度
        //此时的continue_b为最终写入开始位置
        int waiting_len=str_len;


    }else{
        return -1;
    }
   

}

#endif
