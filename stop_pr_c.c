#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<time.h>
#define TIMEOUT_SEC 2

void main()
{
 int sockfd;
 struct sockaddr_in server_addr;
 socklen_t addrsz;
 char buffer[1024];
 sockfd = socket(AF_INET,SOCK_STREAM,0);
 server_addr.sin_family = AF_INET;
 server_addr.sin_port = htons(4095);
 server_addr.sin_addr.s_addr = INADDR_ANY;

    int stat = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (stat < 0) {
        perror("connection failed");
        exit(1);
    }
int exp_seq = 0;
while(1)
{
memset(buffer,0,1024);
int n = recv(sockfd,buffer,1024,0);
if (n <= 0) {
    printf("Connection closed .\n");
    break;
}
int recv_seq = -1;
sscanf(buffer,"Frame %d ",&recv_seq);
if(recv_seq == exp_seq)
{
 printf("Received : %s\n",buffer);
 srand(time(NULL)+recv_seq);
 int delay = rand() % 4 + 1;
 sleep(delay);
 char ack[1024];
 sprintf(ack,"Ack %d \n",recv_seq);
 send(sockfd,ack,1024,0);
 printf("Sent : %s\n",ack);
 exp_seq++;
}
else
{
 printf("Duplicate frame Received : %d(expected %d)\n",recv_seq,exp_seq);
 char ack[1024];
 sprintf(ack,"No ack ");
 send(sockfd,ack,1024,0);
 printf("Resent : %s\n",ack);}   
}
close(sockfd);
}