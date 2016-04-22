#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define width 20									// 가로 축 길이
#define height 20									// 세로 축 길이
#define ITEM_COUNT 20								// 게임에서의 총 아이템의 갯수

typedef struct worm{								// 지렁이 노드
	int x;
	int y;
	int value;
	struct worm* link;
}Worm;

typedef struct{										// 지렁이 헤드
	Worm* head;
}Worm_h;

int makeMap(int Map[width][height]);				// 시작 시, 맵 생성
void printMap();									// 맵 출력
int Map[width][height]={0};							// 맵의 배열
void leftMove(Worm_h* p);							// 왼쪽 이동
void rightMove(Worm_h* p);							// 오른쪽 이동
void upMove(Worm_h* p);								// 위쪽 이동
void downMove(Worm_h* p);							// 아래쪽 이동
void gameOver(int timer);							// 게임 끝 확인
void die();
Worm_h* createHead(){								// 리스트 헤드 생성
	Worm_h* w;
	w=(Worm_h*)malloc(sizeof(Worm_h));
	w->head=NULL;
	return w;
}


void addTail(Worm_h* w, int x, int y){				// 지렁이 꼬리 추가
	Worm* newtail;
	Worm* p;
	newtail=(Worm*)malloc(sizeof(Worm));			// 새로운 노드 생성
	newtail->link=NULL;								// 새로운 노드의 링크를 Null로 설정
	if(w->head==NULL){								// 헤드가 Null이라면, 새로운 노드 넣기
		newtail->x=10;								// 좌표 설정
		newtail->y=10;								// 좌표 설정
		newtail->value=55;
		Map[newtail->x][newtail->y]=55;				// 해당 좌표에 지렁이 몸 표시
		w->head=newtail;
		return;
	}
	p=w->head;										// 헤드가 존재한다면, 임시노드 p가 w->head를 가리킨다,
	while(p->link!=NULL)		p=p->link;			// 리스트의 끝에 도달할때까지 반복
	newtail->value=55;
	newtail->x=x;
	newtail->y=y;
	Map[newtail->x][newtail->y]=newtail->value;		// 해당 좌표에 지렁이 몸 표시
	p->link=newtail;								// 리스트의 끝에 새로운 리스트 연결
}

int itemcount=ITEM_COUNT;							// 아이템의 갯수
/*
Worm head;											// 리스트의 헤드
Worm tail;
int length=3;										// 최초 길이
*/
void itemRand(){									// 아이템을 랜덤으로 만들어준다.
	int i,x,y;
	srand(time(NULL));
	for(i=0; i<ITEM_COUNT; i++){
		x=rand()%18+1;								// x 좌표
		y=rand()%18+1;								// y 좌표 
		if(Map[x][y]==54)		i-=1;				// 해당 좌표에 아이템이 있다면 다시 생성
		Map[x][y]=54;								// 해당 좌표에 아이템 설정
	}	
}

void main(){										// 0 : 왼쪽 1 : 오른쪽 2 : 위쪽 3 : 아래쪽 4 : 없음 
	int key;
	int direct=0;
	int timer=0;
	Worm_h* p;
	p=createHead();									// head 설정
	makeMap(Map);									// 맵을 만드는 함수
	itemRand();										// 아이템 랜덤 생성
	addTail(p,10,10);								// 초기 지렁이 몸 3개 생성
	addTail(p,10,11);
	addTail(p,10,12);
	system("cls");									// 화면 전체 지우기
	printMap();										// 맵 출력

	key=getch();									// 키보드로부터 값을 받음
	if(key==224){									// 방향키 아스키 코드는 224 XX
		key=getch();		
		while(1){
			Sleep(100);
			if(!kbhit()){							// 키가 눌리지 않았을 경우
				switch(direct){						// 방향에 따라 그 방향으로 계속 움직임
					case 0:
						leftMove(p);				// 0일 경우, 왼쪽으로 이동
 						gameOver(timer++);			// 게임 종료 확인.
						break;
					case 1:
						rightMove(p);				// 1일 경우, 오른쪽으로 이동.					
						gameOver(timer++);			// 게임 종료 확인.
						break;
					case 2:
						upMove(p);					// 2일 경우, 위쪽으로 이동
						gameOver(timer++);			// 게임 종료 확인
						break;
					case 3:
						downMove(p);				// 3일 경우, 아래쪽으로 이동
						gameOver(timer++);			// 게임 종료 확인.
						break;
				}
			}
			else{									// 키가 눌러져 있다면.
				key=getch(); 
				if(key==224){						// 방향키라면
					key=getch();					// 두번째 아스키코드를 받는다.
					
					switch(key){					// 해당 키값을 확인
						case 75:					// 왼쪽
							if(direct==1)	break;	// 오른쪽으로 이동중, 왼쪽 이동 불가
							direct=0;					
							break;
						case 77:					// 오른쪽
							if(direct==0)	break;	// 왼쪽 이동중, 오른쪽 이동 불가
							direct=1;
							break;
						case 72:					// 위
							if(direct==3)	break;	// 아래쪽 이동 중, 위쪽 이동 불가
							direct=2;									
							break;
						case 80:					// 아래 
							if(direct==2)	break;	// 위쪽 이동 중, 아래쪽 이동 불가
							direct=3;
							break;
					}
				}
				system("cls");						// 화면 지우기
				printMap();							// 화면 출력
				fflush(stdin);						// 입력 버퍼 초기화
			}
		}
	}	
}



void leftMove(Worm_h* w)							// 왼쪽으로 움직이는 함수
{
	Worm* temp;										// 이전 위치 저장할 임시 노드
	Worm* p;										// 리스트 가리킬 임시 노드
	Worm* previous;									// 기존 리스트의 마지막 노드를 가리킨 변수
	boolean check;									// 아이템 먹음을 확인해줄 변수( 1은 true, 0은 false )
	int x, y, value;								// temp와 같이, 임시 저장해줄 변수
	temp=(Worm*)malloc(sizeof(Worm));				// 임시 노드 동적할당.
	previous=(Worm*)malloc(sizeof(Worm));			// 임시 노드 동적할당.
	p=w->head;										// 리스트 가리키는 임시노드가 헤더를 가리킨다.
	temp->x=p->x;									// 헤더의 데이터를 위치 저장할 임시 노드에 저장.
	temp->y=p->y;
	temp->value=p->value;
	p->y-=1;										// 헤드의 위치를 왼쪽으로 한칸 이동.
	if(p->y!=0){									// 벽이 있는 곳이 아니라면,
		if(Map[p->x][p->y]==55)		die();			// 자신의 몸이라면, 죽기
		if(Map[p->x][p->y]==54){					// 아이템 위치라면
			itemcount--;							// 전체 아이템 수 1개 감소
			check=1;								// check를 통해 아이템 먹음을 인지
		}
		else						check=0;		// 아이템 위치가 아니라면, check를 통해 아이템 먹지 않음을 인지
		Map[p->x][p->y]=p->value;					// 맵 값에 지렁이 헤드값을 넣어, 움직인것 처럼 표시
		p=p->link;									// p는 다음 링크로 이동.
		while(p!=NULL){								// 리스트의 끝이 될때까지 확인
			if(p->link==NULL){						// 마지막 노드라면, 마지막 노드에 대한 정보를 저장한다 ( 추후, 꼬리 추가 때 사용 )
				previous->x=p->x;
				previous->y=p->y;
				previous->value=p->value;
			}
			Map[p->x][p->y]=48;						// 해당 자리에, 공백으로 채운다.
			x=p->x;									// 현 자리 저장
			y=p->y;									// 현 자리 저장
			value=p->value;							// 현 자리에 대한 값 저장
			p->x=temp->x;							// 자신의 이전노드가 위치했던 곳으로 이동
			p->y=temp->y;							// 자신의 이전노드가 위치했던 곳으로 이동
			p->value=temp->value;					// 자신의 이전노드가 가지고 있던 값을 설정
			Map[p->x][p->y]=p->value;				// 맵에 자신이 가진 값을 설정
			temp->x=x;								// 현 자리에 대한 위치 저장값을, Temp라는 임시 노드에 저장
			temp->y=y;								// 현 자리에 대한 위치 저장값을, Temp라는 임시 노드에 저장
			temp->value=value;						// 현 자리에 대한 값을, Temp라는 임시 노드에 저장
			p=p->link;								// 다음 노드로 이동
			/*
													자신의 위치를 다음 노드에게 인계.
			*/
		}
		if(check)									// 아이템을 획득 했을 시,
			addTail(w,previous->x,previous->y);		// 새로운 몸을 마지막 노드에 대한 정보에 입력한다.

	}
	else							die();			// 헤드의 옮긴위치가 벽이었다면, 게임 끝
	system("cls");									// 화면 지우기
	printMap();										// 화면 출력
}

void rightMove(Worm_h* w){							// 위와 같은 형식
	Worm* temp;
	Worm* p;
	Worm* previous;
	boolean check;
	int x, y, value;
	temp=(Worm*)malloc(sizeof(Worm));
	previous=(Worm*)malloc(sizeof(Worm));
	p=w->head;
	temp->x=p->x;
	temp->y=p->y;
	temp->value=p->value;
	p->y+=1;
	if(p->y!=(width-1)){
		if(Map[p->x][p->y]==55)		die();			
		if(Map[p->x][p->y]==54){
			itemcount--;
			check=1;
		}
		else						check=0;
		
		Map[p->x][p->y]=p->value;
		p=p->link;
		while(p!=NULL){
			if(p->link==NULL){
				previous->x=p->x;
				previous->y=p->y;
				previous->value=p->value;
			}
			Map[p->x][p->y]=48;
			x=p->x;
			y=p->y;
			value=p->value;
			p->x=temp->x;
			p->y=temp->y;
			p->value=temp->value;
			Map[p->x][p->y]=p->value;
			temp->x=x;
			temp->y=y;
			temp->value=value;
			p=p->link;	
		}
		if(check)					addTail(w,previous->x,previous->y);
	}
	else							die();
	system("cls");
	printMap();
}


void upMove(Worm_h* w){
	Worm* temp;
	Worm* p;
	Worm* previous;
	boolean check;
	int x, y, value;
	temp=(Worm*)malloc(sizeof(Worm));
	previous=(Worm*)malloc(sizeof(Worm));
	p=w->head;
	temp->x=p->x;
	temp->y=p->y;
	temp->value=p->value;
	p->x-=1;
	if(p->x!=0){
		if(Map[p->x][p->y]==55)		die();			
		if(Map[p->x][p->y]==54){
			itemcount--;
			check=1;
		}
		else						check=0;
		
		Map[p->x][p->y]=p->value;
		p=p->link;
		while(p!=NULL){
			
			if(p->link==NULL){
				previous->x=p->x;
				previous->y=p->y;
				previous->value=p->value;
			}
			Map[p->x][p->y]=48;
			x=p->x;
			y=p->y;
			value=p->value;
			p->x=temp->x;
			p->y=temp->y;
			p->value=temp->value;
			Map[p->x][p->y]=p->value;
			temp->x=x;
			temp->y=y;
			temp->value=value;
			p=p->link;	
		}
		if(check)					addTail(w,previous->x,previous->y);
	}
	else							die();
	
	system("cls");
	printMap();
}

void downMove(Worm_h* w){
	Worm* temp;
	Worm* p;
	Worm* previous;
	boolean check;
	int x, y, value;
	temp=(Worm*)malloc(sizeof(Worm));
	previous=(Worm*)malloc(sizeof(Worm));
	p=w->head;
	temp->x=p->x;
	temp->y=p->y;
	temp->value=p->value;
	p->x+=1;
	if(p->x!=(height-1)){
		if(Map[p->x][p->y]==55)		die();			
		if(Map[p->x][p->y]==54){
			itemcount--;
			check=1;
		}
		else						check=0;
		Map[p->x][p->y]=p->value;
		p=p->link;
		while(p!=NULL){
			if(p->link==NULL){
				previous->x=p->x;
				previous->y=p->y;
				previous->value=p->value;
			}
			Map[p->x][p->y]=48;
			x=p->x;
			y=p->y;
			value=p->value;
			p->x=temp->x;
			p->y=temp->y;
			p->value=temp->value;
			Map[p->x][p->y]=p->value;
			temp->x=x;
			temp->y=y;
			temp->value=value;
			p=p->link;	
		}
		if(check)					addTail(w,previous->x,previous->y);
		
	}
	else							die();
	
	system("cls");
	printMap();
}

void die(){											// 사망 함수
	system("cls");
	printf("\n\n\n\n\t\t\t You are die!!!\n\n\n\n");
	getchar();
	exit(1);										// 종료
}
void gameOver(int timer){							// 게임 종료 확인
	if(itemcount==0){								// 총 아이템 개수가 0개라면
		system("cls");								// 화면 초기화
		printf("\n\n\n\n\t\t\t You are Winner!!!\n\n\n\n");
		getchar();
		exit(1);									// 종료
	}
	if(timer>=150){									// 만약 시간이 다 되었다면 
		system("cls");
		printf("\n\n\n\n\t\t\t You are Loser!!!\n\n\n\n"); 
		exit(1);									// 종료
	}	
	printf("%d시간만큼이 남았습니다.",150-timer);	// 남은 시간 출력
	
}



int makeMap(int Map[width][height])					// 맵 생성
{
	FILE* fd;
	char buf[width*height*2];
	int i, j;
	int index=0;
	fd=fopen("map.txt","r");						// 파일 읽기
	fread(buf,sizeof(char),width*height*2,fd);
	for(i=0; i<width; i++){
		for(j=0; j<height; j++){
			Map[i][j]=buf[index++];
			while(buf[index]==10)	index++;
		}
		printf("\n");
	}
	return Map[width][height];
}
void printMap()										// 맵 출력
{
	int i, j;
	int a=1;
	for(i=0; i<width; i++){
		for(j=0; j<height; j++){
			if(Map[i][j]==48)		printf("　");	// 공백
			else if(Map[i][j]==54)	printf("＠");	// 아이템
			else if(Map[i][j]==49)	printf("■");	// 벽
			else if(Map[i][j]==55)	printf("○");	// 지렁이 몸
			else					printf("%d no",Map[i][j]);
		}			
		printf("\n");
	}
}