#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main()
{
 int fd;
 struct sockaddr_in server_addr;
 socklen_t addrsz;
 char buffer[1024];
 fd = socket(AF_INET,SOCK_STREAM,0);
 if(fd == -1)
{
 perror("socket cre failed"); 
 exit(1);
}
 printf("socket created successfully\n");
 server_addr.sin_family = AF_INET;
 server_addr.sin_port = htons(4950);
 server_addr.sin_addr.s_addr = INADDR_ANY;

 int status = connect(fd,(struct sockaddr *)&server_addr,sizeof(server_addr));
 if(status == -1)
{
perror("connetion failed"); 
 exit(1);
}
 printf("connected to server\n");
 FILE *fp;
 fp = fopen("send.txt","r");
 fgets(buffer,1024,fp);
 buffer[strcspn(buffer, "\n")] = '\0';
 send(fd,buffer,sizeof(buffer),0);
 char res[1024];
 recv(fd,res,1024,0);
 printf("%s",res);
 fclose(fp);
 close(fd);
}

 
