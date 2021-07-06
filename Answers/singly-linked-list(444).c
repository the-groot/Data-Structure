#include <stdio.h>
#include <stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node
{
	int key;
	struct Node *link;
} listNode;

typedef struct first
{
	struct Node *first;
} firstNode;

/* 함수 리스트 */
firstNode *initialize(firstNode *h);
int freeList(firstNode *h);

int insertFirst(firstNode *h, int key);
int insertNode(firstNode *h, int key);
int insertLast(firstNode *h, int key);

int deleteFirst(firstNode *h);
int deleteNode(firstNode *h, int key);
int deleteLast(firstNode *h);

int invertList(firstNode *h);

void printList(firstNode *h);

int main()
{
	
	char command;
	int key;
	firstNode *firstnode = NULL;

	do
	{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command)
		{
		case 'z':
		case 'Z': //z를 입력 받으면 노드를 초기화한다.
			firstnode = initialize(firstnode);
			break;
		case 'p':
		case 'P': //p를 입력받으면 노드를 출력한다
			printList(firstnode);
			break;
		case 'i':
		case 'I': //i를 입력받으면 노드를 추가한다.
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(firstnode, key);
			break;
		case 'd':
		case 'D': //d를 입력받으면 노드를 삭제한다.
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(firstnode, key);
			break;
		case 'n':
		case 'N': //n을 입력받으면 Last에 추가한다.
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(firstnode, key);
			break;
		case 'e':
		case 'E': //e를 입력받으면 Last를 삭제한다.
			deleteLast(firstnode);
			break;
		case 'f':
		case 'F': //f를 입력받으면 First를 추가한다.
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(firstnode, key);
			break;
		case 't':
		case 'T': //t를 입력받으면 First를 제거한다.
			deleteFirst(firstnode);
			break;
		case 'r':
		case 'R': //r를 입력받으면 리스트의 링크를 역순으로 한다.
			invertList(firstnode);
			break;
		case 'q':
		case 'Q': //q를 입력받으면 할당된 메모리를 해제한다.
			freeList(firstnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

firstNode *initialize(firstNode *h)
{

	/* firstNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (h != NULL) //전달받은 h가
		freeList(h);

	/* firstNode에 대한 메모리를 할당하여 리턴 */
	firstNode *temp = (firstNode *)malloc(sizeof(firstNode));
	temp->first = NULL;
	return temp;
}

int freeList(firstNode *h)
{
	/* h와 연결된 listNode 메모리 해제
	 * firstNode도 해제되어야 함.
	 */
	listNode *p = h->first;

	listNode *prev = NULL;
	while (p != NULL)
	{
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(firstNode *h, int key)
{

	listNode *node = (listNode *)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(firstNode *h, int key)
{

	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(firstNode *h, int key)
{

	listNode *node = (listNode *)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	listNode *n = h->first;
	while (n->link != NULL)
	{
		n = n->link;
	}
	n->link = node;
	return 0;
	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(firstNode *h)
{
	listNode *p = h->first;
	if (h->first == NULL)
		return 0;
	if (h->first->link == NULL)
	{
		free(h->first);
		h->first = NULL;
		return 0;
	}
	else
	{
		h->first = p->link;
		free(p);
	}
	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(firstNode *h, int key)
{
/*
	listNode *pre;		  //삭제할 노드의 선행자 노드를 나타낼 포인터
	if (h->first == NULL) //공백리스트면 중단
		return;
	if (h->first->link == NULL) //리스트에 노드가 하나만 있으면
	{
		free(h->first);
		h->first = NULL;
		return;
	}

	else if (key == NULL) // 삭제할 노드가 없으면
		return;

	else
	{
		pre = h->first; //삭제할 노드 key의 선행자 노드를 포인터 pre를 이용해 찾는다
		while (pre->key != key)
		{
			pre = pre->link;
		}

		pre->link = key->link;
		free(key);

		return 0;
		*/
	}

	/**
 * list의 마지막 노드 삭제
 */
	int deleteLast(firstNode * h)
	{
		listNode *p;
		listNode *c;

		if (h->first == NULL)
			return 0;
		if (h->first->link == NULL)
		{
			free(h->first);
			h->first = NULL;
			return 0;
		}
		else
		{
			p = h->first;
			c = h->first->link;
			while (c->link != NULL)
			{
				p = c;
				c = c->link;
			}
			free(c);
			p->link = NULL;
		}

		return 0;
	}

	/**
 * 리스트의 링크를 역순으로 재 배치
 */
	int invertList(firstNode * h)
	{

		return 0;
	}

	void printList(firstNode * h)
	{
		int i = 0;
		listNode *p;

		printf("\n---PRINT\n");

		if (h == NULL)
		{
			printf("Nothing to print....\n");
			return;
		}

		p = h->first;

		while (p != NULL)
		{
			printf("[ [%d]=%d ] ", i, p->key);
			p = p->link;
			i++;
		}

		printf("  items = %d\n", i);
	}
