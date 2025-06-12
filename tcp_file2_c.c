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
 char buffer[1024],filename[100];
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
 printf("enter the filename : ");
 scanf("%s",filename);
 FILE *fp;
 fp = fopen(filename,"r");

 while(fgets(buffer,1024,fp)!=NULL){
 send(fd,buffer,sizeof(buffer),0);
 }
 fclose(fp);
 close(fd);
}

 
