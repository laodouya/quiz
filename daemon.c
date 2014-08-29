#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<signal.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include <sys/stat.h>
#define MAXFILE 65535
void sigterm_handler(int arg);
volatile sig_atomic_t _running = 1;
void make_it_daemon()
{
    pid_t pid;
    int i,len;
    pid = fork(); //第一步
    if(pid<0){
        printf("error fork\n");
        exit(1);
    }
    else if(pid>0)
        exit(0);  //kill father

    pid = setsid(); //第二步
    if (pid < 0)
        perror("setsid error");

    pid = fork(); //第三步
    if(pid<0){
        printf("error fork\n");
        exit(1);
    }
    else if(pid>0)
        exit(0);  //kill father

    for(i=0;i<MAXFILE;i++) //第四步
        close(i);

    chdir("/"); //第五步
    umask(0); //第六步

    signal(SIGCHLD,SIG_IGN); //第七步

    signal(SIGTERM, sigterm_handler); //第八步
}

int main(int argc, char* argv[])
{
    if (argc<3)
    {
        printf("Usage: daemon program_full_path parameter\n");
        return 1;
    }
    
    make_it_daemon();
    
    int status;
    pid_t pid;
    
    while( _running )
    {
        pid = fork();
        if (pid<0)
        {
            printf("error fork");
            exit(1);
        }
        else if (0==pid)
        {
            int ret = execl(argv[1],argv[1],argv[2],NULL);
            if (ret<0)
                perror("execl");
            exit(1);
        }

        waitpid(pid,&status,0);

    } 
    return 0; 
} 
void sigterm_handler(int arg) 
{ 
    _running = 0; 
}
