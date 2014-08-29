#include<stdio.h>

int main()
{
    long long multi = 1000000000;
    int header[]={13,14,15,17,18};
    int i = 0;
    printf("Name, Phone Number\n");
    for (i = 0; i<5; i++)
    {
        long long num = header[i]*multi;
        long long next = (header[i]+1)*multi;
        while (num<next)
        {
            printf("\"%lld\",\"%lld\"\n",num,num);
            num++;
        }
    }
}
