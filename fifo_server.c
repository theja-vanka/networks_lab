#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#define FIFO1_NAME "fifo1"
#define FIFO2_NAME "fifo2"

int main()
{
    char p[100],f[100],c[300],r,ch;
    int num1,num2,f1,fd1,fd2,i=0;

    mknod(FIFO1_NAME,S_IFIFO|0666,0);
    mknod(FIFO2_NAME,S_IFIFO|0666,0);

    printf("Server online !!!! \n");
    fd1=open(FIFO1_NAME,O_RDONLY);
    printf("Client Online !!! Waiting for request ...\n\n");

    while(1)
    {
        if((num1=read(fd1,p,100))==-1)
        perror("read error\n");
        else{
            p[num1]='\0';
            if((f1=open(p,O_RDONLY))<0)
            {
                printf("\n Server %s not found !!!\n",p);
                exit(1);
            }
            else
            {
                printf("Server %s found!!! \n Transferring contents ... \n",p);
                stdin=fdopen(f1,"r");
                while((ch=(char)getc(stdin))!=EOF)
                {
                    c[i]=ch;
                    i++;
                }
                c[i]='\0';
                fd2=open(FIFO2_NAME,O_WRONLY);
                printf("File content is server is \n %s \n",c);
                if((num2=write(fd2,c,strlen(c)))==-1)
                perror("Transfer error \n");
                else
                printf("Transfter completed .... \n");
                exit(1);
            }
        }
    }
}