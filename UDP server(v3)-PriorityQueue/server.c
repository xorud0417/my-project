#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "Tactical.h"

void initQueue(PriorityQueue *q) { q->size = 0; }

// 데이터 삽입 시 위로 올라가며 정렬 (Up-Heap)
void push(PriorityQueue *q, TacticalData data) {
    if (q->size >= MAX_HEAP_SIZE - 1) return;
    
    int i = ++(q->size);
    while (i != 1 && data.priority < q->heap[i/2].priority) {
        q->heap[i] = q->heap[i/2];
        i /= 2;
    }
    q->heap[i] = data;
    printf("🎯 [Detected] ID:%d (우선순위:%d) 탐지 및 정렬 완료\n", data.targetID, data.priority);
}

// 가장 높은 우선순위 추출 후 아래로 재정렬 (Down-Heap)
void pop(PriorityQueue *q) {
    if (q->size == 0) {
        printf("ℹ️ 현재 대기 중인 위협이 없습니다.\n");
        return;
    }
    
    TacticalData root = q->heap[1]; // 가장 위험한 타겟
    TacticalData last = q->heap[q->size--];
    int parent = 1, child = 2;

    while (child <= q->size) {
        if (child < q->size && q->heap[child].priority > q->heap[child+1].priority) 
            child++;
        if (last.priority <= q->heap[child].priority) break;
        
        q->heap[parent] = q->heap[child];
        parent = child;
        child *= 2;
    }
    q->heap[parent] = last;

    printf("🔥 [Action] 최우선 타겟 처리: ID:%d | 등급:%d | 위치:(%.1f, %.1f)\n", 
            root.targetID, root.priority, root.x, root.y);
}

void printStatus(PriorityQueue *q) {
    printf("\n--- 🛰️ 실시간 위협 순위 보고 ---\n");
    for (int i = 1; i <= q->size; i++) {
        printf("[%d순위 대기] ID:%03d | 위협등급:%d | 비고:%s\n", 
                i, q->heap[i].targetID, q->heap[i].priority, q->heap[i].desc);
    }
    printf("-------------------------------\n");
}

int main() {
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);
    
    PriorityQueue q;
    initQueue(&q);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(9000);
    bind(s, (struct sockaddr *)&server, sizeof(server));

    printf("🛡️ 전술 우선순위 관제 서버 가동...\n");

    TacticalData incoming;
    while (1) {
        if (recvfrom(s, &incoming, sizeof(incoming), 0, (struct sockaddr *)&client, &len) > 0) {
            if (incoming.type == 0) push(&q, incoming);
            else if (incoming.type == 1) pop(&q);
            else if (incoming.type == 2) printStatus(&q);
        }
    }
    return 0;
}
