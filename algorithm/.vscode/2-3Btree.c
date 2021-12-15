#include<stdio.h>
#include <stdlib.h>

//차수가 3인 b-tree

//1.루트노드는 적어도 2개의 자식을 갖는다.
//2.모든 노드는 적어도m/2(ceiling)개의 자식을 갖는다.
//3.모든 외부노드들은 같은 레벨에 있다.

typedef struct node{
	int key1,key2;	//노드의 키값은 2개			
	struct node* cp1;	//자식노드를 가리킬 포인터는 최대 3개(차수가 3이므로)
	struct node* cp2;	//cp는 child pointer를 말함
	struct node* cp3;
}Node;

void CreateHeadNode(Node** h);
int InsertNode(Node*, int);	
//삽입위치 찾아 삽입
//꽉차면 분할
//분할했는데 조건안맞으면 중앙값 부모노드로보냄
//부모노드꽉차면 다시가운데부모노드로보냄

int main(void)
{	
	Node* head;
	CreateHeadNode(&head);

	FILE* pFile = fopen("test.txt", "r"); //read mode 
	int intTemp = -1;

	if (pFile == NULL)
	{
		printf("File does not exist");
		return 0;
	}


	// 파일 읽기 성공
	while(1) {
		fscanf(pFile, "%d", &intTemp);
		if (intTemp < 0) break;
		 // 트리생성
		 InsertNode(head,intTemp);
		
		 // 생성된 트리에서 키 검색

		printf("%d ", intTemp);
	}
	
	//파일 형태로 반환

	fclose(pFile);          //close file
	return 0;
}


void CreateHeadNode(Node** h) {

	(*h) = (Node*)malloc(sizeof(Node));
	(*h)->key1 = -9999;
	(*h)->key2 = -9999;
	(*h)->cp1 = NULL;				//헤드노드 키값은 -9999, cp2,cp3는 자신을 가리킴 cp1는 NULL 
	(*h)->cp2 = (*h);
	(*h)->cp3=(*h);

}

int InsertNode(Node* head, int key){
	Node* search=head->cp1;
	

	if (!head) {		//헤드 노드가 생성이 안됐으면
		printf("head is empty\n");	//경고문구 출력 후
		return 0;		//종료
	}

	if(!search){	//루트노드를 삽입할때
		Node* node=(Node*)malloc(sizeof(Node));	//노드 동적할당
		head->cp1=node;
		node->key1=key;	//처음의 key값은 key1에 저장
		node->cp1=NULL;
		node->cp2=NULL;
		node->cp3=NULL;
		return 0;
	}

	while(1){








	}

}