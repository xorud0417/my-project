#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "Tactical.h"

int main(int argc, char *argv[]) {
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_port = htons(9000);

    TacticalData data;
    char cmd[20];

    while(1) {
        printf("\n[data, pop, status, exit]: ");
        scanf("%s", cmd);
        if(!strcmp(cmd, "exit")) break;

        memset(&data, 0, sizeof(data));
        if(!strcmp(cmd, "data")) {
		    data.type = 0;
		    printf("ID: "); 
		    scanf("%d", &data.targetID);
		    
		    printf("Priority (1:High, 3:Low): "); 
		    scanf(" %d", &data.priority); // %d 앞에 공백 추가 (엔터 무시)
		    
		    printf("X, Y: "); 
		    scanf(" %f %f", &data.x, &data.y); // %f 앞에 공백 추가
		    
		    // 문자열 입력 시 버퍼 비우기
		    while(getchar() != '\n'); 
		    printf("Description: ");
		    fgets(data.desc, sizeof(data.desc), stdin);
		    data.desc[strcspn(data.desc, "\n")] = 0; // 줄바꿈 제거
		} else if(!strcmp(cmd, "pop")) data.type = 1;
        else if(!strcmp(cmd, "status")) data.type = 2;

        sendto(s, &data, sizeof(data), 0, (struct sockaddr *)&server, sizeof(server));
    }
    close(s);
    return 0;
}
