#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>      // Linux 전용 헤더
#include <arpa/inet.h>   // 인터넷 주소 관련 헤더
#include <sys/socket.h>  // 소켓 관련 헤더

int main() {
    // [1] UDP 소켓 생성 (무전기 준비)
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0) {
        printf("소켓 생성 실패!\n");
        return 1;
    }

    // [2] 서버 주소 설정 (채널 설정)
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY); // 내 컴퓨터의 모든 IP 허용
    server.sin_port = htons(9000);              // 9000번 채널(포트) 사용

    // [3] 바인드 (채널 고정)
    if (bind(s, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("바인드 실패! (이미 포트가 사용 중일 수 있습니다)\n");
        return 1;
    }

    printf("🛡️ [SERVER] 9000번 포트에서 데이터 대기 중...\n");

    // [4] 데이터 수신 루프 (귀 기울이기)
    char buf[512];
    struct sockaddr_in client;
    socklen_t clientLen = sizeof(client);

    while (1) {
        // 상대방이 데이터를 보낼 때까지 여기서 딱 멈춰서 기다립니다.
        int len = recvfrom(s, buf, sizeof(buf) - 1, 0, (struct sockaddr *)&client, &clientLen);
        
        if (len > 0) {
            buf[len] = '\0';
            printf("📩 [수신 데이터]: %s\n", buf);
            
            if (strcmp(buf, "exit") == 0) break;
        }
    }

    // [5] 소켓 닫기
    close(s);
    printf("서버를 종료합니다.\n");
    return 0;
}