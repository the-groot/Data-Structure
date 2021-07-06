/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *

 */



#include<stdio.h>
#include<stdlib.h>
 /* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	printf("[2018038072 임상우]\n");
	char command;
	int key;
	listNode* headnode = NULL;

	do {
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h) {

	if (h == NULL) {
		printf("Nothing to free....\n");
		return 1;
	}

	listNode* p = h->rlink;   //p는 rlink를 가리킴(노드가 하나면 다시 h를가리키고 노드가 두개 이상이면 두번째 노드를 가리킴)
	listNode* pre = NULL;



	while (p != NULL && p != h) {     //첫번째 노드를 제외한 노드들을 순차적으로 할당해제한다
		pre = p;                  //만약 노드가 하나밖에없으면 이 반복문을 들어오지않는다.
		p = p->rlink;
		free(pre);
	}

	free(h);        //첫번째 노드를 할당해제한다

	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

	if (h == NULL) {
		printf("h is NULL\n");
		return 1;
	}

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	listNode* p = h->rlink;


	while (p != NULL && p->rlink != h) {		//p가 마지막노드를 가리키게함
		p = p->rlink;
	}

	node->llink = p;		//새로운 노드의 llink는 이전의 마지막 노드를 가리키게함
	node->rlink = h;		//새로운 노드는 마지막노드가 되기위해 rlink가 헤드노드를 가리킴
	p->rlink = node;		//마지막노드의 rlink는 새로운 노드를 가리키게함
	h->llink = node;		//헤드노드의 llink는 마지막노드를 가리킴



	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

	if (h == NULL) {
		printf("h is empty\n");
		return 1;
	}

	listNode* p = h->rlink;

	if (p == h) {
		printf("There is nothing to delete\n");
		return 1;
	}

	while (p->rlink != h) {		//마지막노드까지 p가 감
		p = p->rlink;
	}




	p->llink->rlink = h;	//p의 이전노드의 rlink는 헤드노드를가리키고
	h->llink = p->llink;	//h의 llink는 p의 이전노드를 가리킨다
	p->llink = NULL;		//p의 llink와 rlink를 NULL로 하는 이유는 혹시모를 누수를 방지하기위함이다
	p->rlink = NULL;
	free(p);			//그러고 p할당해제




	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

	if (h == NULL) {
		printf("h is NULL\n");
		return 1;
	}

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	listNode* p = h;

	if (h->rlink == h) {	//노드가 한 개도 없을때
		h->rlink = node;	//각각의 rlink, llink를 서로 연결
		node->llink = h;
		node->rlink = h;
		h->llink = node;
	}

	else {		//노드가 한 개 이상인 경우는
		node->rlink = h->rlink;		//헤드노드 뒤에 삽입
		h->rlink->llink = node;
		h->rlink = node;
		node->llink = h;
	}



	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	if (h == NULL) {
		printf("h is empty\n");
		return 1;
	}

	listNode* p = h->rlink;

	if (p == h) {
		printf("There is nothing to delete\n");
		return 1;
	}

	else {
		h->rlink = p->rlink;
		p->rlink->llink = h;
		p->llink = NULL;
		p->rlink = NULL;
		free(p);
	}




	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
	if (h == NULL) {
		printf("h is NULLt\n");
		return 1;
	}

	if (h == h->rlink) {	//헤드노드 한 개 밖에 없을때
		printf("There is nothing to invert\n");
		return 0;
	}

	listNode* head = h->llink;
	listNode* middle = h;
	listNode* tail = NULL;

	if (h->llink == h) {	//노드가 2개일때(헤드노드 포함)
		return 0;			//뒤집어도 동일하므로 return
	}



	while (head != h) {		//헤드가 h올때까지
		tail = middle;		//한칸씩증가하고
		middle = head;
		head = head->llink;
		tail->rlink = middle;	//tail의 rlink가 middle
		middle->llink = tail;	//middle의 llink가 tail을 가리키게함
	}
	middle->rlink = head;	//마지막에 head가 다시 h가되었을때 middle이 마지막노드가 되므로 middle의 rlink는 head를 가리키고
	head->llink = middle;	//head의 llink는 middle을 가리킨다.
		
		
	return 0;
}



/**
 *  리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
 **/
int insertNode(listNode* h, int key) {

	if (h == NULL) {
		printf("h is NULL\n");
		return 1;
	}
	int checkcode = 0;
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	listNode* p = h->rlink;
	if (p == h) {			//노드가 한개도 없을때 insertFirst()호출
		insertFirst(h, key);
		return 0;
	}

	while (p->key <= node->key) {		//node->key값 보다 p->key가 클때까지
		checkcode = 1;

		if (p->rlink == h) {	//마지막 노드일때 
			if (p->key > node->key) {	//마지막 노드 앞에 삽입된다면
				break;	//반복문 탈출
			}
			else {		//마지막노드 뒤에 삽입된다면
				insertLast(h, key);	//insertLast 호출
				return 0;
			}
		}

		p = p->rlink;	//한칸씩증가
	}

	if (checkcode == 0) {	//node->key가 최솟값일때
		insertFirst(h, key);
	}

	else {				//node->key가 최솟값도 아니고, 마지막 노드 뒤에 삽입될때도 아닐때(중간에 삽일될때)
		node->rlink = p;
		node->llink = p->llink;
		p->llink->rlink = node;		//p의 이전노드의 rlink가 노드를가리킴
		p->llink = node;				//p의 llink가 node를 가리킴
	}


	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	int nodecount = 1;	//헤드노드를 제외한 노드개수의 수 세는 변수

	if (h == NULL) {
		printf("h is empty\n");
		return 1;
	}
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	listNode* p = h->rlink;


	if (p == h) {
		printf("There is nothing to delete\n");
		return 1;
	}

	while (p->key != node->key) {
		if (p->rlink == h) {	//마지막 노드까지 왔을때 값을 찾았을 경우와 못찾았을 경우로 나눈다
			if (p->key == node->key) {	//찾았을 경우 
				deleteLast(h);		//deleteLast() 호출
				return 0;
			}
			else {		//못찾았을 경우
				printf("There is not %d in list\n", node->key);	//오류문구 출력
				return 1;
			}

		}

		p = p->rlink;
		nodecount++;
	}

	if (nodecount == 1) {	//삭제할 노드가 첫번째 일때
		deleteFirst(h);
	}

	else {		//삭제할 노드가 첫번째도 마지막도 아닌 노드일때

		p->llink->rlink = p->rlink;
		p->rlink->llink = p->llink;
		p->llink = NULL;
		p->rlink = NULL;
		free(p);

	}



	return 0;
}



