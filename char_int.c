#include<stdio.h>

int main()
{

    char array[16] ={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    char* cp = array;
    int* ip = (int*)array;
    printf("%d %d\n",sizeof(char),sizeof(int));
    printf("%c %d\n",*(cp+2),*(ip+2));
    return 0;
}
