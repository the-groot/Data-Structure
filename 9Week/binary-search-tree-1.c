/*
 * Binary Search Tree #1
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

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */
	printf("[2018038072 임상우]\n");

	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
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
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
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
		freeBST((*h)->left);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	
	return 1;
}



void inorderTraversal(Node* ptr)
{


	if (ptr) {			//강의자료와 동일하게 구현 Recursive
		inorderTraversal(ptr->left);
		printf("[%d]  ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

void preorderTraversal(Node* ptr)
{


	if (ptr) {		//강의자료와 동일하게 구현 Recursive
		printf("[%d]  ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr)
{	


	if (ptr) {				//강의자료와 동일하게 구현 Recursive
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf("[%d]  ", ptr->key);
	}
}


int insert(Node* head, int key)
{
	

	if (!(head)) {	//head가 NULL이면 경고문구 출력 후 종료
		printf("head is empty\n");
		return 0;
	}
	
	Node* node = (Node*)malloc(sizeof(Node));	//노드 동적할당
	
	node->key = key;		//노드 key값 설정
	node->left = NULL;		//노드의 left,right 설정g
	node->right = NULL;

	if (head->left==NULL) {  //루트노드가 없을때 
		head->left = node; //head->left에 node삽입
		return 0;
	}

	Node* prev = head->left;    //처음은 prev가 루트노드를 가리키게함

	while (1)
	{
		
		if (node->key <= prev->key) {   //삽입하고자하는 노드의 key값이 현재 가리키고있는 key값보다작거나같으면
									//왼쪽으로감
			

			if (prev->left == NULL) {   //리프노드이면
				prev->left = node;    // 왼쪽에 삽입
                
				return 0;
			}
			prev = prev->left;
		}

		else {       //node의 key값이 현재 가리키고있는 노드보다 크면
					//오른쪽으로감  
					
			if (prev->right == NULL) {  //리프노드이면
				prev->right = node;   //오른쪽에 삽입
				return 0;
			}
			prev = prev->right;
		}
	}
	


	return 0;



}

int deleteLeafNode(Node* head, int key)
{	
	if(!head){
		printf("head is empty\n");
		return 0;
	}

	Node* delete=NULL;	//삭제할 key값을 가진 노드의 주소를 받아온다.
	Node* prev=NULL;	//삭제할 노드의 부모노드의 주소

	head=head->left;
	
	while(head){			//searchRecursive나 searchIterative를 호출하고싶었지만
							//그러려면 더블형 포인터로 head를 받아와야하므로
							//여기서 삭제할 노드의 위치를 구한다
		if(key==head->key)
		break;
		if(key<head->key){
		prev=head;
		head=head->left;
		}
		else{
		prev=head;
		head=head->right;
		}
	}

	delete=head;	//삭제할 노드의 주소를 받음

	if(!delete){	//삭제할 key값의 노드가 존재하지 않는다면
		printf("\n Cannot find the node [%d]\n", key);
		return 0;
	}

	if(delete->left!=NULL || delete->right!=NULL){	//자식노드가 하나라도 존재하면 리프노드가 아니므로
		printf("the node [%d] is not a leaf\n",key);
		return 0;
	}

	if(delete->key<=prev->key){	//delete가 prev의 왼쪽자식이면
		free(delete);			//delete할당해제 및
		prev->left=NULL;		//prev의 왼쪽노드 NULL
	}
	else{					//delete가 prev의 오른쪽 자식이면
	free(delete);			//delete할당해제 및
	prev->right=NULL;		//prev의 오른쪽노드 NULL
	}

	return 0;


}

Node* searchRecursive(Node* ptr, int key)
{								//강의자료 참고 후 동일하게 구현
	if(!ptr) return NULL;
	if(key==ptr->key) return ptr;
	if(key<ptr->key)
		return searchRecursive(ptr->left,key);
	return searchRecursive(ptr->right,key);	
}

Node* searchIterative(Node* head, int key)
{						//강의자료 참고 후 동일하게 구현
	head=head->left;

	while(head){
		if(key==head->key) return head;
		if(key<head->key)
		head=head->left;
		else
		head=head->right;
	}

	return NULL;
}


int freeBST(Node* head)
{
	
	if (head) {	//postorder방식으로 free구현
		freeBST(head->left);
		freeBST(head->right);
		free(head);
	}

	return 0;
}






