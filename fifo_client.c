#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#define FIFO1_NAME "fifo1"
#define FIFO2_NAME "fifo2"

int main()
{
    char p[100],f[100],c[300];
    int num1,num2,f1,fd1,fd2;
    
    mknod(FIFO1_NAME,S_IFIFO|0666,0);
    mknod(FIFO2_NAME,S_IFIFO|0666,0);
    printf("Waiting for server !! \n\n");
    fd1=open(FIFO1_NAME,O_WRONLY);
    printf("file descriptor fd is %d \n\n",fd1);
    if(fd1<0)
    {
        printf("File open error ... \n");
        getchar();
        exit(1);
    }
    else
    printf("\n Server Online ... \n Client: Enter the path \n\n");
    scanf("%s",p);
    while(!feof(stdin))
    {
        if((num1=write(fd1,p,strlen(p)))==-1)
        perror("Write error...\n");
        else{
            printf("Waiting for reply ..\n");
            fd2=open(FIFO2_NAME,O_RDONLY);
            if((num2=read(fd2,c,300))==-1)
            perror("Transfer error ... \n");
            else
            {
                printf("File received!! \n displaying the contents .. !! \n\n");
                printf("%s",c);
                exit(1);
            }
        }
    }
}