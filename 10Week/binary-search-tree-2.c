/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node* left;
	struct node* right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL;
	printf("[2018038072 임상우]\n");

	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if (ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224s
 */
void iterativeInorder(Node* node)       //강의자료참고
{
	top = -1;
	for (int i = 0; i < MAX_STACK_SIZE; i++) {		//호출될때마다 스택을 NULL로 초기화
		stack[i] = NULL;
	}

	for (; ;) {
		for (; node; node = node->left) {      //처음에 자기자신을 push하고 왼쪽노드로 계속 가면서 push해줌 (L)
			push(node);
		}
		node = pop();     //스택에 저장된 노드하나를 불러들여서
		if (!node)       //스택에 저장된 값이 없을때(모든 노드를 출력했을때)
			break;          //탈출
		printf("[%d]  ", node->key);     //pop한 노드 출력 (V)

		node = node->right;       //지금의 노드는 pop한 노드의 위치에 있으므로 오른쪽 방문을 해줌
								//그러면 오른쪽자식의 노드는 또 위의 반복문을 돌며 왼쪽자식노드들을 push해주고
								//가장 마지막에 push돼있는 노드를 pop해 출력하고 오른쪽자식으로 만약 리프노드이면(LVR이 끝나면)
								//상위레벨의 노드의 VR을 해줌 
	}
}

Node* pop()
{
	if (top == -1) {        //top이 -1이라는 것은 스택이 비었다는 것이므로 NULL을 리턴해준다
						//NULL을 리턴해주면 iterativeInorder는 종료된다.
		return NULL;
	}
	return stack[top--];    //top이 -1이아니면 stack[top]이 가리키고 있는 Node의 주소를 리턴해준다
}

void push(Node* aNode)
{
	if (top == 19) {                //top이 19이면 stack이 꽉찼으므로 스택에 저장못시키게한다.
		printf("stack is full\n");
		return;
	}

	stack[++top] = aNode;     //aNode를 stack[++top]에 저장시킨다.(stack[++top]이 aNode를 가리키고있다.)
}


/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	front = -1, rear = -1;
	for (int i = 0; i < MAX_QUEUE_SIZE; i++) {	//levelOrder가 여러번 호출될때 혹시 큐에 남아있는 정보가 있을 것을 방지하기위해
		queue[i] = NULL;						//queue를 NULL로 초기화해준다
	}

	enQueue(ptr);		//큐에 루트노드를 하나 넣어놓음

	for (; ;) {
		ptr = deQueue(ptr);		//큐에 저장된 노드를 하나 받고
		if (ptr) {				//ptr이 NULL이면(큐에 저장된 값이 없을때) 탈출
			printf("[%d]  ", ptr->key);		//노드의 KEY값을 출력한 후
			if (ptr->left)					//왼쪽자식노드 있으면 큐에삽입
				enQueue(ptr->left);
			if (ptr->right)					//오른쪽 자식노드 있으면 큐에삽입
				enQueue(ptr->right);
		}
		else break;

	}
}

Node* deQueue()
{
	if (front == MAX_QUEUE_SIZE - 1 || front==rear)		// MAX_QUEUE-SIZE를 넘어가는 것을 방지
		return NULL;					//front가 마지막 인덱스라면 더이상 pop할게없으므로 NULL반환

	return queue[++front];				//queue[++front]반환
}

void enQueue(Node* aNode)
{
	if (rear == MAX_QUEUE_SIZE - 1) {			// MAX_QUEUE-SIZE를 넘어가는 것을 방지
		printf("queue is full\n");			// 큐에 입력하지 않고 
		return;								//종료시킴
	}


	queue[++rear] = aNode;				//queue[++rear]이 aNode를 가리키도록함
}




int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while (ptr != NULL) {

		/* if there is a node for the key, then just return */
		if (ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if (ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if (parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{


	if (!head) {
		printf("head is empty\n");
		return 0;
	}

	Node* delete = NULL;	//삭제할 key값을 가진 노드의 주소를 받아온다.
	Node* prev = NULL;	//삭제할 노드의 부모노드의 주소
	Node* small = NULL;	//삭제할 노드의 오른쪽 서브트리의 최솟값 노드
	Node* temp = NULL;	//삭제할 노드의 주소를 임시로 받음
	int childnode = 0;	//삭제하고자하는 노드의 자식노드가 몇개인지 세는 변수(0,1,2중 하나)
	temp = head->left;

	while (temp) {			
							//여기서 삭제할 노드의 위치를 구한다
		if (key == temp->key)
			break;
		if (key < temp->key) {
			prev = temp;
			temp = temp->left;
		}
		else {
			prev = temp;
			temp = temp->right;
		}
	}

	delete = temp;	//삭제할 노드의 주소를 받음

	if (!delete) {	//삭제할 key값의 노드가 존재하지 않는다면
		printf("\n Cannot find the node [%d]\n", key);
		return 0;
	}

	if (delete->right != NULL)		//삭제할노드의 자식노드가 몇개인지 카운트
		++childnode;
	if (delete->left != NULL)
		++childnode;


	switch (childnode) {		//자식노드의 개수에따라 분류해서 구현

	case 0: {		//자식노드가 0개일때
		if (!prev) {	//삭제하는 노드가 루트노드일때(prev는 삭제하고자하는 노드의 부모노드이기때문에 delete가 루트노드일때 prev는 NULL이다)
			head->left = NULL;		//헤드의 left NULL
			free(delete);			//delete할당해제
			break;
		}
		if (delete->key <= prev->key) {	//delete가 prev의 왼쪽자식이면
			free(delete);			//delete할당해제 및
			prev->left = NULL;		//prev의 왼쪽노드 NULL
		}
		else {					//delete가 prev의 오른쪽 자식이면
			free(delete);			//delete할당해제 및
			prev->right = NULL;		//prev의 오른쪽노드 NULL
		}
		break;
	}

	case 1: {			//자식노드가 1개일때
		if (!prev) {	//삭제하는 노드가 루트노드일때
			if (delete->left != NULL) { 	//자식이 왼쪽에있을때
				head->left = delete->left;		//헤드의 left가 delete의 자식을가리키게함
				delete->left = NULL;
			}
			else {      //자식이 오른쪽에 있을때
				head->left = delete->right;		//헤드의 left가 delete의 자식을 가리키게함
				delete->right = NULL;
			}
			free(delete);
			break;
		}

		if (delete->left != NULL) {	//자식이 왼쪽에 있을때
			if (prev->key > delete->key)	//prev의 key값이 delete key값보다크면
				prev->left = delete->left;	//prev left에 delete의 자식노드삽입
			else                            //prev의 key값이 delete key값보다 작거나같으면
				prev->right = delete->left;	//prev의 right에 delete의 자식노드삽입
			delete->left = NULL;	//자식과의 링크를 끊고
			free(delete);		//delete 할당해제해준다
		}

		else {		//자식이 오른쪽에 있을때
			if (prev->key > delete->key)	//prev의 key값이 delete key값보다크면
				prev->left = delete->right;	//prev left에 delete의 자식노드삽입
			else                            //prev의 key값이 delete key값보다 작거나같으면
				prev->right = delete->right;	//prev의 right에 delete의 자식노드삽입
			delete->right = NULL;	//자식과의 링크를 끊고
			free(delete);		//delete 할당해제해준다
		}
		break;
	}

	case 2: {	//자식노드가 두개일때
		Node* small_parent = NULL;	//small의 부모노드
		int small_child = 0;			//small노드의 자식노드 세는 변수(0개 혹은 1개)
		small = delete->right;			//small은 delete의 오른쪽 서브트리의 최솟값이므로 오른쪽자식으로 한 번 가고

		while (small->left!=NULL) {		//그중에서 가장 작은값이 small이 된다.
			small_parent = small;
			small = small->left;
		}

		if (small->right)		//small은 가장 높은 레벨의 왼쪽자식이므로 왼쪽자식이 존재할 순 없고
									//오른쪽자식이 존재하냐 아니냐에따라 다르게 구현해야하므로 small 자식 개수를 구해준다
			++small_child;



		if (!prev) {					//루트노드를 삭제할때		

			if (small_child == 0) {	//small이 리프노드일때
				if (small_parent)		//small_parent가 존재하면
					small_parent->left = NULL;	//small이 delete자리로 갈거기때문에 
												//이제 자식노드가 아니므로 연결해제
			}
			else {	//small의 자식노드가 존재할때(오른쪽 자식 한개만 존재할 것임)		
				if (small_parent)									//small노드의 오른쪽자식이 존재할때 오른쪽자식은 small노드의 위치로 올려줘야한다
					small_parent->left = small->right;	//오른쪽 서브트리의 최솟값이기때문에
														//small의 parent의 left에 small의 오른쪽자식이 들어간다.
														//만약 왼쪽서브트리의 최댓값이었으면 parent right에 왼쪽자식이 들어갔을것이다.
			}
			head->left= small;		//small이 이제 루트노드
		}

		else {		//삭제하고자하는 노드가 루트노드가 아닐때

			if (prev->key > delete->key) {	//prev의 key값이 delete의 key값보다 크면 delete는 prev의 왼쪽자식이므로
				prev->left = small;			//prev의 left는 이제 small을가리킴
			}
			else {						//반대의 경우에는
				prev->right = small;	//prev의 right는 small을 가리킴
			}

			if (small_child == 0) {		//small의 자식노드가 0개일때
				if (small_parent)		//small_parent가 NULL이아니면
					small_parent->left = NULL;	//small_parent의 자식은 이제 없으므로 NULL	
			}

			else {				
				if(small_parent!=NULL)					//자식노드가 1개일때
				small_parent->left = small->right;	//small_parent의 자식을 small의 자식노드로 변경
			}
		}
		if(small!=delete->left)			//insertnode 30,5,40했을때 delete(30)을하면
										//small(40)과 delete->right(40)이 같은경우가 생겨
										//cycle이 생기는 경우가 있어 small과 delete->left or delete->right이 같지 않을때만 하도록구현
		small->left = delete->left;		
		if(small!=delete->right)
		small->right = delete->right;//small은 delete가 가리키던 링크를 그대로 가리키고
		delete->left = NULL, delete->right = NULL;	//delete의 자식노드들을 잘라내고
		free(delete);		//delete할당해제

		break;
	}


	}

	return 0;


}


void freeNode(Node* ptr)
{
	if (ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if (head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}








