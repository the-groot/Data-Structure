#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
	int key;
	struct node* leftChild;
	struct node* rightChild;

}Node;

void CreatHeadNode(Node** h);		//헤드노드를 생성하는 함수(헤드노드는 루트노드를가리키는 노드)
int InsertNode(Node*, int);			//트리구조로 삽입하는 함수
int freeBST(Node*);					//동적할당한 노드들을 해제하는 함수
Node* SearchIterative(Node*, int);	//반복문형태로 key값을 search하는 함수
void inorderTraversal(Node* ptr);	//inorderTraversal(recursive)형태로 트리를 탐색및출력하는함수(main에서는 주석처리해놓음)
Node* searchRecursive(Node*, int);

void CreateHeadNode(Node** h) {

	(*h) = (Node*)malloc(sizeof(Node));
	(*h)->key = -9999;
	(*h)->leftChild = NULL;				//헤드노드 키값은 -9999, rightChild는 자신을 가리킴 leftChild는 NULL 
	(*h)->rightChild = (*h);


}

Node* searchRecursive(Node* ptr, int key)
{								//강의자료 참고 후 동일하게 구현
	if (!ptr) return NULL;
	if (key == ptr->key) return ptr;
	if (key < ptr->key)
		return searchRecursive(ptr->leftChild, key);
	return searchRecursive(ptr->rightChild, key);
}

int InsertNode(Node* head, int key) {			//삽입노드함수
	Node* search = NULL;		//삽입될 위치를 찾는 포인터

	Node* node = (Node*)malloc(sizeof(Node));			//삽입될 노드 동적할당
	node->leftChild = NULL;
	node->rightChild = NULL;
	node->key = key;

	search = head->leftChild;

	if (!head) {		//헤드 노드가 생성이 안됐으면
		printf("head is empty\n");	//경고문구 출력 후
		return 0;		//종료
	}

	if (!(search)) {	//루트노드를 삽입할때
		head->leftChild = node;		//헤드의 left는 node를 가리킴
		return 0;
	}

	while (1) {	//루트노드 이외의 노드를 삽입할때

		if (search->key < key) {	//삽입될 키가 더 크면

			if (!(search->rightChild))	//삽입될 위치를 찾으면
			{
				search->rightChild = node;	//search의 오른쪽자식에 node삽입
				return 0;
			}
			search = search->rightChild;	//오른쪽 자식으로간다.

		}

		else {		//삽입될 키가 더 작으면

			if (!(search->leftChild)) {	//삽입될 위치를 찾으면
				search->leftChild = node; //search의 왼쪽자식에 node삽입
				return 0;
			}

			search = search->leftChild; //왼쪽자식으로 간다

		}
	}
	return 0;
}


Node* SearchIterative(Node* head, int key) {

	while (head) {
		if (head->key == key)
			return head;;
		if (head->key < key)
			head = head->rightChild;
		else
			head = head->leftChild;
	}
	return NULL;

}

void inorderTraversal(Node* ptr)
{


	if (ptr) {			//강의자료와 동일하게 구현 Recursive
		inorderTraversal(ptr->leftChild);
		printf("[%d]  ", ptr->key);
		inorderTraversal(ptr->rightChild);
	}
}

int freeBST(Node* head)
{

	if (head) {	//postorder방식으로 free구현
		freeBST(head->leftChild);
		freeBST(head->rightChild);
		free(head);
	}

	return 0;
}


int main(void)
{

	Node* head = NULL;	//루트노드를 가리킬 헤드노드 선언
	Node* result = NULL;
	int user_input;
	CreateHeadNode(&head);	//헤드노드 생성
	FILE* pFile = fopen("test.txt", "r"); //read mode 
	int intTemp = -1;

	if (pFile == NULL)
	{
		printf("File does not exist");
		return 0;
	}


	// 파일 읽기 성공
	while (1) {
		fscanf(pFile, "%d", &intTemp);
		if (intTemp < 0) break;
		// 트리생성
		InsertNode(head, intTemp);
	}


	//파일 형태로 반환


	fclose(pFile);          //close file

	// 생성된 트리에서 키 검색
	printf("검색할 key값 입력:");
	scanf("%d", &user_input);

	result = SearchIterative(head->leftChild, user_input);
	if (result)
		printf("\n node [%d] found at %p\n", result->key, result);
	else
		printf("\n Cannot find the node [%d]\n", user_input);

	//inorderTraversal(head->leftChild);
	freeBST(head->leftChild);		//노드 동적할당 해제
	return 0;
}