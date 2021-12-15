#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
	int key;
	struct node* leftChild;
	struct node* rightChild;

}Node;

void CreatHeadNode(Node** h);		//����带 �����ϴ� �Լ�(������ ��Ʈ��带����Ű�� ���)
int InsertNode(Node*, int);			//Ʈ�������� �����ϴ� �Լ�
int freeBST(Node*);					//�����Ҵ��� ������ �����ϴ� �Լ�
Node* SearchIterative(Node*, int);	//�ݺ������·� key���� search�ϴ� �Լ�
void inorderTraversal(Node* ptr);	//inorderTraversal(recursive)���·� Ʈ���� Ž��������ϴ��Լ�(main������ �ּ�ó���س���)
Node* searchRecursive(Node*, int);

void CreateHeadNode(Node** h) {

	(*h) = (Node*)malloc(sizeof(Node));
	(*h)->key = -9999;
	(*h)->leftChild = NULL;				//����� Ű���� -9999, rightChild�� �ڽ��� ����Ŵ leftChild�� NULL 
	(*h)->rightChild = (*h);


}

Node* searchRecursive(Node* ptr, int key)
{								//�����ڷ� ���� �� �����ϰ� ����
	if (!ptr) return NULL;
	if (key == ptr->key) return ptr;
	if (key < ptr->key)
		return searchRecursive(ptr->leftChild, key);
	return searchRecursive(ptr->rightChild, key);
}

int InsertNode(Node* head, int key) {			//���Գ���Լ�
	Node* search = NULL;		//���Ե� ��ġ�� ã�� ������

	Node* node = (Node*)malloc(sizeof(Node));			//���Ե� ��� �����Ҵ�
	node->leftChild = NULL;
	node->rightChild = NULL;
	node->key = key;

	search = head->leftChild;

	if (!head) {		//��� ��尡 ������ �ȵ�����
		printf("head is empty\n");	//����� ��� ��
		return 0;		//����
	}

	if (!(search)) {	//��Ʈ��带 �����Ҷ�
		head->leftChild = node;		//����� left�� node�� ����Ŵ
		return 0;
	}

	while (1) {	//��Ʈ��� �̿��� ��带 �����Ҷ�

		if (search->key < key) {	//���Ե� Ű�� �� ũ��

			if (!(search->rightChild))	//���Ե� ��ġ�� ã����
			{
				search->rightChild = node;	//search�� �������ڽĿ� node����
				return 0;
			}
			search = search->rightChild;	//������ �ڽ����ΰ���.

		}

		else {		//���Ե� Ű�� �� ������

			if (!(search->leftChild)) {	//���Ե� ��ġ�� ã����
				search->leftChild = node; //search�� �����ڽĿ� node����
				return 0;
			}

			search = search->leftChild; //�����ڽ����� ����

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


	if (ptr) {			//�����ڷ�� �����ϰ� ���� Recursive
		inorderTraversal(ptr->leftChild);
		printf("[%d]  ", ptr->key);
		inorderTraversal(ptr->rightChild);
	}
}

int freeBST(Node* head)
{

	if (head) {	//postorder������� free����
		freeBST(head->leftChild);
		freeBST(head->rightChild);
		free(head);
	}

	return 0;
}


int main(void)
{

	Node* head = NULL;	//��Ʈ��带 ����ų ����� ����
	Node* result = NULL;
	int user_input;
	CreateHeadNode(&head);	//����� ����
	FILE* pFile = fopen("test.txt", "r"); //read mode 
	int intTemp = -1;

	if (pFile == NULL)
	{
		printf("File does not exist");
		return 0;
	}


	// ���� �б� ����
	while (1) {
		fscanf(pFile, "%d", &intTemp);
		if (intTemp < 0) break;
		// Ʈ������
		InsertNode(head, intTemp);
	}


	//���� ���·� ��ȯ


	fclose(pFile);          //close file

	// ������ Ʈ������ Ű �˻�
	printf("�˻��� key�� �Է�:");
	scanf("%d", &user_input);

	result = SearchIterative(head->leftChild, user_input);
	if (result)
		printf("\n node [%d] found at %p\n", result->key, result);
	else
		printf("\n Cannot find the node [%d]\n", user_input);

	//inorderTraversal(head->leftChild);
	freeBST(head->leftChild);		//��� �����Ҵ� ����
	return 0;
}