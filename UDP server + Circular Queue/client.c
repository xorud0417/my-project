#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

typedef struct {
    int type;
    int targetID;
    float x;
    float y;
    char desc[20];
} TacticalData;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <Server_IP>\n", argv[0]);
        return 1;
    }

    int s = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_port = htons(9000);

    char cmd[20];
    TacticalData myData;

    printf("📡 Tactical Command System Online\n");
    while(1) {
        printf("\n[명령: data, pop, status, exit] 입력: ");
        scanf("%s", cmd);

        if (strcmp(cmd, "exit") == 0) break;

        memset(&myData, 0, sizeof(TacticalData));

        if (strcmp(cmd, "pop") == 0) {
            myData.type = 1;
        } else if (strcmp(cmd, "status") == 0) {
            myData.type = 2;
        } else if (strcmp(cmd, "data") == 0) {
            myData.type = 0;
            printf("Target ID: "); scanf("%d", &myData.targetID);
            printf("X Coord: ");   scanf("%f", &myData.x);
            printf("Y Coord: ");   scanf("%f", &myData.y);
            printf("Description: "); scanf("%s", myData.desc);
        } else {
            printf("❌ Unknown Command.\n");
            continue;
        }

        sendto(s, &myData, sizeof(TacticalData), 0, (struct sockaddr *)&server, sizeof(server));
        printf("➡️ Command Sent: %s\n", cmd);
    }

    close(s);
    return 0;
}
