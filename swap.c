#include <stdio.h>

void swap1(int a, int b)
{
    int temp=a;
    a=b;
    b=temp;
}
void swap2(int *a, int *b)
{
    *a=*a+*b-(*b=*a);
}
void swap3(int& a, int& b)
{
    a^=b^=a^=b;
}


int main()
{
    int a=1,b=2;
    swap1(a,b);
    printf("swap1(a,b) %d, %d\n",a,b);
   
    a=1,b=2;
    swap2(&a,&b);
    printf("swap2(&a,&b) %d, %d\n",a,b);

    a=1,b=2;
    swap3(a,b);
    printf("swap3(a,b) %d, %d\n",a,b);

    return 0;
}
