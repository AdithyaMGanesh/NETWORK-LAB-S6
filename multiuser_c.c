#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

void send_msg(int sock)
{
 char msg[1024];
 fgets(msg,1024,stdin);
 if(strcmp(msg,"quit\n")==0)
 {
    printf("exiting...");
    exit(0);
 }
 send(sock,msg,strlen(msg),0);
} 

void recv_msg(int sock)
{
 char recmsg[1024];
 int status = recv(sock,recmsg,strlen(recmsg),0);
 if(status==-1)
 {
  perror("recv error");
  exit(1);
 }
 else
  recmsg[status]='\0';
  printf("%s",recmsg);
}


int main()
{
 int sock,i;
 struct sockaddr_in server_addr;
 sock = socket(AF_INET,SOCK_STREAM,0);
 if(sock == -1)
{
 perror("SOCKET CREATION FAILED");
 exit(1);
}
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(4950);
server_addr.sin_addr.s_addr = INADDR_ANY;
int stat= connect(sock,(struct sockaddr*)&server_addr,sizeof(server_addr));
if(stat==-1){
perror("connection error");
exit(1);
}
fd_set all_sockets,selected_sockets;
FD_ZERO(&all_sockets);
FD_SET(0,&all_sockets);
FD_SET(sock,&all_sockets);

while(1)
{
 selected_sockets = all_sockets;
 if(select(sock+1,&selected_sockets,NULL,NULL,NULL)==-1)
 {
   perror("Select Error");
   exit(1);
 }
 if(FD_ISSET(0,&selected_sockets))
        send_msg(sock);
 if(FD_ISSET(sock,&selected_sockets))
        recv_msg(sock);
  }
close(sock);
return 0;
}