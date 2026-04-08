#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "static.h"

// 전역 변수로 메모리 풀 관리
Node pool[MAX_POOL];
int head = -1;      // 사용 중인 리스트의 시작점
int freeHead = 0;   // 빈 노드 리스트의 시작점

// [1] 초기화: 모든 노드를 Free List에 연결
void initPool() {
    for (int i = 0; i < MAX_POOL - 1; i++) {
        pool[i].next = i + 1;
    }
    pool[MAX_POOL - 1].next = -1; // 마지막 노드
}

// [2] 할당: Free List에서 빈 칸 하나 꺼내기
int allocNode() {
    if (freeHead == -1) return -1;
    int res = freeHead;
    freeHead = pool[freeHead].next;
    return res;
}

// [3] 반납: 사용 끝난 노드를 Free List로 복귀
void deallocNode(int idx) {
    pool[idx].next = freeHead;
    freeHead = idx;
}

// [4] 타겟 추가: 리스트 맨 앞에 삽입
void addTarget(int id, float x, float y) {
    int idx = allocNode();
    if (idx == -1) {
        printf("⚠️ [FULL] 메모리가 부족합니다. ID:%d 추가 불가\n", id);
        return;
    }
    pool[idx].targetID = id;
    pool[idx].x = x; 
    pool[idx].y = y;
    pool[idx].next = head; // 새 노드가 기존 head를 가리킴
    head = idx;            // head를 새 노드로 변경
    printf("✅ [Added] ID:%d (Pool Index:%d)\n", id, idx);
}

// [5] 타겟 삭제: ID를 찾아 연결 끊고 반납
void deleteTarget(int id) {
    int curr = head;
    int prev = -1;

    while (curr != -1 && pool[curr].targetID != id) {
        prev = curr;
        curr = pool[curr].next;
    }

    if (curr == -1) {
        printf("ℹ️ [Delete] ID:%d 찾지 못함\n", id);
        return;
    }

    if (prev == -1) head = pool[curr].next;
    else pool[prev].next = pool[curr].next;

    deallocNode(curr);
    printf("🗑️ [Deleted] ID:%d (Index:%d 반납)\n", id, curr);
}

// [6] 리스트 출력: 현재 연결된 모든 타겟 조회
void showTargets() {
    printf("\n--- 🛰️ Tactical Display (Linked List) ---\n");
    int curr = head;
    if (curr == -1) printf("(Empty)\n");
    while (curr != -1) {
        printf("[ID:%03d] Pos:(%.1f, %.1f) -> Next:%d\n", 
               pool[curr].targetID, pool[curr].x, pool[curr].y, pool[curr].next);
        curr = pool[curr].next;
    }
    printf("----------------------------------------\n");
}

int main() {
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);
    
    initPool(); // 메모리 풀 초기화 필수

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(9000);
    
    if (bind(s, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Bind failed");
        return 1;
    }

    printf("🛡️ Static Memory Pool Server (UDP 9000) Started...\n");

    TacticalPacket pkt;
    while (1) {
        int recv_len = recvfrom(s, &pkt, sizeof(pkt), 0, (struct sockaddr *)&client, &len);
        if (recv_len > 0) {
            switch(pkt.type) {
                case 0: addTarget(pkt.targetID, pkt.x, pkt.y); break;
                case 1: deleteTarget(pkt.targetID); break;
                case 2: showTargets(); break;
            }
        }
    }
    close(s);
    return 0;
}
