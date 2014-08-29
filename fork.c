#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
int main()
{
    int i = 0;
    if(fork()==0)
        execl("/bin/echo","echo","this is first execl forked by main",NULL);
    if(fork()==0)
        execl("/bin/echo","/bin/echo","this is second /bin/echo/execl forked by main",NULL);
    if(fork()==0)
    {
        int ret = execl("/bin/","echo","this is not work",NULL);
        if (ret<0)
        {
            perror("execl of third");
            //if not exit,this process will continue
            exit(1);
        }
    }

    //father is a endless loop
    while(1)
    {
        printf("%d\n",i++);
        sleep(1);
    }
    return 0;
}
