#include<stdio.h>
#include <string.h>
int main(){
    char a[9];
    scanf("%s",a);
    getchar();
    printf("%s\n",a);
    printf("%d\n",strlen(a));
    char b[9];
    char c[9];
    memcpy(c,a,9);
    printf("%c\n",c[10]);
    printf("%s\n",c);
    // int m[10]={9,8,7,6,5,4,3,2,1,0};
    // char *p=(char *)m;
    // printf("%p\n",p);
    // int *pp=(int *)(p+sizeof(int));
    // printf("%p\n",p);
    // printf("%d",*pp);
}