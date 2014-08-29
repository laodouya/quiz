//Read file while words splited by \0

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int splitNameParameter(char* cmdline, char* name, char* parameter)
{
    while ((*name++ = *cmdline++)!=' ');
    name--;
    *name = '\0';
    strcpy(parameter, cmdline);
    return 0;    
}

int main()
{
    char* test = (char*)malloc(3000);
    int i = 0;
    FILE* fd_CmdLineFile = fopen ("cmdline", "rt");
    while ((test[i] = fgetc(fd_CmdLineFile))!=EOF)
    {
        if (0 == test[i])
            test[i] = ' ';
        i++;
    }
    i--;
    test[i] = 0;

    char name[1000];
    char parameter[2000];
    splitNameParameter(test, name, parameter); 
    printf("%s|\n%s|\n",name,parameter);
    return 0;
}
