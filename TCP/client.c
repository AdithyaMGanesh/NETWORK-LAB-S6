#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>

int main()
{
 int fd;
 struct sockaddr_in server_addr;
 char buff[1024];
 fd = socket(AF_INET,SOCK_STREAM,0);
 if(fd == -1)
{
 perror("SOCKET CREATION FAILED");
 exit(1);
}
printf("SOCKET CREATED SUCCESSFULLY\n");

server_addr.sin_family = AF_INET;
server_addr.sin_port =htons(4950);
server_addr.sin_addr.s_addr = INADDR_ANY;

int status = connect(fd,(struct sockaddr*)&server_addr,sizeof(server_addr));
if(status == -1)
{
perror("connection error");
exit(1);
}
printf("client connected\n");
bzero(buff,1024);
printf("ENTER A MSG TO SERVER\n");
fgets(buff,1024,stdin);
send(fd,buff,sizeof(buff),0);
close(fd);
}




