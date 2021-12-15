#include <iostream>
#define MAX 10000


/*
처음에 문장을 입력하면 대문자 소문자 따로 각각 빈도수를 count해 key값에 매치 시켜 frequency table을 만든다
만들어진 frequency table을 통해 node를 생성하고 각각 node들은 node* next를 통해 연결시킨다.(CreateTree)
연결된 노드들중에 최솟값을 2개 찾아 새노드를 만들어 각각 왼쪽 오른쪽자식으로 삽입한다.
최솟값 2개의 노드들은 기존의 노드들과 연결해제(삭제) 해준다(next->NULL)
새노드는 기존에 존재하던 노드들과 연결해준다.

최솟값은 앞에있는 노드들 부터 찾아나가며 새로운 노드는 마지막에 삽입된다.
이 과정을 한개의 노드가 남을때 까지 반복하면 하프만트리가 완성된다.

inordertraversal을 통해 encoding을 하고 encoding된 result값은 decoding을 위해 배열에 저장한다.
decoding은 result값을 통해 리프노드를 찾으면 문자로 출력하는 방식을 사용한다.


*/



using namespace std;
int stack[MAX];		//한 문자 encoding값 담아둘 스택
int top = -1;
int result[MAX];		//전체 문자 encoding값 담아둘 배열
int result_length = 0;	//배열의 길이를 나타내는 변수

void push(int a) {		//stack push 함수

	if (top >= MAX - 1) {
		cout << "stack is full" << endl;
		return;
	}

	stack[++top] = a;
}

int pop() {		//stack pop함수

	if (top == -1)
	{
		return NULL;
	}

	return stack[top--];

}


typedef struct Node {		//구조체 key값, 빈도수, left, right자식, next를 통해 연결되어있음
	char key;
	int freq;
	struct Node* left;
	struct Node* right;
	struct Node* next;
}node;






int CountAlphabet(string, int*,int *,char*,int *);	//알파벳개수 셈
void CreateFrequencyTable(int* allcase, char* key, int alphabet_count, int* , int* );	//frequency table만듬
void CreateNode(char*, int*, int, Node**);		//노드 생성
void CreateTree(Node**,Node*);			//트리 생성
Node* CreateHaffmanTree(Node**);		//하프만 트리 생성
Node* SearchMin(Node**);		//최소freq을 가진 노드를 찾고, 삭제도해줌
void Encoding(char, Node*);		//인코딩하는 함수
void PrintCode();		//인코딩된 숫자 출력
void Decoding(Node*);		//디코딩하는함수
void FreeNode(Node*);		//노드 동적할당해제



int main() {
	string str;	//문자열입력받을 변수
	int alphabet_count;		//대문자 소문자 합쳐서 총 알파벳 개수
	int uppercase[26] = { 0 };	//대문자의 개수를 셀 변수
	int lowercase[26] = { 0 };	//소문자의 개수를 셀 변수
	int string_length = 0;    //입력받은 string의 길이
	int i = 0;				//반복문변수
	char* key=NULL;			//알파벳 대소문자 모두 저장할 포인터
	int* allcase=NULL;		//알파벳 대소문자의 개수를 모두 저장할 포인터
	Node* root = NULL;
	


	printf("Put the string to encode: ");
	cin >> str;
	while (1) {
		if (str[i] == '\0')
			break;
		string_length++;
		i++;
	}
	

	cout << "encoding..."<<endl<<endl;
	alphabet_count=CountAlphabet(str, uppercase,lowercase,key,allcase);		//알파벳 대소문자 각각 센다
	allcase = new int[alphabet_count];		//존재하는 문자의 개수만 세어줄 변수
	key = new char[alphabet_count];


	CreateFrequencyTable(allcase, key, alphabet_count,uppercase, lowercase);	//frequency table 생성
	CreateNode(key, allcase, alphabet_count,&root);		//노드생성
	root=CreateHaffmanTree(&root);			//하프만트리 생성후 루트노드에 할당
	cout << "Encoded result: ";
	for (int i = 0; i < string_length; i++) {
		Encoding(str[i], root);			//인코딩
	}
	cout << endl;
	
	
	cout << "Decoding..." << endl<<endl;
	Decoding(root);		//디코딩
	FreeNode(root);		//노드 동적할당 해제
	
	return 0;
}


void FreeNode(Node* root) {

	if (root) {
		FreeNode(root->left);
		FreeNode(root->right);
		delete root;
	}

	
}

void Decoding(Node* root) {		//inordertraversal방식

	Node* rooot = root;		//루트노드로 돌아가기 위해 세이브포인터

	for (int i = 0; i <= result_length; i++) {		//result값을 읽는다

		if (!root->left && !root->right) {		//리프노드일때
			cout << root->key;	//출력
			root = rooot;		//루트노드는 다시 원위치로
		}


		if (result[i] == 0) {		//0이면 왼쪽으로
			root = root->left;
		}
		else if (result[i] == 1) {		//1이면 오른쪽으로
			root = root->right;
		}
	}

}

void Encoding(char key, Node* root) {	//inordertraversal방식
	
	

	if (!root) {
		pop();
		return;
	}

	
	push(0);			//왼쪽갈때마다 0스택에 추가
	Encoding(key, root->left);		//왼쪽으로 탐색
	

	if (!root->left && !root->right) {
		if (root->key == key) {		//key값을 찾았으면
			PrintCode();
			return;
		}
	}
	
	push(1);				//오른쪽갈때마다 1스택에 추가
	Encoding(key, root->right);		//오른쪽으로 탐색
	pop();

}

void PrintCode() {
	for (int i = 0; i <= top; i++) {		//스택의 값을 출력
		cout << stack[i];
		result[result_length] = stack[i];	//결과값은 result에 차곡차곡 저장한다.
		result_length++;
	}


	top = -1;		//top -1로 초기화
}

Node* CreateHaffmanTree(Node** root) {

	Node* left = NULL;
	Node* right = NULL;
		
	while (1) {
		left = SearchMin(root);	//freq이 가장 작은 node 반환
		right = SearchMin(root);
		Node* newnode = new Node;	//새노드 생성
		newnode->next = NULL;

		if (!right) {		//노드가 하나만 있을때는
			return left;		//left반환
		}
		newnode->freq = left->freq + right->freq;		//left와 right의 freq합침
		newnode->left = left;							//왼쪽자식 오른쪽자식 연결
		newnode->right = right;
		CreateTree(root, newnode);				//트리에 연결
	}
	
		
}

Node* SearchMin(Node** root) {
	Node* search = *root;		//search를 할 포인터
	Node* prev = NULL;
	Node* prev_minnode = NULL;
	Node* minnode = search;		//minnode의 주소를 저장하는 포인터

	if (!search) {		//root노드가 존재하지않으면 경고문구와 함께 null반환
		return NULL;
	}

	int minindex = search->freq;	//첫번째 노드를 최솟값으로 가정


	

	while (search->next) {			
		prev = search;
		search = search->next;		//계속탐색
		
		if (search->freq < minindex) {		//minindex보다 작은freq를가지면
			minnode = search;			//minnode는 그 노드를 가리킴
			prev_minnode = prev;		//minnode의 이전을 가리키는 노드
			minindex = search->freq;
		}
		
	}
	
	if (!prev_minnode) {		//첫번째 노드가 minnode일때는

		if (minnode->next) {		//minnode가 하나남은 노드가 아닐때
			*root = minnode->next;	//루트노드 새로가리킴
			minnode->next = NULL;
			return minnode;
		}
		else {			//minnode가 하나남았을때
			*root = NULL;
			return minnode;
		}

	}

	prev_minnode->next = minnode->next;		//minnode는 이제 연결해제해주고		
	minnode->next = NULL;			//minnode->next도 초기화해줌
	return minnode;

}

void CreateNode(char* key, int* allcase, int count, Node** root) {
	
	for (int i = 0; i < count; i++) {		//알파벳 개수만큼 노드 생성 후 
		node* newnode = new node;
		newnode->freq = allcase[i];
		newnode->key = key[i];
		newnode->left = NULL;
		newnode->right = NULL;
		newnode->next = NULL;
		CreateTree(root, newnode);			//서로 연결해줌
	}
}

void CreateTree(Node** root, Node* newnode) {
	
	Node* search = *root;
	if (!search) {	//root노드가 null일때
		*root = newnode;		//newnode를 가리키게함
	}
	else {		//root노드가 존재하면
		while (search->next) {		//마지막 노드까지 탐색한 후
			search = search->next;
		}
		search->next = newnode;		//마지막 노드의 next에 삽입
	}
}

void CreateFrequencyTable(int* allcase, char* data, int alphabet_count, int* upper, int* lower) {

	int allcasecount = 0;	//allcase의 개수를 세어주는 변수
	int datacasecount = 0;	//data의 개수를 세어주는 변수

	for (int i = 0; i < 26; i++) {		//upper의 정보 data와 allcase에 저장
		if (upper[i] > 0) {
			data[datacasecount] = 'A' + i;
			allcase[allcasecount] = upper[i];
			allcasecount++;
			datacasecount++;
		}
	}
	for (int i = 0; i < 26; i++) {	//lower의 정보 data와 allcase에 저장
		if (lower[i] > 0) {
			data[datacasecount] = 'a' + i;
			allcase[allcasecount] = lower[i];
			allcasecount++;
			datacasecount++;
		}
	}

}

int CountAlphabet(string str , int* upper, int* lower,char* data, int* allcase) {
	int count = 0;	//개수를 세어주는 변수
	
	
	for (int i = 0; i < str.size(); i++) {

		if (isalpha(str[i]) != 0) {	//문자가 알파벳일때

			if ('a' <= str[i] && str[i] <= 'z') {	//소문자일때
				lower[str[i] - 'a']++;
			}
			else if ('A' <= str[i] && str[i] <= 'Z') {	//대문자일때
				upper[str[i] - 'A']++;
			}

		}

	}


	for (int i = 0; i < 26; i++) {
		if (upper[i] > 0) {
			++count;			//알파벳 문자의 개수 count
		}
		if (lower[i] > 0) {
			++count;
		}
	}

	

	return count;
	
}

