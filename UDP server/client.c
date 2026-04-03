#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("사용법: %s <IP주소>\n", argv[0]);
        return 1;
    }

    int s = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_port = htons(9000);

    char *msg = "Defense Data: 123.45";
    sendto(s, msg, strlen(msg), 0, (struct sockaddr *)&server, sizeof(server));
    printf("데이터 전송 완료: %s\n", msg);

    close(s);
    return 0;
}