#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<string.h>

int main()
{
    char *data;
    char tmp[64];
    printf("Content-Type:text/html;charset=gb2312\n\n");
    data = getenv("QUERY_STRING");
    if(NULL == data)
        printf("No data input");
    else if (0 == strcmp(data,"Date"))
    {
        time_t t = time(NULL);
        memset(tmp, 0, sizeof(tmp));
        strftime(tmp, sizeof(tmp), "%Y/%m/%d", localtime(&t));
        printf("%s",tmp);
    }
    else
        printf("Command not recognized");
    return 0;
}

