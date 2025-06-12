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
 struct sockaddr_in server_addr,clie_addr;
 socklen_t addrsz;
 char buffer[1024];
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

 int status = bind(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
 if(status == -1)
{
perror("binding error");
 exit(1);
}
addrsz = sizeof(clie_addr);
recvfrom(sockfd,buffer,1024,0,(struct sockaddr *)&clie_addr,&addrsz);
printf("received from client : %s",buffer);
char buff2[102]="hii client....";
sendto(sockfd,buff2,102,0,(struct sockaddr *)&clie_addr,addrsz);
close(sockfd);

}