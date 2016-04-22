#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define width 20									// ���� �� ����
#define height 20									// ���� �� ����
#define ITEM_COUNT 20								// ���ӿ����� �� �������� ����

typedef struct worm{								// ������ ���
	int x;
	int y;
	int value;
	struct worm* link;
}Worm;

typedef struct{										// ������ ���
	Worm* head;
}Worm_h;

int makeMap(int Map[width][height]);				// ���� ��, �� ����
void printMap();									// �� ���
int Map[width][height]={0};							// ���� �迭
void leftMove(Worm_h* p);							// ���� �̵�
void rightMove(Worm_h* p);							// ������ �̵�
void upMove(Worm_h* p);								// ���� �̵�
void downMove(Worm_h* p);							// �Ʒ��� �̵�
void gameOver(int timer);							// ���� �� Ȯ��
void die();
Worm_h* createHead(){								// ����Ʈ ��� ����
	Worm_h* w;
	w=(Worm_h*)malloc(sizeof(Worm_h));
	w->head=NULL;
	return w;
}


void addTail(Worm_h* w, int x, int y){				// ������ ���� �߰�
	Worm* newtail;
	Worm* p;
	newtail=(Worm*)malloc(sizeof(Worm));			// ���ο� ��� ����
	newtail->link=NULL;								// ���ο� ����� ��ũ�� Null�� ����
	if(w->head==NULL){								// ��尡 Null�̶��, ���ο� ��� �ֱ�
		newtail->x=10;								// ��ǥ ����
		newtail->y=10;								// ��ǥ ����
		newtail->value=55;
		Map[newtail->x][newtail->y]=55;				// �ش� ��ǥ�� ������ �� ǥ��
		w->head=newtail;
		return;
	}
	p=w->head;										// ��尡 �����Ѵٸ�, �ӽó�� p�� w->head�� ����Ų��,
	while(p->link!=NULL)		p=p->link;			// ����Ʈ�� ���� �����Ҷ����� �ݺ�
	newtail->value=55;
	newtail->x=x;
	newtail->y=y;
	Map[newtail->x][newtail->y]=newtail->value;		// �ش� ��ǥ�� ������ �� ǥ��
	p->link=newtail;								// ����Ʈ�� ���� ���ο� ����Ʈ ����
}

int itemcount=ITEM_COUNT;							// �������� ����
/*
Worm head;											// ����Ʈ�� ���
Worm tail;
int length=3;										// ���� ����
*/
void itemRand(){									// �������� �������� ������ش�.
	int i,x,y;
	srand(time(NULL));
	for(i=0; i<ITEM_COUNT; i++){
		x=rand()%18+1;								// x ��ǥ
		y=rand()%18+1;								// y ��ǥ 
		if(Map[x][y]==54)		i-=1;				// �ش� ��ǥ�� �������� �ִٸ� �ٽ� ����
		Map[x][y]=54;								// �ش� ��ǥ�� ������ ����
	}	
}

void main(){										// 0 : ���� 1 : ������ 2 : ���� 3 : �Ʒ��� 4 : ���� 
	int key;
	int direct=0;
	int timer=0;
	Worm_h* p;
	p=createHead();									// head ����
	makeMap(Map);									// ���� ����� �Լ�
	itemRand();										// ������ ���� ����
	addTail(p,10,10);								// �ʱ� ������ �� 3�� ����
	addTail(p,10,11);
	addTail(p,10,12);
	system("cls");									// ȭ�� ��ü �����
	printMap();										// �� ���

	key=getch();									// Ű����κ��� ���� ����
	if(key==224){									// ����Ű �ƽ�Ű �ڵ�� 224 XX
		key=getch();		
		while(1){
			Sleep(100);
			if(!kbhit()){							// Ű�� ������ �ʾ��� ���
				switch(direct){						// ���⿡ ���� �� �������� ��� ������
					case 0:
						leftMove(p);				// 0�� ���, �������� �̵�
 						gameOver(timer++);			// ���� ���� Ȯ��.
						break;
					case 1:
						rightMove(p);				// 1�� ���, ���������� �̵�.					
						gameOver(timer++);			// ���� ���� Ȯ��.
						break;
					case 2:
						upMove(p);					// 2�� ���, �������� �̵�
						gameOver(timer++);			// ���� ���� Ȯ��
						break;
					case 3:
						downMove(p);				// 3�� ���, �Ʒ������� �̵�
						gameOver(timer++);			// ���� ���� Ȯ��.
						break;
				}
			}
			else{									// Ű�� ������ �ִٸ�.
				key=getch(); 
				if(key==224){						// ����Ű���
					key=getch();					// �ι�° �ƽ�Ű�ڵ带 �޴´�.
					
					switch(key){					// �ش� Ű���� Ȯ��
						case 75:					// ����
							if(direct==1)	break;	// ���������� �̵���, ���� �̵� �Ұ�
							direct=0;					
							break;
						case 77:					// ������
							if(direct==0)	break;	// ���� �̵���, ������ �̵� �Ұ�
							direct=1;
							break;
						case 72:					// ��
							if(direct==3)	break;	// �Ʒ��� �̵� ��, ���� �̵� �Ұ�
							direct=2;									
							break;
						case 80:					// �Ʒ� 
							if(direct==2)	break;	// ���� �̵� ��, �Ʒ��� �̵� �Ұ�
							direct=3;
							break;
					}
				}
				system("cls");						// ȭ�� �����
				printMap();							// ȭ�� ���
				fflush(stdin);						// �Է� ���� �ʱ�ȭ
			}
		}
	}	
}



void leftMove(Worm_h* w)							// �������� �����̴� �Լ�
{
	Worm* temp;										// ���� ��ġ ������ �ӽ� ���
	Worm* p;										// ����Ʈ ����ų �ӽ� ���
	Worm* previous;									// ���� ����Ʈ�� ������ ��带 ����Ų ����
	boolean check;									// ������ ������ Ȯ������ ����( 1�� true, 0�� false )
	int x, y, value;								// temp�� ����, �ӽ� �������� ����
	temp=(Worm*)malloc(sizeof(Worm));				// �ӽ� ��� �����Ҵ�.
	previous=(Worm*)malloc(sizeof(Worm));			// �ӽ� ��� �����Ҵ�.
	p=w->head;										// ����Ʈ ����Ű�� �ӽó�尡 ����� ����Ų��.
	temp->x=p->x;									// ����� �����͸� ��ġ ������ �ӽ� ��忡 ����.
	temp->y=p->y;
	temp->value=p->value;
	p->y-=1;										// ����� ��ġ�� �������� ��ĭ �̵�.
	if(p->y!=0){									// ���� �ִ� ���� �ƴ϶��,
		if(Map[p->x][p->y]==55)		die();			// �ڽ��� ���̶��, �ױ�
		if(Map[p->x][p->y]==54){					// ������ ��ġ���
			itemcount--;							// ��ü ������ �� 1�� ����
			check=1;								// check�� ���� ������ ������ ����
		}
		else						check=0;		// ������ ��ġ�� �ƴ϶��, check�� ���� ������ ���� ������ ����
		Map[p->x][p->y]=p->value;					// �� ���� ������ ��尪�� �־�, �����ΰ� ó�� ǥ��
		p=p->link;									// p�� ���� ��ũ�� �̵�.
		while(p!=NULL){								// ����Ʈ�� ���� �ɶ����� Ȯ��
			if(p->link==NULL){						// ������ �����, ������ ��忡 ���� ������ �����Ѵ� ( ����, ���� �߰� �� ��� )
				previous->x=p->x;
				previous->y=p->y;
				previous->value=p->value;
			}
			Map[p->x][p->y]=48;						// �ش� �ڸ���, �������� ä���.
			x=p->x;									// �� �ڸ� ����
			y=p->y;									// �� �ڸ� ����
			value=p->value;							// �� �ڸ��� ���� �� ����
			p->x=temp->x;							// �ڽ��� ������尡 ��ġ�ߴ� ������ �̵�
			p->y=temp->y;							// �ڽ��� ������尡 ��ġ�ߴ� ������ �̵�
			p->value=temp->value;					// �ڽ��� ������尡 ������ �ִ� ���� ����
			Map[p->x][p->y]=p->value;				// �ʿ� �ڽ��� ���� ���� ����
			temp->x=x;								// �� �ڸ��� ���� ��ġ ���尪��, Temp��� �ӽ� ��忡 ����
			temp->y=y;								// �� �ڸ��� ���� ��ġ ���尪��, Temp��� �ӽ� ��忡 ����
			temp->value=value;						// �� �ڸ��� ���� ����, Temp��� �ӽ� ��忡 ����
			p=p->link;								// ���� ���� �̵�
			/*
													�ڽ��� ��ġ�� ���� ��忡�� �ΰ�.
			*/
		}
		if(check)									// �������� ȹ�� ���� ��,
			addTail(w,previous->x,previous->y);		// ���ο� ���� ������ ��忡 ���� ������ �Է��Ѵ�.

	}
	else							die();			// ����� �ű���ġ�� ���̾��ٸ�, ���� ��
	system("cls");									// ȭ�� �����
	printMap();										// ȭ�� ���
}

void rightMove(Worm_h* w){							// ���� ���� ����
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

void die(){											// ��� �Լ�
	system("cls");
	printf("\n\n\n\n\t\t\t You are die!!!\n\n\n\n");
	getchar();
	exit(1);										// ����
}
void gameOver(int timer){							// ���� ���� Ȯ��
	if(itemcount==0){								// �� ������ ������ 0�����
		system("cls");								// ȭ�� �ʱ�ȭ
		printf("\n\n\n\n\t\t\t You are Winner!!!\n\n\n\n");
		getchar();
		exit(1);									// ����
	}
	if(timer>=150){									// ���� �ð��� �� �Ǿ��ٸ� 
		system("cls");
		printf("\n\n\n\n\t\t\t You are Loser!!!\n\n\n\n"); 
		exit(1);									// ����
	}	
	printf("%d�ð���ŭ�� ���ҽ��ϴ�.",150-timer);	// ���� �ð� ���
	
}



int makeMap(int Map[width][height])					// �� ����
{
	FILE* fd;
	char buf[width*height*2];
	int i, j;
	int index=0;
	fd=fopen("map.txt","r");						// ���� �б�
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
void printMap()										// �� ���
{
	int i, j;
	int a=1;
	for(i=0; i<width; i++){
		for(j=0; j<height; j++){
			if(Map[i][j]==48)		printf("��");	// ����
			else if(Map[i][j]==54)	printf("��");	// ������
			else if(Map[i][j]==49)	printf("��");	// ��
			else if(Map[i][j]==55)	printf("��");	// ������ ��
			else					printf("%d no",Map[i][j]);
		}			
		printf("\n");
	}
}