#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main()
{
 int sockfd,cl_fd,flag=1,i,j,temp;
 struct sockaddr_in server_addr,cl_addr;
 socklen_t addrsz;
 char buffer[1024],newstr[1024];
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
 int n = recv(cl_fd,buffer,1024,0);
 if(n<0)
 {
    perror("receive error");
    exit(1);
 }
 buffer[n]='\0';
 FILE *fp;
 fp = fopen("op1.txt","w"); 
 int str_len=strlen(buffer);
 int mid = str_len/2;
 for(i=0,j=str_len-1;i<mid;i++,j--)
 {
    if(buffer[i]!=buffer[j])
    {
        flag=0;
        break;
    }
 } 
 j=0;
 for(i=str_len-1;i>=0;i--)
 {
    newstr[j]=buffer[i];
    j++;

 }
 newstr[j]='\0';
 fprintf(fp,"%s",newstr);
 if(flag==1)
 {
  char res[1024] = "STRING IS PALINDROME\n";
  send(cl_fd,res,strlen(res),0);
  printf("STRING IS PALINDROME\n");
 }
 else if(flag==0)
 {
  char res[1024] = "STRING IS NOT PALINDROME\n";
  send(cl_fd,res,strlen(res),0);
  printf("STRING IS NOT PALINDROME\n");
 }
 fclose(fp);
 close(sockfd);
 close(cl_fd);
}