#include <stdio.h>
#include "circular_queue.h"

// 2. 초기화 함수
void initQueue(struct CircularQueue *q) {
    q->front = 0;
    q->rear = 0;
    q->count = 0;
}

// 3. 데이터 넣기 (Enqueue)
void enqueue(struct CircularQueue *q, int value) {
    if (q->count == MAX_SIZE) {
        printf("[경고] 큐가 가득 찼습니다! (%d 삽입 실패)\n", value);
        return;
    }
    q->data[q->rear] = value;
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->count++;
    printf("-> %d 삽입 완료 (현재 개수: %d)\n", value, q->count);
}

// 4. 데이터 빼기 (Dequeue)
int dequeue(struct CircularQueue *q) {
    if (q->count == 0) {
        printf("[에러] 큐가 비어있습니다!\n");
        return -1;
    }
    int extracted = q->data[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    q->count--;
    return extracted;
}
