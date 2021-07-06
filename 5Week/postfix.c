/*
 * postfix.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

 /* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum {
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과를 저장 */

void postfixpush(char x);		//스택에 값저장하는 push역할함수
char postfixPop();				//스택에 저장된 값 가져오는 pop역할 함수
void evalPush(int x);			//스택에 값저장하는 push역할함수
int evalPop();					//스택에 저장된 값 가져오는 pop역할 함수
void getInfix();				//infix식 저장하는 함수
precedence getToken(char symbol);	//토큰을 받아오는 함수
precedence getPriority(char x);		//우선순위를 받아오는 함수
void charCat(char* c);		//c문자 하나를 postfixexp에 추가
void toPostfix();		//infix를 postfix로 변경하는 함수
void debug();			//현재 상태 출력하는 함수
void reset();			//전체를 초기화시키는 함수
void evaluation();		//postfix의 결과값을 구하는 함수
void eval_calc(int x, int y, int priority);		//eval연산하는 함수

int main()
{
	printf("[임상우]    [2018038072]\n");
	char command;

	do {
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

void postfixPush(char x)
{												

	postfixStack[++postfixStackTop] = x;		//postfixstacktop을 1증가시켜준다
												//postfixstack의 postfixstacktop 인덱스의 값을 x로 저장하고
}

char postfixPop()
{
	char x;
	if (postfixStackTop == -1)		//postfixstacktop이 -1이라면 아무것도 pop할게 없으므로
		return '\0';				//'\0' 리턴
	else {
		x = postfixStack[postfixStackTop--];		//postfixstack에 값이 저장돼있다면
													//postfixstack의 postfixstacktop 인덱스의 값을 x에 저장하고
													//postfixstacktop을 1감소시켜준다
	}
	return x;	//x 리턴
}

void evalPush(int x)
{
	evalStack[++evalStackTop] = x;		//evalstacktop 1증가
										//evalstack의 evalstacktop인덱스의 값에 x저장
	
}

int evalPop()
{
	if (evalStackTop == -1)			//evalstacktop이 -1이면
		return -1;					//비정상종료
	else							//evalstacktop이 -1이아니면 스택에 값이 저장돼있으므로
		return evalStack[evalStackTop--];		//evalstack에 evalstacktop의 인덱스 값 리턴
												//evalstacktop값 1감소시킴
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
	printf("Type the expression >>> ");
	scanf("%s", infixExp);		//infix표현식 입력받음
}

precedence getToken(char symbol)
{
	switch (symbol) {			//토큰 리턴
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	default: return operand;
	}
}

precedence getPriority(char x)
{
	return getToken(x);		//토큰에 저장된 값(우선순위) 리턴
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0')			//postfixexp이 Null이라면
		strncpy(postfixExp, c, 1);		//strncpy로 c를 복사
	else							//postfixexp에 값이있으면
		strncat(postfixExp, c, 1);	//stncat으로 한글자를 이어붙임
	
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char* exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */
	int i = 0;	// exp 증감연산자
	int priority;	//exp[i]의 priority
	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while (*exp != '\0')
	{	
		

		if (exp[i] == '\0') { //exp에 있는 요소를 다 읽으면 스택에 남아있는 요소들 전부 pop하고 postfixExp에 저장하고 탈출
			while (postfixStackTop != -1) {		//postfixStackTop이 1이될때까지
				x = postfixPop();			
				charCat(&x);				
			}

			break;		//반복문 탈출
		}
		priority = getPriority(exp[i]);		//exp[i]의 우선순위 구해줌

		

		if (priority == 9) {		//오른쪽괄호가나올때는
			while (postfixStack[postfixStackTop] != '(') {	//postfixstack 배열의 postfixstacktop 인덱스에 저장된 값이 왼쪽 괄호일때까지
				x = postfixPop();			//pop
				charCat(&x);				//값 저장
				
			}
			postfixPop();	//왼쪽괄호는 pop안해줬으니 한번 pop해줌
			i++;
			continue;
		}

		if (priority == 0) {	//왼쪽괄호가 나왔을때 postfixtop이 1이아닐때 (스택에 값이 저장돼있으면) priority비교문에서 
								//pop&push를 해버리기때문에(우선순위가 0으로 가장 낮기때문에)
			postfixPush(exp[i++]);		//예외적으로 push처리
			continue;

		}

		if (priority == 1) {	//x가 피연산자일때
			charCat(&exp[i++]);		//postfixexp에 저장
			continue;				
		}


		else if (postfixStackTop == -1) {	//아직 postfixStack에 아무것도 안들어와있고, x가 연산자일때
			postfixPush(exp[i++]);		//push
			continue;
		}


		if (priority <= getPriority(postfixStack[postfixStackTop])) {	//exp[i]의 우선순위가 postfixstack의 postfixstacktop인덱스 값의 우선순위보다 낮거나 같을때는

			x = postfixPop();		//pop&push   
			charCat(&x);
			postfixPush(exp[i]);	
		}

		else {		//반대의 경우에는 exp[i]만 스택에 push
			postfixPush(exp[i]);
		}



		i++;



		

	}
}

void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for (int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);			//infixexp,postfixexp,evalresult,postfixstack 전부 출력

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for (int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';

	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;				//전부 초기화
}	

void evaluation()
{
	char* exp = postfixExp;
	int priority;
	int i = 0;		//exp 증감연산자
	int x, y;
	while (exp[i] != '\0') {
		
		priority = getPriority(exp[i]);

		if (priority == 1) {		//exp[i]가 피연산자일때는 스택에 push
			evalPush(exp[i]-'0');		//exp[i]는 배열에 저장돼있어 아스키코드값으로 저장돼있기때문에 '0'만큼 뺀값을 push해준다

		}


		else  {		//exp[i]가 연산자일때는

			x = evalPop();		
			y = evalPop();	//두가지의 피연산자 pop시켜서 값 받고
		

			eval_calc(y, x, priority);	// x의 evalpostfix 인덱스값이 y의 evalpostfix 인덱스값보다 크므로
										//eval_calc 호출할때는 x와 y의 자리를 바꿔서 호출해준다

		}
	
		i++;		
		
	}

	evalResult = evalStack[0];		//반복문이 끝난후 evalstack[0]에 저장된 값이 결과값이므로 evalresult에 저장해준다
}





void eval_calc(int x, int y, int priority) {

	switch (priority) {		//계산해준값을 push해준다
	case 7: {	//곱하기
		evalPush(x * y);
		break;
	}
	case 6: {	//나누기
		evalPush(x / y);
		break;
	}
	case 5: {	//더하기
		evalPush(x + y);
		break;
	}
	case 4: {	//빼기
		evalPush(x - y);
		break;
	}

	}
	

}
