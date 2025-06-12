#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

int main()
{
 int sockfd;
 struct sockaddr_in server_addr;
 socklen_t addrsz;
 char buffer[1024],buff2[102];
 sockfd = socket(AF_INET,SOCK_DGRAM,0);
 if(sockfd==-1)
{
 perror("socket cre failed");
 exit(1);
}
 printf("SOCKET CREATED SUCCESSFULLY\n");
 server_addr.sin_family = AF_INET;
 server_addr.sin_port = htons(5000);
 server_addr.sin_addr.s_addr = INADDR_ANY;

addrsz = sizeof(server_addr);
bzero(buffer,1024);
printf("ENTER A MSG TO SERVER\n");
fgets(buffer,1024,stdin);
addrsz = sizeof(server_addr);
sendto(sockfd,buffer,1024,0,(struct sockaddr *)&server_addr,addrsz);
recvfrom(sockfd,buff2,102,0,(struct sockaddr *)&server_addr,&addrsz);
printf("%s",buff2);
close(sockfd);

}