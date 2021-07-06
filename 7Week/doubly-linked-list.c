/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
 /* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
		 singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
		- initialize와 왜 다른지 이해 할것
		- 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	printf("2018038072  임상우\n");
	char command;
	int key;
	headNode* headnode = NULL;

	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {
	//h==main의 &headnode *h=headnode가 가리키는 Headnode형 변수의 주소 **h는 Headnode형 변수에 저장된 값

	if (*h != NULL) {		//헤드노드가 NULL이 아니라면
		freeList(*h);	//모두 할당해줌 
		//initialize는 h를 더블형포인터로 받았고, freeList는 싱글형 포인터로 받았기때문에
		//*h를 넘겨준다
	}

	headNode* temp = (headNode*)malloc(sizeof(headNode));		//temp headNode*로 동적할당

	(*h) = temp;			//더블형포인터로 받았기때문에 역참조*를 한번 해준다
	(*h)->first = NULL;	//만약 싱글형 포인터로 받았으면 h=temp, h->first=NULL;로 표현했을 것이다.



	return 1;
}

int freeList(headNode* h) {

	listNode* p = h->first;		//두개의 listNode형 포인터 선언
	listNode* prev = NULL;		//prev는 이전의 노드를 가리킴

	while (p != NULL) {		//p와 prev가 한칸씩 증가하며 free(prev를 해줌)	

		prev = p;
		p = p->rlink;		//p는 p의 rlink가 가리키는곳으로 이동 
		free(prev);
	}

	free(h);	//헤드노드도 할당해제해줌



	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;
	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	listNode* search = h->first;		//마지막노드를 찾을 변수

	if (!search) {		//첫번째 노드가 입력됐을때
		insertFirst(h, key);	//insertFirst()호출
		return 0;
	}


	while (search) {		//search가 NULL일때까지


		if (!(search->rlink)) {	//search의 rlink가 NULL이면 
								//밑에 search=search->rlink를 하므로써 마지막노드를 가리키지못하니까 탈출시켜준다
								//그러면 search에는 마지막노드를 가리키고 있는 상태다
			break;

		}
		search = search->rlink;
	}


	search->rlink = node;		//마지막노드뒤에삽입
	node->llink = search;
	node->rlink = NULL;



	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	listNode* search = h->first;

	if (!search) {			//노드가 0개일때 삭제하면
		printf("list is empty\n");	//에러메시지 출력
		return -1;	//비정상종료
	}

	if (search->rlink == NULL) {		//노드가 1개이면
		free(search);				//search할당해제후
		h->first = NULL;			//h->first NULL로 만들어줌
		return 0;
	}


	while (search) {		//마지막노드를 찾음

		if (!(search->rlink))
			break;

		search = search->rlink;
	}



	search->llink->rlink = NULL;	//search 이전노드의 rlink NULL
	free(search);	//free(search)


	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	if (!(h->first)) {		//첫번째로 노드가 들어올때
		h->first = node;		//헤드는 node를 가리키게하고
		node->llink = NULL;		//node의 llink는 invertList()때문에 NUll로 해준다
		node->rlink = NULL;		//node의 rlink는 null(처음이자 마지막노드임을 의미)
	}

	else {							//두번째 이후의 노드가 들어올때
		node->rlink = h->first;		//node의 rllink는 이전의 헤드였던 노드를 가리킴
		h->first->llink = node;		//이전의 헤드노드의 llink는 지금 들어온 node를 가리킴
		h->first = node;				//헤드는 지금 들어온 node를 가리킴
		node->llink = NULL;		//노드의 llink는 invertList()때문에 NULL로해준다
	}




	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	listNode* search = h->first;

	if (!search) {			//노드가 0개일때 삭제하면
		printf("list is empty\n");	//에러메시지 출력
		return -1;	//비정상종료
	}

	h->first = search->rlink;	//h->first는 search의 rlink를 가리키고
	h->first->llink = NULL;		//첫번째 노드의 llink는 NULL이되어야한다.
	free(search);	//free(search)

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	listNode* tail = NULL;
	listNode* middle = NULL;
	listNode* head = h->first;

	if (!head) {			//노드가 0개일때 
		printf("list is empty\n");	//에러메시지 출력
		return -1;	//비정상종료
	}

	while (1) {				//head가 마지막 노드를 가리키게한다
		if (head->rlink == NULL)
			break;

		head = head->rlink;
	}

	while (head) {	//head가 NULL일때까지
		tail = middle;	//tail과 middle과 head는 마지막노드부터 왼쪽으로 한 칸 씩 이동한다
		middle = head;
		head = head->llink;
		middle->llink = tail;	//middle의 llink와 rlink의 위치를 바꾼다
		middle->rlink = head;

		if (tail == NULL) {		//tail이 NULL일때는 middle이 마지막 노드를 가리키고있다
			h->first = middle;	//이때의 middle은 역순으로 출력되면 헤드이므로 middle이 한 칸 왼쪽으로 가기전에 헤드가 middle을 가리키게한다
		}
	}

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	listNode* search = h->first;
	listNode* prev = NULL;
	int checkpoint = 0;		//반복문 들어갔는지 체크하는변수

	if (!search) {		//한개의 노드도 없을때
		insertFirst(h, key);		//insertFirst()호출
		return 0;
	}

	if(!key){
		printf("key값 공백\n");
		return -1;
	}

	while (search->key <= key) {
		checkpoint = 1;
		if (!(search->rlink)) {		//key값이 최댓값일때는 search뒤에 노드 삽입
			node->llink = search;
			search->rlink = node;
			node->rlink = NULL;
			return 0;
		}

		prev = search;
		search = search->rlink;		//한칸씩증가
	}


	if (checkpoint == 0) {	//checkpoint가 0이라는 것은 반복문 안돔==최솟값이 들어옴
		insertFirst(h, key);	//insertFirst()호출
		return 0;
	}


	node->rlink = search;		//search와 prev사이에 노드 삽입
	node->llink = prev;
	prev->rlink = node;
	search->llink = node;



	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	listNode* search = h->first;
	listNode* node = (listNode*)malloc(sizeof(listNode));
	int checkpoint = 0;
	node->key = key;

	if (!search) {			//노드가 0개일때 삭제하면
		printf("list is empty\n");	//에러메시지 출력
		return -1;	//비정상종료
	}



	while (search->key != key) {		//key값이 있는지 찾는반복문
		checkpoint = 1;
		search = search->rlink;	//search는 한칸씩 증가

		if (search->rlink == NULL) {	//search가 마지막 노드일때

			if (search->key == key) {	//찾는 key값이 마지막노드였을때
				deleteLast(h);	//deleteLast()호출
				return 0;
			}
			else {		//찾는 key값이 마지막 노드가 아니었을때
				printf("cannot find the node for the key = %d\n", key);
				return 0;
			}
		}

	}


	if (checkpoint == 0) {	//반복문을 안들어갔으면 search->key==key 첫번째 노드에 찾는값이 있음
		deleteFirst(h);
		return 0;
	}

	//반복문을 들어갔으면
	search->llink->rlink = search->rlink;	//search의 이전노드와 이후노드를 연결시킴
	search->rlink->llink = search->llink;
	free(search);



	return 1;
}