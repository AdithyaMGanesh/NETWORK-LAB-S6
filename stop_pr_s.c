#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<time.h>
#define TIMEOUT_SEC 1

void main()
{
 int sockfd,client_fd;
 struct sockaddr_in server_addr,cl_addr;
 socklen_t addrsz;
 char buffer[1024];
 int num_frames;
 sockfd = socket(AF_INET,SOCK_STREAM,0);
 server_addr.sin_family = AF_INET;
 server_addr.sin_port = htons(4095);
 server_addr.sin_addr.s_addr = INADDR_ANY;

  if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(1);
    }

    if (listen(sockfd, 5) < 0) {
        perror("Listen failed");
        exit(1);
    }

    printf("[+]Server listening on port 4095...\n");

    addrsz = sizeof(cl_addr);
    client_fd = accept(sockfd, (struct sockaddr *)&cl_addr, &addrsz);
    if (client_fd < 0) {
        perror("Accept failed");
        exit(1);
    }
    printf("[+]Client connected: %s:%d\n", inet_ntoa(cl_addr.sin_addr), ntohs(cl_addr.sin_port));

    printf("Enter number of frames to send: ");
    scanf("%d", &num_frames);
    for(int i =0;i<num_frames;)
{
     sprintf(buffer,"Frame %d\n",i);
     send(client_fd,buffer,strlen(buffer),0);
     printf("Sent : %s\n",buffer);
     
     fd_set readfds;
     FD_ZERO(&readfds);
     FD_SET(client_fd,&readfds);
     struct timeval timeout;
     timeout.tv_sec=TIMEOUT_SEC;
     timeout.tv_usec=0;
     int activity = select(client_fd+1,&readfds,NULL,NULL,&timeout);
     if(activity == 0){
     printf("Timeout..retransmitting frame %d\n ",i);
     continue;
     }
     memset(buffer,0,1024);
     recv(client_fd,buffer,1024,0);
     printf("Received : %s\n\n",buffer);
     i++;
     sleep(1);
}
 printf("Transmitted all frames\n");
 close(client_fd);
 close(sockfd);


}