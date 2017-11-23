#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int min(int a, int b)
{
    return (a<b)?a:b;
}

void dist(int p[10][10],int n)
{
    int i,j,k;
    for(k=1;k<=n;k++)
    for(j=1;j<=n;j++)
    for(i=1;i<=n;i++)
    p[i][j]=min(p[i][j],p[i][k]+p[k][j]);
}

int main()
{
    int a[10][10],i,j,n,flag,temp=1;
    printf("Enter number of nodes:\n");
    scanf("%d",&n);
    printf("Enter the matrix 0 for self loop and 999 for no path \n");
    for(i=1;i<=n;i++)
    for(j=1;j<=n;j++)
    scanf("%d",&a[i][j]);
    for(i=1;i<=n;i++)
    {
        printf("Initial record of %d is\n",i);
        for(j=1;j<=n;j++)
        printf("%d to %d is %d \n",i,j,a[i][j]);
    }
    dist(a,n);

    for(i=1;i<=n;i++)
    {
        printf("Updated record of %d is \n",i);
        for(j=1;j<=n;j++)
        printf("%d to %d is %d\n",i,j,a[i][j]);
    }
    while(temp)
    {
        do{
            printf("Enter 0 to find shortest path and 1 to exit\n");
            scanf("%d",&flag);
            if(flag==0)
            {
                printf("Enter 2 nodes \n");
                scanf("%d%d",&i,&j);
                printf("%d to %d is %d\n",i,j,a[i][j]);
            }
            else
            temp=0;
            break;
        }while(flag!=0);
    }
    exit(0);
}