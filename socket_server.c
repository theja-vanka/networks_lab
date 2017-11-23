// Server code

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> //include write function
#include<errno.h>
#include<string.h>
#include<sys/types.h> //Signed data type
#include<sys/stat.h> 
#include<fcntl.h> //include the read function
#include<netinet/in.h> // contains constants and structure needed for internet domain address
#include<sys/socket.h> //include the number of definitions of structures needed for socket
#include<arpa/inet.h> //utility function prototype
#include<sys/wait.h>
#include<signal.h>

#define myport 6490
#define BACKLOG 10

int main()
{
    int sockfd,fp,new_fd;
    struct sockaddr_in my_addr,their_addr;
    int sin_size,i=0;
    int yes=1;
    char buf1[20], buf2[2000];
    if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
    {
        perror("Socket");
        exit(1);
    }
    if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int))==-1)
    {
        perror("Set sockopt");
        exit(1);
    }
    my_addr.sin_family=AF_INET;
    my_addr.sin_port=htons(myport);
    my_addr.sin_addr.s_addr=INADDR_ANY;
    memset(&(my_addr.sin_zero),'\0',8); //memset - fill memory with the constant bite. returns a pointer to a memory address.
    if(bind(sockfd,(struct sockaddr*)&my_addr,sizeof(struct sockaddr))==-1)
    {
        perror("Bind");
        exit(1);
    }
    if(listen(sockfd,BACKLOG)==-1)
    {
        perror("Listen");
        exit(1);
    }
    printf("\n Server is online; waiting for the client");
    sin_size=sizeof(struct sockaddr_in);
    if((new_fd=accept(sockfd,(struct sockaddr *)&their_addr,&sin_size))==-1)
    {
        perror("Accept");
        exit(0);
    }
    printf("Got connection %s \n",inet_ntoa(their_addr.sin_addr));
    recv(new_fd,&buf1,sizeof(buf1),0);
    printf("File requested is %s \n",buf1);
    if((fp=open(buf1,O_RDONLY))<0)
    {
        printf("File not found");
        strcpy(buf2,"File no found");
    }
    else
    {
        printf(" %s found & ready to transfer \n",buf1);
        read(fp,&buf2,20000);
        close(fp);
    }
    send(new_fd,&buf2,sizeof(buf2),0);
    close(new_fd);
    close(sockfd);
    printf("Transaction Success \n");
    printf("\n");
    return 0;
}