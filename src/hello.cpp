#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
//接受文件函数
void* myserver(void* param)
{
    int ret;
    int sk, ask;
    char buf[1024];
    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(1234);
    sk = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sk)
    {
	printf("socket create error!\n");
	return (void*)1;
    }
    else
    {
	printf("socket created: %d\n", sk);
    }
    ret = bind(sk, (sockaddr*)&addr, sizeof(addr));
    if (-1 == ret)
    {
	printf("bind error!\n");
	return (void*)2;
    }
    else
    {
	printf("socket bind!\n");
    }
    ret = listen(sk, 10);
    if (-1 == ret)
    {
	printf("listen error!\n");
	return (void*)3;
    }
    else
    {
	printf("socket listen!\n");
    }
    ask = accept(sk, 0, 0);
    if (-1 == ask)
    {
	printf("accept error!\n");
	return (void*)4;
    }
    else
    {
	printf("socket accept!\n");
    }
    while(1)
    {
	recv(ask, buf, 1024, 0);
	printf("recv: %s", buf);
	printf("\nplease reply: ");
	memset(buf, 0, 1024);
	scanf("%s", buf);
	send(ask, buf, 1024, 0);	
    }
    return 0;
}
int main()
{
pthread_t pid;
pthread_create(&pid, 0,  myserver,  0);
pthread_join(pid, NULL);
return 0;
}
