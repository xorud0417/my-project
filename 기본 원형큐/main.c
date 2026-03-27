#include <stdio.h>
#include "circular_queue.h"

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
