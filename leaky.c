#include <stdio.h>

#define MIN(x, y) ((x) < (y) ? (x) : (y))

int main() {
    int bucketSize, outputRate, nPackets = 0;
    int input[100], i = 0, choice;
    int remaining = 0, drop = 0;

    printf("Enter Bucket Size (Bytes): ");
    scanf("%d", &bucketSize);

    printf("Enter Output Rate (Bytes/sec): ");
    scanf("%d", &outputRate);

    // Take input packets for each second
    do {
        printf("Enter size of packet at sec %d: ", i + 1);
        scanf("%d", &input[i]);
        i++;
        printf("Enter 1 to continue / 0 to stop: ");
        scanf("%d", &choice);
    } while (choice && i < 100);

    nPackets = i;

    printf("\nTime\tReceived\tSent\tDropped\tRemaining\n");

    for (i = 0; i < nPackets || remaining > 0; i++) {
        int received = input[i];
        int sent = MIN(outputRate, remaining + received);

        if (remaining + received > bucketSize) {
            drop = (remaining + received) - bucketSize;
            received -= drop;  // only accept data that fits
        } else {
            drop = 0;
        }

        remaining = remaining + received - sent;
        if (remaining < 0) remaining = 0;

        printf("%2d\t%8d\t%4d\t%6d\t%9d\n", i + 1, input[i], sent, drop, remaining);
    }

    return 0;
}
