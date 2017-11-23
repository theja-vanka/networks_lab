#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<ctype.h>
#include<string.h>

long int e,d,n;
long int val[50];

char decode(long int ch)
{
    int i;
    long int temp=ch;
    for(i=1;i<d;i++)
    ch=temp*ch%n;
    return(ch);
}

int gcd(long a,long b)
{
    if(b==0)
    return(a);
    else
    return(gcd(b,a%b));
}

int prime(int a)
{
    int i;
    for(i=2;i<a;i++)
    {
        if((a%i)==0)
        return 0;
    }
    return 1;
}

int encode(char ch)
{
    int i;
    long int temp=ch;
    for(i=1;i<e;i++)
    temp=temp*ch%n;
    return temp;
}

int main()
{
    int i;
    long int p,q,phi,c[50];
    char text[50],ctext[50];
    printf("Enter text to be encoded: \n");
    scanf("%[^\n]",text);
    printf("%s\n",text);
    do{
        p=rand()%30;
    }while(!prime(p));
    do{
        q=rand()%30;
    }while(!prime(q));
    n=p*q;
    phi=(p-1)*(q-1);
    printf("\n p=%ld\t q=%ld\t n=%ld\t phi=%ld\n",p,q,n,phi);

    do{
        e=rand()%phi;
    }while(!gcd(e,phi));  
    do{
        d=rand()%phi;
    }while((d*e%phi)!=1); 

    printf("\n ***** Encoding Message *****\n");
    sleep(2);

    for(i=0;text[i]!='\0';i++)
    val[i]=encode(text[i]);
    val[i]=-999;

    printf("\n Encoded message is ..... \n");
    for(i=0;val[i]!=-999;i++)
    printf("%ld",val[i]);

    printf("\n ***** Decoding message ***** \n");
    sleep(2);

    for(i=0;val[i]!=-999;i++)
    ctext[i]=decode(val[i]);

    ctext[i]='\0';
    printf("\n Decoded message is ... \n");
    printf("%s\n",ctext); 
    return 1;
}