#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main()
{
 int sockfd,cl_fd;
 struct sockaddr_in server_addr,cl_addr;
 socklen_t addrsz;
 char buffer[1024];
 sockfd = socket(AF_INET,SOCK_STREAM,0);
 if(sockfd == -1)
{
 perror("socket cre failed"); 
 exit(1);
}
 printf("socket created successfully\n");
 server_addr.sin_family = AF_INET;
 server_addr.sin_port = htons(4950);
 server_addr.sin_addr.s_addr = INADDR_ANY;

if(bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr))==-1)
{
perror("binding failed"); 
 exit(1);
}
 printf("bind successful\n");
 if(listen(sockfd,5)==-1)
{
perror("listening failed"); 
 exit(1);
}
 printf("listening \n");
 addrsz = sizeof(cl_addr);
 cl_fd = accept(sockfd,(struct sockaddr *)&cl_addr,&addrsz);
 if(cl_fd == -1)
{
perror("connetion failed"); 
 exit(1);
}
 printf("client connection successful\n");
 FILE *fp;
 fp = fopen("op.txt","w");
 int by,i;
 while((by = recv(cl_fd,buffer,1024,0))>0){
 buffer[by]='\0';
 fprintf(fp,"%s",buffer); 
 }
 fclose(fp);
 close(sockfd);
 close(cl_fd);
}