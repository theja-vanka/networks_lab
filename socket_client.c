// Server code

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> //include write function
#include<errno.h>
#include<string.h>
#include<sys/types.h> //Signed data type
//#include<sys/stat.h> 
#include<fcntl.h> //include the read function
#include<netinet/in.h> // contains constants and structure needed for internet domain address
#include<sys/socket.h> //include the number of definitions of structures needed for socket
#include<arpa/inet.h> //utility function prototype
#include<sys/wait.h>
#include<signal.h>

#define myport 6490

int main()
{
    int i=0,sockfd,len;
    char buf1[40],buf2[20000];
    FILE* fp;
    struct sockaddr_in their_addr;
    if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
    {
        perror("socket");
        exit(1);
    }
    their_addr.sin_family=AF_INET;
    their_addr.sin_port=htons(myport);
    their_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    memset(&(their_addr.sin_zero),'\0',8);
    if(connect(sockfd,(struct sockaddr*)&their_addr,sizeof(struct sockaddr))==-1)
    {
        perror("Connect");
        exit(1);
    }
    printf("Client is online ! \n");
    printf("Client: Enter the filename to be displayed :");
    scanf("%s",buf1);
    send(sockfd,buf1,sizeof(buf1),0);
    if(recv(sockfd,buf2,sizeof(buf2),0)==1)
    {
        perror("recv");
        exit(1);
    }
    else{
        printf("Display the contents of %s",buf1);
        printf(" \n %s \n",buf2);
    }
    close(sockfd);
    return 0;
}