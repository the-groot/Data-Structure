/*
 *
 *
 *  Graph Search
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>

typedef struct node {	//노드 구조체
	int key;
	struct node* link;			//key값과 링크를 가진다
}Node;

#define MAX_VERTEX_NUM 10
Node vertex[MAX_VERTEX_NUM];		//Node형 배열 vertex[i]->link로 vertex의 존재유무를 판단할 것임
char edge_check[MAX_VERTEX_NUM][MAX_VERTEX_NUM] = { 0 };	//edge 중복생성을 막기위한 edge check 2차원 배열
char visit[MAX_VERTEX_NUM] = { 0 };		//vertex visit 판단 배열
Node* stack[MAX_VERTEX_NUM];
int top = -1;
Node* queue[MAX_VERTEX_NUM];
int front=-1;
int rear=-1;

/* 함수 리스트 */
int InitializeGraph();					//초기화함수
int InsertVertex(int vertexnum);		//vertex생성함수
int InsertEdge(int vertex1, int vertex2);	//edge생성함수
void PrintGraph();		//vertex와 edge print함수
void FreeVertex();		//node 할당해제함수
Node* Place(int vertex1, int vertex2);	//node 삽입위치 찾는 함수
void DFS(int vertex);
void push(Node*);
Node* pop();
void BFS(int vertex);
void enqueue(Node*);
Node* dequeue();

int main()
{
	printf("[2018038072  임상우]\n");
	char command;
	int key;
	int vertexnum1;
	int vertexnum2;
	int edgenum;
	Node* head = NULL;

	do {
		printf("----------------------------------------------------------------\n");
		printf("                        Graph Searches                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph     = z\n");
		printf(" Insert Vertex        = v           Insert Edge           = e\n");
		printf(" Depth First Search   = d           Breath First Search   = b\n");
		printf(" Print Graph          = p           Quit                  = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			InitializeGraph();
			break;
		case 'v': case 'V':
			printf("[vertex create(only 0~9)]\n");
			printf("Your vertex = ");
			scanf("%d", &vertexnum1);
			InsertVertex(vertexnum1);
			break;
		case 'e': case 'E':
			printf("Your vertex1 = ");
			scanf("%d", &vertexnum1);
			printf("Your vertex2 = ");
			scanf("%d", &vertexnum2);
			InsertEdge(vertexnum1, vertexnum2);

			break;
		case 'p': case 'P':
			PrintGraph();
			break;
		case 'd': case 'D':
			printf("input vertex : ");
			scanf("%d", &vertexnum1);
			DFS(vertexnum1);
			break;
		case 'b': case 'B':
			printf("input vertex : ");
			scanf("%d",&vertexnum1);
			BFS(vertexnum1);
			break;
		case 'q': case 'Q':
			FreeVertex();
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	FreeVertex();

	return 1;
}


int InitializeGraph() {

	FreeVertex();		//할당된 노드 모두 해제


	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		vertex[i].link = NULL;		//vertex link를 NULL로 초기화해줌(vertex의 link가 vertex의 생성유무를 판단한다)
	}
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		for (int j = 0; j < MAX_VERTEX_NUM; j++) {
			edge_check[i][j] = 0;
		}
	}
	return 0;


}
void FreeVertex() {

	for (int i = 0; i < MAX_VERTEX_NUM; i++) {

		Node* p = vertex[i].link;
		Node* prev = NULL;

		while (p != NULL) {
			prev = p;
			p = p->link;
			free(prev);
		}

		free(p);
		vertex[i].link = NULL;
	}
}

int InsertVertex(int vertexnum) {

	if (vertexnum < 0 || vertexnum>9) {		//0~9값이 아니면 오류문구 출력
		printf("vertexnum is not 0~9\n");
		return 1;
	}

	if (vertex[vertexnum].link) {			//vertex[vertexnum]->link가 존재한다면 이미 vertex가 생성된거기때문에
		printf("vertex [%d] is already exist\n", vertexnum);		//문구 출력후 종료
		return 0;
	}

	Node* node = (Node*)malloc(sizeof(Node));		//노드하나 동적할당
	node->link = NULL;
	vertex[vertexnum].link = node;		//vertexnum==0이라면 vertex[0]의 link는 ->node를 가리키게한다
	vertex[vertexnum].link->key = -9999;
	return 0;


}

int InsertEdge(int vertex1, int vertex2) {



	if ((vertex1 < 0 || vertex1>9) || (vertex2 < 0 || vertex2>9)) {		//vertex 0~9사이값이 아니면 경고문구 출력 후 종료
		printf("vertex1 vertex2 out of range\n");
		return 1;
	}

	if (!(vertex[vertex1].link)) {		//vertex1이 생성되지 않았으면 경고문구 출력 후 종료
		printf("vertex [%d] is not created\n", vertex1);
		return 1;
	}

	if (!(vertex[vertex2].link)) {		//vertex2가 생성되지 않았으면 경고문구 출력 후 종료
		printf("vertex [%d] is not created\n", vertex2);
		return 1;
	}

	if (edge_check[vertex1][vertex2] == 1 || edge_check[vertex2][vertex1] == 1) {		//edge_check[][]는 edge중복생성을 막아주는 배열이다.
		printf("edge is alreay exist\n");
		return 1;
	}


	Node* node2 = (Node*)malloc(sizeof(Node));		//노드생성
	Node* node1 = (Node*)malloc(sizeof(Node));
	node2->key = vertex2, node1->key = vertex1;	//노드의 key는 vertex2 (vertex1 -> vertex2로의 edge생성이므로)
	node2->link = NULL, node1->link = NULL;		//마지막노드임을 명시

	Node* search1 = Place(vertex1, vertex2);		//삽입위치 Place()로 받음
	if (search1->link == NULL) {	//첫번째나 마지막위치인경우
		search1->link = node2;
	}
	else {		//중간에 삽입하는 경우
		node2->link = search1->link;
		search1->link = node2;
	}
	Node* search2 = Place(vertex2, vertex1);
	if (search2->link == NULL) {
		search2->link = node1;
	}
	else {
		node1->link = search2->link;
		search2->link = node1;
	}


	edge_check[vertex1][vertex2] = 1;		//edge가생성됐으므로 1로초기화
	edge_check[vertex2][vertex1] = 1;

	return 0;
}

Node* Place(int vertexnum1, int vertexnum2) {
	Node* prev = vertex[vertexnum1].link;
	Node* search = vertex[vertexnum1].link->link;

	if (!search) {	//edge가 하나도 없는상황
		return prev;
	}
	while (search != NULL) {
		if (search->key >= vertexnum2) {
			return prev;
		}
		prev = search;
		search = search->link;
	}

	return prev;		//prev가 삽입할 노드의 바로 이전위치이므로 prev를 return 해준다

}
void PrintGraph() {
	Node* search = NULL;

	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		search = vertex[i].link;
		if (!search)	//vertex가 생성되지 않았을때 다음 인덱스로
			continue;
		printf("vertex[%d] is connected with vertex", i);
		search = search->link;
		while (search) {
			printf("[%d] ", search->key);
			search = search->link;
		}
		printf("\n");
	}
}

void push(Node* node) {
	if (top == MAX_VERTEX_NUM - 1) {	//stack이가득차면 경고문구 출력
		printf("stack is full\n");
		return;
	}
	stack[++top] = node;
}

Node* pop() {
	if (top == -1) {
		return NULL;
	}
	return stack[top--];
}

void DFS(int vertexnum) {
	if (vertexnum < 0 || vertexnum>9) {		//0~9값이 아니면 오류문구 출력
		printf("vertex is not 0~9\n");
		return;
	}
	Node* w = vertex[vertexnum].link;	//엣지로 연결된 첫번째 노드를 가리킴
	int key = 0;	//연결된 vertex의 key값 저장 변수
	if (!w) {		//w가 생성안됐으면 종료
		printf("vertex [%d] is not created\n", vertexnum);
		return;
	}
	w = w->link;		//첫번쨰 엣지 vertex로 이동

	if (!w) {		//이 경우는 vertex는 있지만 edge가 하나도 없는경우
		printf("vertex [%d] has no edges\n");
		return;
	}
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		visit[i] = 0;		//visit[]과 stack[] top 초기화해줌
		stack[i] = NULL;
	}
	top = -1;
	visit[vertexnum] = 1;		//사용자가 선택한 vertex는 방문했다고 표시
	printf(" [%d] ", vertexnum);	//그리고 출력 
	push(w);		//첫번째 vertex의 엣지중 가장 최솟값 push함
	while (1) {

		while (w) {
			key = w->key;
			if (w->key == -9999) {	//vertex 체크 노드는 push()건너뜀
				w = w->link;		
				continue;
			}

			if (visit[key] == 1) {	//이미 visit했으면 push()건너뛰고 다음 링크로
				w = w->link;
				continue;
			}
			push(w);			//vertex체크 노드도 아니고 visit하지않았으면 push해주고
			printf(" [%d] ", key);	//출력해주고
			visit[key] = 1;			//visit check해주고
			w = vertex[key].link;	//해당 vertex[index]로 간다.
		}
		//반복문에서 탐색을 다 해서 w가 NULL이되면
		w = pop();		//하나의 노드를 pop해 그 vertex 위치부터 다시 탐색한다

		if (!w)		//pop했는데 아무것도 안나오면 모든 엣지 탐색 끝 그러므로 반복문 탈출
			break;

	}
	printf("\n");

}


void enqueue(Node* node){
	if(rear==MAX_VERTEX_NUM-1){
		printf("queue is full\n");
		return;
	}

	queue[++rear]=node;
}

Node* dequeue(){
	if(front==rear || front==MAX_VERTEX_NUM-1)
	return NULL;

	return queue[++front];
}

void BFS(int vertexnum){
	if (vertexnum < 0 || vertexnum>9) {		//0~9값이 아니면 오류문구 출력
		printf("vertex is not 0~9\n");
		return;
	}
	Node* w = vertex[vertexnum].link;	//엣지로 연결된 첫번째 노드를 가리킴
	int key = 0;	//연결된 vertex의 key값 저장 변수
	if (!w) {		//w가 생성안됐으면 종료
		printf("vertex [%d] is not created\n", vertexnum);
		return;
	}
	w = w->link;		//첫번쨰 엣지 vertex로 이동

	if (!w) {		//이 경우는 vertex는 있지만 edge가 하나도 없는경우
		printf("vertex [%d] has no edges\n");
		return;
	}
	for (int i = 0; i < MAX_VERTEX_NUM; i++) {
		visit[i] = 0;		//visit[]과 stack[] top 초기화해줌
		queue[i] = NULL;
	}
	front = -1, rear = -1;
	visit[vertexnum] = 1;		//사용자가 선택한 vertex는 방문했다고 표시
	printf(" [%d] ", vertexnum);	//그리고 출력 
	
	while(1) {
		while(w){
			key=w->key;
			if(w->key==-9999){
				w=w->link;
				continue;
			}
			if(visit[key]==1){
				w=w->link;
				continue;
			}
			enqueue(w);
			visit[key]=1;
			w=w->link;
		}
		w=dequeue();
		if(!w)
		break;
		printf(" [%d] ",w->key);
		w=vertex[w->key].link;
	}

	printf("\n");
}