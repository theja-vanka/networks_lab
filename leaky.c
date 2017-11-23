#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
struct frame
{
    char msg[20];
    int seq;
}fr[40];
int fno,front=0,rear=-1,count=0;
char q[10][20];

void insert(int i)
{
    if(count == 3)
    {
        printf("Bucket is full ... \n");
        printf("\n Packet loss is %s\n",fr[i].msg);
        sleep(3);
    }
    else
    {
        rear=(rear+1)%3;
        strcpy(q[rear],fr[i].msg);
        count++;
        printf("\n Inserted packet into the bucket is %s\n",fr[i].msg);
        sleep(5);
    }
}

void transmitted()
{
    if(count==0)
    {
        printf("\n\n Bucket is empty\n");
        return;
    }
    printf("\n\n Transmitted packet is %s\n",q[front]);
    sleep(5);
    front=(front+1)%3;
    count--;
}

int main()
{
    int i,j,k,arrival[40],clk=20,n;
    char str[100];
    printf("Enter the message\n");
    scanf("%[^\n]",str);
    for(i=0;str[i]!='\0';)
    {
        fr[fno].seq=fno;
        for(j=i,k=0;str[j]!='\0'&&k<5;j++,k++)
        fr[fno].msg[k]=str[j];
        fr[fno].msg[k]='\0';
        fno++;
        i=j;
    }
    printf("Show the packets \n");
    for(i=0;i<fno;i++)
        printf("\n Packet %d is : %s\n",i,fr[i].msg);
    sleep(5);
    for(i=0;i<fno;i++)
    {
        n=random()%3;
        arrival[i]=arrival[i-1]+n;
    }
    printf("Arrival time of packets is .... \n");
    for(i=0;i<fno;i++)
    printf("Packet %d %s : %d\n",i,fr[i].msg,arrival[i]);
    printf("Size of bucket is 3 \n\n");
    sleep(5);
    i=0;
    while(i<fno || count!=0)
    {
        printf("CLK::%d\n",clk);
        while(clk==arrival[i])
        {
            insert(i);
            i++;
        }
        if((clk%5)==0)
        transmitted();
        clk++;
    }
}