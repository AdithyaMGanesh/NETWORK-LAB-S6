#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>

int main()
{
 int sock_fd,cl_fd;
 struct sockaddr_in server_addr,clie_addr;
 socklen_t addrsz;
 char buff[1024];
 sock_fd = socket(AF_INET,SOCK_STREAM,0);
 if(sock_fd == -1)
{
 perror("SOCKET CREATION FAILED");
 exit(1);
}
printf("SOCKET CREATED SUCCESSFULLY\n");

server_addr.sin_family = AF_INET;
server_addr.sin_port =htons(4950);
server_addr.sin_addr.s_addr = INADDR_ANY;

if(bind(sock_fd,(struct sockaddr*)&server_addr,sizeof(server_addr))==-1)
{
perror("binding error");
 exit(1);
}
if((listen(sock_fd,6))==-1)
{
perror("listening error");
exit(1);
}
printf("listening to client\n");
addrsz = sizeof(clie_addr);
cl_fd = accept(sock_fd,(struct sockaddr*)&clie_addr,&addrsz);
if(cl_fd == -1)
{
perror("connection error");
exit(1);
}
printf("client connected\n");
bzero(buff,1024);
recv(cl_fd,buff,sizeof(buff),0);
printf("client : %s\n",buff);
close(cl_fd);
}




