#include <stdio.h>

#define MAX_SIZE 5  // 테스트를 위해 크기를 5로 작게 잡았습니다.

// 1. 구조체 설계
struct CircularQueue {
    int data[MAX_SIZE];
    int front;
    int rear;
    int count;
};

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

// 5. 메인 함수 (시뮬레이션)
int main() {
    struct CircularQueue myQueue;
    initQueue(&myQueue);

    printf("--- 데이터 삽입 단계 ---\n");
    enqueue(&myQueue, 10);
    enqueue(&myQueue, 20);
    enqueue(&myQueue, 30);
    enqueue(&myQueue, 40);
    enqueue(&myQueue, 50);
    enqueue(&myQueue, 60); // 가득 차서 실패하는 모습을 보여줍니다.

    printf("\n--- 데이터 추출 단계 ---\n");
    for(int i = 0; i < 3; i++) {
        int val = dequeue(&myQueue);
        if(val != -1) printf("<- %d 추출 완료\n", val);
    }

    printf("\n--- 다시 삽입 (원형 회전 확인) ---\n");
    enqueue(&myQueue, 70);
    enqueue(&myQueue, 80);

    return 0;
}
