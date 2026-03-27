#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#define MAX_SIZE 100

struct CircularQueue {
    int data[MAX_SIZE];
    int front;
    int rear;
    int count;
};

void initQueue(struct CircularQueue *q);

void enqueue(struct CircularQueue *q, int value);

int dequeue(struct CircularQueue *q);

#endif
