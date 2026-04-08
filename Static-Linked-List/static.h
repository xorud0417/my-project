#ifndef STATIC_H
#define STATIC_H

#define MAX_POOL 10  // 메모리 풀의 크기

// [노드 구조체] 데이터 + 다음 노드의 위치(인덱스)
typedef struct {
    int targetID;
    float x, y;
    int next;        // 다음 노드의 인덱스 (-1이면 끝을 의미)
} Node;

// [전술 데이터 패킷] 통신용
typedef struct {
    int type;        // 0: 추가(Add), 1: 삭제(Delete), 2: 조회(Show)
    int targetID;
    float x, y;
} TacticalPacket;

#endif
