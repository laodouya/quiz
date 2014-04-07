#include<stdio.h>


long int f1(int n)
{
    if (0==n)
        return 0;
    else if(1==n)
        return 1;
    else 
        return f1(n-1)+f1(n-2);
}

long int f2(int n)
{
    long int data[10000];
    data[0]=0;
    data[1]=1;
    for (int i=2; i<=n; i++)
        data[i]=data[i-1]+data[i-2];
    return data[n];
}

int main()
{
    int num;
    scanf("%d",&num);
    long int ret;
    ret = f1(num);
    printf("%ld\n",ret);
    return 0;
}
