#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    float distance;
} Target;

int main() {
    int max_targets = 3;
    // Target 구조체 주소 3개를 담을 수 있는 포인터 배열 (레이더 슬롯)
    Target *radar_slots[3] = { NULL, NULL, NULL };

    printf("=== 레이더 시스템 가동 ===\n");

    // 1. 첫 번째 타겟 탐지 (메모리 할당)
    radar_slots[0] = (Target *)malloc(sizeof(Target));
    if (radar_slots[0] != NULL) {
        radar_slots[0]->id = 101;
        radar_slots[0]->distance = 50.5f;
        printf("[탐지] 타겟 %d가 %.1fkm 지점에서 발견되었습니다.\n", radar_slots[0]->id, radar_slots[0]->distance);
    }

    // 2. 두 번째 타겟 탐지
    radar_slots[1] = (Target *)malloc(sizeof(Target));
    if (radar_slots[1] != NULL) {
        radar_slots[1]->id = 202;
        radar_slots[1]->distance = 120.3f;
        printf("[탐지] 타겟 %d가 %.1fkm 지점에서 발견되었습니다.\n", radar_slots[1]->id, radar_slots[1]->distance);
    }
    
    radar_slots[2] = (Target *)malloc(sizeof(Target));
    if (radar_slots[2] != NULL){
        radar_slots[2]->id = 303;
        radar_slots[2]->distance = 67.5f;
        printf("타켓 %d가 %.1fkm 지점에서 발견되었습니다.\n", radar_slots[2]->id , radar_slots[2]->distance);
    }

    // 3. 첫 번째 타겟 격추 (메모리 해제 및 NULL 처리)
    printf("\n--- 타겟 %d 격추 시도 ---\n", radar_slots[0]->id);
    free(radar_slots[0]);
    radar_slots[0] = NULL; // 댕글링 포인터 방지 
    printf("[알림] 타겟 메모리가 안전하게 해제되었습니다.\n");

    // 4. 현재 레이더 슬롯 상태 점검
    printf("\n=== 현재 레이더 가동 현황 ===\n");
    for (int i = 0; i < max_targets; i++) {
        if (radar_slots[i] != NULL) {
            printf("Slot[%d]: 타겟 %d (거리: %.1fkm)\n", i, radar_slots[i]->id, radar_slots[i]->distance);
        } else {
            printf("Slot[%d]: 비어 있음 (대기 중)\n", i);
        }
    }

    // 남은 메모리 모두 정리 
    for (int i = 0; i < max_targets; i++) {
        if (radar_slots[i] != NULL) free(radar_slots[i]);
    }

    return 0;
}
