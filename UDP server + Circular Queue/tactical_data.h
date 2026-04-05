#ifndef TACTICAL_DATA_H
#define TACTICAL_DATA_H
#define MAX_QUEUE_SIZE 5

// [데이터 규격] 전술 데이터 구조체
typedef struct {
    int type;          // 0: 데이터 저장, 1: POP(삭제), 2: STATUS(상태)
    int targetID;      // 타겟 번호
    float x;           // X 좌표
    float y;           // Y 좌표
    char desc[20];     // 타겟 설명 (예: Enemy, Ally)
} TacticalData;

// [창고] 원형 큐 구조체
typedef struct {
    TacticalData data[MAX_QUEUE_SIZE]; 
    int front;
    int rear;
} CircularQueue;

void initQueue(CircularQueue *q) {
    q->front = 0;
    q->rear = 0;
}

void enqueue(CircularQueue *q, TacticalData newData) {
    if ((q->rear + 1) % MAX_QUEUE_SIZE == q->front) {
        printf("⚠️ [Queue Full] 데이터 유실 발생!\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = newData;
    printf("✅ [Enqueue] ID:%d 저장됨 (Rear:%d)\n", newData.targetID, q->rear);
}

void dequeue(CircularQueue *q) {
    if (q->front == q->rear) {
        printf("ℹ️ [Queue Empty] 처리할 데이터가 없습니다.\n");
        return;
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    TacticalData d = q->data[q->front];
    printf("📤 [Dequeue] ID:%d | 위치:(%.1f, %.1f) | 유형:%s 처리완료\n", 
            d.targetID, d.x, d.y, d.desc);
}

void showStatus(CircularQueue *q) {
    printf("\n--- 🛰️ Tactical Queue Status ---\n");
    if (q->front == q->rear) {
        printf("Empty.\n");
    } else {
        int i = (q->front + 1) % MAX_QUEUE_SIZE;
        while (1) {
            TacticalData d = q->data[i];
            printf("[%d] ID:%03d | Pos:(%5.1f, %5.1f) | Desc:%s\n", i, d.targetID, d.x, d.y, d.desc);
            if (i == q->rear) break;
            i = (i + 1) % MAX_QUEUE_SIZE;
        }
    }
    printf("-------------------------------\n\n");
}
