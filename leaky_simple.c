#include <stdio.h>
#include <stdlib.h>

#define min(x, y) ((x) < (y) ? (x) : (y))

int main() {
    int bkt_size, rate, packetCount, packet[20], i;
    int remainingSize = 0;

    printf("Enter Bucket Size: ");
    scanf("%d", &bkt_size);
    printf("Enter Output Rate: ");
    scanf("%d", &rate);
    printf("Enter number of packets: ");
    scanf("%d", &packetCount);

    for (i = 0; i < packetCount; i++) {
        printf("Packet Size at sec %d: ", i + 1);
        scanf("%d", &packet[i]);
    }
    int dropped;
    i = 0;
    
    printf("\nTime\tReceived\tSent\tDropped\tRemaining\n");

    while (i < packetCount || remainingSize > 0) {
        int received = packet[i] ;
       
        if (received + remainingSize > bkt_size) {
             dropped = received;
            
        } else {
             dropped = 0;
            remainingSize += received;
        }

        int sent = min(rate, remainingSize);
        remainingSize -= sent;
        printf("%2d\t%8d\t%4d\t%6d\t%9d\n", i + 1, received, sent, dropped, remainingSize);
        i++;
    }

    return 0;
}