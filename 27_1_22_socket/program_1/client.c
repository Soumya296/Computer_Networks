#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
int main()
{
    struct sockaddr_in add;
    socklen_t addr_size;
    int sfd=socket(AF_INET,SOCK_STREAM,0);
    if(sfd==0)
    {
        printf("creation of socket failed\n");
    }
    add.sin_family=AF_INET;
    add.sin_port=htons(8080);
    add.sin_addr.s_addr=inet_addr("127.0.0.1");
    if(connect(sfd,(struct sockaddr *)&add,sizeof(add))<0)
    {
        printf("connection failed\n");
        return 0;
    }
    getsockname(sfd,(struct sockaddr *)&add,&addr_size);
    char ip[100];
    inet_ntop(AF_INET,&add.sin_addr,ip,sizeof(ip));
    printf("local ip : %s\n",ip);
    printf("local port %d \n",ntohs(add.sin_port));
    getpeername(sfd,(struct sockaddr*)&add,&addr_size);
    inet_ntop(AF_INET,&add.sin_addr,ip,sizeof(ip));
    printf("foreign ip : %s\n",ip);
    printf("foreign port %d \n",ntohs(add.sin_port));
    char msg[1024];
    char buf[1024];
    printf("Client : ");
    scanf("%s",msg);
    send(sfd,msg,sizeof(msg),0);
    close(sfd);
}