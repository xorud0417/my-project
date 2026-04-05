# 🛡️ UDP 전술 데이터 관리 시스템 (Circular Queue)

이 프로젝트는 C언어를 이용해 구조체(Struct) 데이터를 UDP 통신으로 주고받고, 
서버 측에서 원형 큐(Circular Queue)를 이용해 데이터를 관리하는 연습 프로젝트입니다.

## 📂 주요 파일
- `tactical_data.h`: 전술 데이터(ID, 좌표, 타입 등) 구조체 정의
- `server.c`: UDP 서버 및 원형 큐 관리 (데이터 저장/처리/상태확인)
- `client.c`: 전술 명령 송신 클라이언트 (Data, Pop, Status 명령)

## 🚀 실행 방법
### 1. 컴파일
```bash
gcc -o server server.c
gcc -o client client.c
