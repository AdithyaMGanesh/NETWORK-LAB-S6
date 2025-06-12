#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/time.h>
#include<time.h>
int main()
{
 int sockfd;
 struct sockaddr_in server_addr;
 socklen_t addrsz;
 char buffer[1024];
 char msg[1024] ="PLS SEND TIME...\n";
 sockfd = socket(AF_INET,SOCK_DGRAM,0);
 if(sockfd==-1)
{
 perror("socket cre failed");
 exit(1);
}
 printf("SOCKET CREATED SUCCESSFULLY\n");
 server_addr.sin_family = AF_INET;
 server_addr.sin_port = htons(1023);
 server_addr.sin_addr.s_addr = INADDR_ANY;

addrsz = sizeof(server_addr);
sendto(sockfd,msg,1024,0,(struct sockaddr *)&server_addr,addrsz);
recvfrom(sockfd,buffer,1024,0,(struct sockaddr *)&server_addr,&addrsz);
printf("SERVER SYSTEM TIME :%s",buffer);
close(sockfd);

}
