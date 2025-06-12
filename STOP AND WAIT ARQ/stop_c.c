#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 5568
#define MAX_BUFFER 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[MAX_BUFFER];
    char *ip = "127.0.0.1";  // localhost

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(ip);
    memset(&(server_addr.sin_zero), '\0', 8);

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sockfd);
        exit(1);
    }

    printf("[+]Connected to server at %s:%d\n", ip, PORT);
    
    int expected_seq = 0;

    while (1) {
        memset(buffer, 0, MAX_BUFFER);
        int n = recv(sockfd, buffer, MAX_BUFFER, 0);
        if (n <= 0) {
            printf("Connection closed or error.\n");
            break;
        }

        int received_seq = -1;
        sscanf(buffer, "Frame %d", &received_seq);  // Extract sequence number

        if (received_seq == expected_seq) {
            printf("Received Frame %d: %s\n", received_seq, buffer);

            // Simulate delay before sending ACK
            srand(time(NULL) + received_seq);  // seed randomness
            int delay = rand() % 4 + 1;        // 1 to 4 seconds delay
            sleep(delay);

            char ack[32];
            sprintf(ack, "ACK %d", received_seq);
            send(sockfd, ack, strlen(ack), 0);
            printf("Sent: %s\n\n", ack);

            expected_seq++;
        } else {
            printf("Duplicate Frame Received: %s (expected %d, got %d)\n", buffer, expected_seq, received_seq);
            
            // Re-send ACK for the last received in-order frame
            char ack[32];
            sprintf(ack, "ACK %d", received_seq);
            send(sockfd, ack, strlen(ack), 0);
            printf("Resent ACK for duplicate: %s\n\n", ack);
        }
    }

    close(sockfd);
    return 0;
}
