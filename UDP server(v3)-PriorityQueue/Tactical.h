#ifndef TACTICAL_H
#define TACTICAL_H

#define MAX_HEAP_SIZE 100

typedef struct{
	int type;
	int targetID;
	float x,y;
	int priority;
	char desc[20];
} TacticalData;

typedef struct{
	TacticalData heap[MAX_HEAP_SIZE];
	int size;
} PriorityQueue;

#endif
