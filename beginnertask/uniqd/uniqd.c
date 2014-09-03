//uniqd receive serial number and return none duplicate number
//listen port specified by argv

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#define MAX 1024

//convert str to number, if only number > = 0. 
//return -1 if str is invalid
int char_to_num(const char* str)
{
    int num = 0, single = 0;
    while (*str)
    {
        num *= 10;
        single = (int)*str - 48;
        if ((single < 0)||(single > 9))
            return -1;
        num += single;
        str++;
    }
    return num;
}

//insert new_data into data.
//n is the number of data.
//return 1 if insert success
//return 0 if data duplicated
//return -1 if insert failed
int unique_insert(int data[], int n, int new_data)
{
    if (n >= MAX)
        return -1;

    int start = 0, mid, end = n-1, i;
    while(start <= end)
    {
        mid = (start + end)/2;
        if (new_data == data[mid])
            return 0;
        else if (new_data < data[mid])
            end = mid - 1;
        else if (new_data > data[mid])
            start = mid + 1;
    }
    for (i = n; i > start; i--)
        data[i] = data[i-1];
    data[i] = new_data;
    return 1;
}

int get_port(int argc, char* argv[])
{
    //get port
    int port = 33333;
    switch (argc)
    {
        case 3:
            port = char_to_num(argv[2]);
            if (-1 == port)
            {
                printf("port invalid\n"); 
                return -1;
            }
            else if (port > 65535)
            {
                printf("port too large\n");
                return -1;
            }
            break;
        case 1:
            break;
        default:
            printf("Usage: uniqd -l port\n");
            return -1;
    }
    return port;
}

int init_socket(int port)
{
    //make socket
    int listenfd;
    struct sockaddr_in servaddr;

    if ((listenfd = socket(AF_INET,SOCK_STREAM, 0)) == -1)
    {
        printf("create scoket error: %s(errno: %d)\n", strerror(errno),errno);
        exit(0);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    
    if (bind(listenfd,(struct sockaddr*)&servaddr, sizeof(servaddr)) == -1)
    {
        printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }

    if (listen(listenfd, 10) == -1)
    {
        printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }
    
    printf("======waiting at port:%d for client's request======\n", port);
    return listenfd;
}


int infinite_loop(int listenfd)
{
    char buff[MAX];
    int data[MAX];
    char str[MAX];
    int len, n, i, j, ret, tmp;
    int connfd;

    while(1)
    {
        //recieving
        if ((connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) == -1)
        {
            printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
            continue;
        }
        len = recv(connfd, buff, MAX, 0);
        buff[len] = '\0';
        printf("recv msg from client: %s\n", buff);
        
        //processing
        n = 0;
        i = 0;
        j = 0;
        while (buff[i]!='\0')
        {
            if ('\n' == buff[i])
            {
                str[j] = '\0';
                tmp = char_to_num(str);
                if (tmp > -1)
                {
                    ret = unique_insert(data, n, tmp);
                    if (ret < 0)
                        printf("insert data failed\n");
                    else if (ret > 0)
                        n++;
                    else
                        ;//DO Nothing
                }
                else
                    printf("number invalid\n");
                j = 0;
                i++;
                continue;
            }
            str[j] = buff[i];
            j++;
            i++;
        }
        
        //sending
        memset(str, 0, sizeof(str));
        for (i = 0; i<n; i++)
        {
            sprintf(str, "%d\n", data[i]);
            if (-1 == send(connfd, str, strlen(str), 0))
                printf("send data failed\n");
        }

        close(connfd);
    }

    return 0;
}

int main(int argc, char* argv[])
{
    int port = get_port(argc, argv);
    if (-1 == port)
        return -1;

    int listenfd;
    listenfd = init_socket(port);

    infinite_loop(listenfd);
    
    close(listenfd);

    return 0;
}
