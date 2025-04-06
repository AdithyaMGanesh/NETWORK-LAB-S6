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
int sockfd,clfd;
struct sockaddr_in server_addr,cl_addr;
socklen_t addrsz;
char buff[50];
char msg[50]="Frame : ";
char msg2[50];
sockfd = socket(AF_INET,SOCK_STREAM,0);
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(9009);
server_addr.sin_addr.s_addr = INADDR_ANY;

if(bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr))==-1)
{
perror("binding error");
exit(1);
}
if(listen(sockfd,5)==-1)
{
perror("listening error");
exit(1);
}
printf("Listening for client\n");
addrsz = sizeof(cl_addr);
clfd = accept(sockfd,(struct sockaddr*)&cl_addr,&addrsz);
if(clfd<0){
 perror("error listening");
 exit(1);}
struct timeval timeout1,timeout2;
int rv1,rv2;
fd_set set1,set2;
int i =-1;
printf("Go back n for 10 frames(n=3)");
qq:
 i = i+1;
 bzero(buff,sizeof(buff));
 bzero(msg2,sizeof(msg2));
 strcpy(msg2,msg);
 msg2[strlen(msg2)]=i+'0';
 msg2[strlen(msg2)]='\0';
 printf("Message sent to client : %s\n",msg2);
 write(clfd,msg2,sizeof(msg2));
 i = i+1;
 bzero(buff,sizeof(buff));
 bzero(msg2,sizeof(msg2));
 strcpy(msg2,msg);
 msg2[strlen(msg2)]=i+'0';
 msg2[strlen(msg2)]='\0';
 printf("Message sent to client : %s\n",msg2);
 write(clfd,msg2,sizeof(msg2));
 
 i = i+1;
 usleep(1000);

qqq:
 bzero(buff,sizeof(buff));
 bzero(msg2,sizeof(msg2));
 strcpy(msg2,msg);
 msg2[strlen(msg2)]=i+'0';
 printf("Message sent to client : %s\n",msg2);
 write(clfd,msg2,sizeof(msg2));
 FD_ZERO(&set1);
 FD_SET(clfd,&set1);
 timeout1.tv_sec = 2;
 timeout1.tv_usec = 0;
 rv1 = select(clfd+1,&set1,NULL,NULL,&timeout1);
 if(rv1 == -1)
{
 perror("select error");
}
else if(rv1==0)
{
printf("Timeout occured...Sending again from %d\n",i-2);
i = i-3;
goto qq;
}
else
{
read(clfd,buff,sizeof(buff));
printf("Message from client : %s\n",buff);
i++;
if(i<=9)
 goto qqq;
}

qq2:
 FD_ZERO(&set2);
 FD_SET(clfd,&set2);
 timeout2.tv_sec = 3;
 timeout2.tv_usec = 0;
 rv2 = select(clfd+1,&set2,NULL,NULL,&timeout2);
 if(rv2 == -1)
{
 perror("select error");
}
else if(rv2==0)
{
printf("Timeout occured...Sending again from %d\n\n",i-2);
i = i-2;
 bzero(buff,sizeof(buff));
 bzero(msg2,sizeof(msg2));
 strcpy(msg2,msg);
 msg2[strlen(msg2)]=i+'0';
 write(clfd,msg2,sizeof(msg2));
 usleep(1000);
 i++;
 bzero(buff,sizeof(buff));
 bzero(msg2,sizeof(msg2));
 strcpy(msg2,msg);
 msg2[strlen(msg2)]=i+'0';
 write(clfd,msg2,sizeof(msg2));
 goto qq2;
}
else
{
read(clfd,buff,sizeof(buff));
printf("Message from client : %s\n",buff);
bzero(buff,sizeof(buff));
read(clfd,buff,sizeof(buff));
printf("Message from client : %s\n",buff);
}
 
close(clfd);
close(sockfd);

}