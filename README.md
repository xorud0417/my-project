Project: Efficient Circular Queue for Embedded Systems

1. 목적

자원이 제한된 임베디드/방산 시스템 환경에서 malloc 없이 동작하는 정적 메모리 기반 버퍼 구현.

UDP 통신 등 실시간 데이터 스트리밍 상황에서의 데이터 유실 방지 및 처리 지연 최소화.

2. 주요 특징

Zero Dynamic Allocation: 힙(Heap) 메모리를 사용하지 않아 메모리 누수 위험 제거.

Modulo Arithmetic: 나머지 연산자를 이용한 효율적인 인덱스 순환.

Boundary Check: Queue Full/Empty 예외 처리를 통한 시스템 안정성 확보.
