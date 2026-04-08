#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "static.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <Server IP>\n", argv[0]);
        return 1;
    }

    int s = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_port = htons(9000);

    TacticalPacket pkt;
    char cmd[20];

    while(1) {
        printf("\n[add, del, show, exit]: ");
        scanf("%s", cmd);

        if(!strcmp(cmd, "exit")) break;

        memset(&pkt, 0, sizeof(pkt));

        if(!strcmp(cmd, "add")) {
            pkt.type = 0;
            printf("Target ID to Add: "); scanf("%d", &pkt.targetID);
            printf("X, Y Coordinates: "); scanf("%f %f", &pkt.x, &pkt.y);
        } 
        else if(!strcmp(cmd, "del")) {
            pkt.type = 1;
            printf("Target ID to Delete: "); scanf("%d", &pkt.targetID);
        } 
        else if(!strcmp(cmd, "show")) {
            pkt.type = 2;
        } 
        else {
            printf("Unknown command.\n");
            continue;
        }

        sendto(s, &pkt, sizeof(pkt), 0, (struct sockaddr *)&server, sizeof(server));
        printf(">> Request sent: %s\n", cmd);
    }

    close(s);
    return 0;
}
