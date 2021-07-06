/*
 * circularQ.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();		//queue배열 동적할당 하는 함수
int freeQueue(QueueType *cQ);	//동적할당 해제하는 함수
int isEmpty(QueueType *cQ);		//큐 배열이 꽉 찼을때 호출하는 함수
int isFull(QueueType *cQ);		//큐 배열이 비었을때 호출하는 함수
void enQueue(QueueType *cQ, element item);	//큐의 element를 하나 추가하는 함수
void deQueue(QueueType *cQ, element* item);	//큐의 element를 하나 제거하는 함수
void printQ(QueueType *cQ);	//큐의 요소들을 출력하는 함수
void debugQ(QueueType *cQ);	//큐의 front,rear 및 요소들 등 현재 상태를 출력하는 함수
element getElement();	//element를 입력받는 함수


int main(void)
{
	printf("[임상우]    [2018038072]\n");
	QueueType *cQ = createQueue();	//QueueType 형 포인터 cQ선언 및 CreateQueue함수 호출
	element data;	//요소를 저장하기 위한 변수
	char command;  // 메뉴에서 사용자의 입력을 받는 변수

	if(cQ==NULL){		
		return -1;	//비정상종료
	}

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);		//i는 데이터입력
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);		//d는 데이터제거
			break;
		case 'p': case 'P':
			printQ(cQ);		//p는 요소들 출력
			break;
		case 'b': case 'B':
			debugQ(cQ);		//b는 현재상태 출력
			break;
		case 'q': case 'Q':
   	        freeQueue(cQ);	//q는 cQ의 동적할당 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');	//q누르면 반복문 탈출


	return 1;
}

QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));	//동적할당하고
	cQ->front = 0;
	cQ->rear = 0;		//front와 rear 0으로 초기화
	return cQ;	//cQ 리턴
}

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;	//CQ가 null인지 확인
    free(cQ);		//CQ 동적할당 해제
    return 1;
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);		//요소 입력받음
	return item;
}


/* complete the function */
int isEmpty(QueueType *cQ)
{	
	if(cQ==NULL){		
		return -1;	//비정상종료
	}


	printf("circular Queue is Empty\n");		//큐가 비었다는 것을 출력해줌
    return 0;
}

/* complete the function */
int isFull(QueueType *cQ)
{
	if(cQ==NULL){
		return -1;		//비정상종료
	}

	printf("circular Queue is Full!\n");
	
   return -1;		//비정상종료
}


/* complete the function */
void enQueue(QueueType *cQ, element item)
{	


	int errorcode=0;	//비정상종료인지 아닌지 체크하는 변수

	if((cQ->rear+1)%MAX_QUEUE_SIZE==cQ->front){		//모듈러연산으로 rear이 증가했을때 front와 같은지 확인하고
		errorcode=isFull(cQ);		//같으면 isFull호출해 에러코드를 받고
	}

	if(errorcode==0){			//에러코드가 변했으면 이 조건문을 실행하지않고(front를 침범하면안되기때문에)
	cQ->rear=(cQ->rear+1)%MAX_QUEUE_SIZE;	//에러코드가 변하지않았으면 rear를 증가시키고
	cQ->queue[cQ->rear]=item;		//queue 배열의 rear인덱스 값에 item을 저장한다.
	}
	
}

/* complete the function */
void deQueue(QueueType *cQ, element *item)
{	
	if(cQ->front==cQ->rear) {	//deque가 왔을때 front와 rear이 같으면 배열이 비어있다는 것이기때문에
		isEmpty(cQ);	//isEmpty호출
	}

	cQ->front=(cQ->front+1)%MAX_QUEUE_SIZE;		//front도 모듈러연산으로 증가시키고
	cQ->queue[cQ->front]=NULL;		//queue배열의 front인덱스 값에 저장된 값을 null로 없애준다.
	
	
    
}


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);		//queue 배열을 first부터 last까지 출력해준다
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);			//i==front 일때는 front라고 출력
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);	//queue에 저장된 값출력


	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);	//front값,rear값 출력
}

