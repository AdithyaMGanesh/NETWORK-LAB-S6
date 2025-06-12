#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

void  accept_connection(int sock,fd_set *all_sockets,int *numsockets)
{
 struct sockaddr_in cl_addr;
 int clsock;
 socklen_t addrsz;
 addrsz = sizeof(cl_addr);
 clsock = accept(sock,(struct sockaddr*)&cl_addr,&addrsz);
 if(clsock == -1)
{
 perror("connection failed");
 exit(1);
}
 FD_SET(clsock,all_sockets);
 *numsockets = *numsockets>clsock ? *numsockets:clsock;
 printf("CLIENT %d on port %d connected\n",clsock-3,cl_addr.sin_port);
 fflush(stdout);
} 

void recv_and_broadcast(int clsock,int sock,fd_set *all_sockets,int numsockets)
{
 char recvbuff[1024],sendbuff[1024];

 int n = recv(clsock,recvbuff,sizeof(recvbuff),0);
 if(n<=0)
{
 if(n==0)
   {printf("client %d has disconnected\n",clsock-3);
   fflush(stdout);}
 else
   perror("recv error\n");
   FD_CLR(clsock,all_sockets);
 close(clsock);
}
else
{
 recvbuff[n]=0;
 printf("Client %d : %s",clsock-3,recvbuff);
 sprintf(sendbuff, "Client %d: %s", clsock-3, recvbuff);
 for(int i=0;i<numsockets+1;i++)
{
 if(FD_ISSET(i,all_sockets))
{
 if(i!=clsock && i!=sock)
{
 int s=send(i,sendbuff,strlen(sendbuff),0);
if(s==-1)
 perror("sending error");
}
}
}
} 
}
int main()
{
 int sock,clsock,i;
 struct sockaddr_in server_addr,cl_addr;
 sock = socket(AF_INET,SOCK_STREAM,0);
 if(sock == -1)
{
 perror("SOCKET CREATION FAILED");
 exit(1);
}
printf("server socket %d \n",sock);
fflush(stdout);
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(4950);
server_addr.sin_addr.s_addr = INADDR_ANY;
int optval = 1;
if(setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(int))==-1)
{
perror("SOCKET error");
exit(1);
}
if(bind(sock,(struct sockaddr*)&server_addr,sizeof(server_addr))==-1)
{
perror("binding error");
 exit(1);
}
if((listen(sock,6))==-1)
{
perror("listening error");
exit(1);
}
printf("server running on port 4950 ,waiting for clients\n");
fflush(stdout);

fd_set all_sockets,selected_sockets;
int numsockets;
FD_ZERO(&all_sockets);
FD_SET(sock,&all_sockets);
numsockets = sock;

while(1)
{
 selected_sockets = all_sockets;
 if(select(numsockets+1,&selected_sockets,NULL,NULL,NULL)==-1)
 {
   perror("Select Error");
   exit(1);
 }
 for(i=0;i<numsockets+1;i++)
{
 if(FD_ISSET(i,&selected_sockets))
  {
   if(i==sock)
        accept_connection(sock,&all_sockets,&numsockets);
   else
        recv_and_broadcast(i,sock,&all_sockets,numsockets);
  }
}
}
close(sock);
return 0;
}