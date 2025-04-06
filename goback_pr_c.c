#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<time.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include <string.h>

void main()
{
int sockfd;
struct sockaddr_in server_addr;
char buff[50];
char msg[50]="Acknowledgement of : ";
char msg2[50];
sockfd = socket(AF_INET,SOCK_STREAM,0);
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(4950);
server_addr.sin_addr.s_addr = INADDR_ANY;

if(connect(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr))==-1)
{
perror("connection error");
exit(1);
}
printf("client running \n");
for(int i =0;i<=9;i++)
{
bzero(buff,sizeof(buff));
bzero(msg2,sizeof(msg2));
read(sockfd,msg2,sizeof(msg2));
if(msg2[strlen(msg2)-1] != i +'0')
{
 printf("Discarded frame received since expected is %d\n\n",i);
 i--;
}
else
{
printf("msg from server : %s\n",msg2);
printf("ackn sent for %d\n",msg2[strlen(msg2)-1]);
strcpy(msg2,msg);
msg2[strlen(msg2)]=i+'0';
write(sockfd,msg2,sizeof(msg2));

}
close(sockfd);
}
}