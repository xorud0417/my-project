#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "tactical_data.h"


int main() {
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server, client;
    socklen_t clientLen = sizeof(client);
    
    CircularQueue q;
    initQueue(&q);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(9000);

    if (bind(s, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Bind failed");
        return 1;
    }

    printf("🛡️ 방산 서버 V2 (전술 데이터 모드) 시작...\n");

    TacticalData incoming;
    while (1) {
        int len = recvfrom(s, &incoming, sizeof(TacticalData), 0, (struct sockaddr *)&client, &clientLen);
        if (len > 0) {
            if (incoming.type == 1) dequeue(&q);
            else if (incoming.type == 2) showStatus(&q);
            else enqueue(&q, incoming);
        }
    }
    close(s);
    return 0;
}
