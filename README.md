##C로 만들어진 간단한 지렁이 키우기 게임##

**이 게임은**는 C를 기반으로 만들어진 간단한 게임입니다.

# 간략한 이 게임의 특징입니다. #

- 키보드의 방향키 입력을 통한 진행
- 초마다 화면 초기화 후 맵 생성

**잘 만든 게임은 아니지만 공부용으로 대체해주시기 바랍니다.**

**코드 설명**

 - map.txt : 파일 읽어, map 생성
 - worm.c : 지렁이 키우기 게임의 핵심 코드
 

### 2013이상에서는 몇가지 코드를 수정해야 합니다. ###

- getch()의 경우, _getch()로 수정해야 합니다.
- khbit()의 경우, _khbit()로 수정해야 합니다.
- fopen()의 경우, fopen_s()로 수정해야 합니다.
	- ex) fd = fopen("map.txt","r') -> fopen_s(&fd,동일)
	
