// server_sender.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define PORT 5568
#define MAX_BUFFER 1024
#define TIMEOUT_SEC 2

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[MAX_BUFFER];
    int num_frames;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(server_addr.sin_zero), '\0', 8);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(1);
    }

    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        exit(1);
    }

    printf("[+]Server listening on port %d...\n", PORT);

    addr_size = sizeof(client_addr);
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_size);
    if (client_fd < 0) {
        perror("Accept failed");
        exit(1);
    }
    printf("[+]Client connected: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    printf("Enter number of frames to send: ");
    scanf("%d", &num_frames);

    for (int i = 0; i < num_frames;) {
        sprintf(buffer, "Frame %d data", i);
        send(client_fd, buffer, strlen(buffer), 0);
        printf("Sent: %s\n", buffer);

        // Wait for ACK with timeout
        fd_set readfds;
        struct timeval timeout;
        FD_ZERO(&readfds);
        FD_SET(client_fd, &readfds);
        timeout.tv_sec = TIMEOUT_SEC;
        timeout.tv_usec = 0;

        int activity = select(client_fd + 1, &readfds, NULL, NULL, &timeout);
        if (activity == 0) {
            printf("Timeout! Retransmitting Frame %d\n", i);
            continue; // resend same frame
        }

        memset(buffer, 0, MAX_BUFFER);
        recv(client_fd, buffer, MAX_BUFFER, 0);
        printf("Received: %s\n\n", buffer);

        i++; // proceed to next frame only after valid ACK
        sleep(1);
    }

    printf("[+]All frames sent. Closing connection.\n");
    close(client_fd);
    close(server_fd);
    return 0;
}
