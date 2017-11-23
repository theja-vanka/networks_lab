#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N strlen(g)
char t[128],cs[128],g[]="10001000000100001";
int a,e,c;

void xor()
{
    for(c=1;c<N;c++)
    cs[c]=((cs[c]==g[c])?'0':'1');
}

void crc()
{
    for(e=0;e<N;e++)
    cs[e]=t[e];
    do{
        if(cs[0]=='1')
        xor();
        for(c=0;c<N-1;c++)
        cs[c]=cs[c+1];
        cs[c]=t[e++];
    }while(e<=a+N-1);
}

int main()
{
    int flag=0;
    system("clear");
    printf("Enter the polynomial:\n");
    scanf("%s",t);
    printf("Generated divisor is %s\n",g);
    a=strlen(t);
    for(e=a;e<a+N-1;e++)
    t[e]='0';
    printf("Modified polynomial is %s\n",t);
    crc();
    printf("Checksum is %s\n",cs);
    for(e=a;e<a+N-1;e++)
    t[e]=cs[e-a];
    printf("Final codeword is %s\n",t);
    printf("Test error detection> \n 1(yes) 0(no):\n");
    scanf("%d",&flag);
    if(flag==0)
    return 1;
    if(flag==1)
    {
        printf("Enter position where error is to be inserted: \n");
        scanf("%d",&e);
        if(e<a+N-1)
        {
            t[e]=(t[e]=='0')?'1':'0';
            printf("err data : %s\n",t);
        }
        else
        printf("Position where error should be created is above the length of codework.. hence\n");
    }
    crc();
    for(e=0;(e<N-1)&&(cs[e]!='1');e++);
    if(e<N-1)
    printf("Error detected \n");
    else
    printf("No error detected\n");
    return 1;
}