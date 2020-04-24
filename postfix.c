/*
 * postfix.c
 *
 *  2020 Data Structures, Homework #5
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


char infixExp[MAX_EXPRESSION_SIZE];       /* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];    /* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];    /* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];        /* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;       /* evalStack용 top */

int evalResult = 0;       /* 계산 결과를 저장 */

void postfixPush(char x)//postfixstack에 원소 저장
{
	postfixStack[++postfixStackTop] = x;
}

char postfixPop()//postfixstac의 top 원소  반환
{
	char x;
	if (postfixStackTop == -1)
		return '\0';
	else {
		x = postfixStack[postfixStackTop--];
	}
	return x;
}


void evalPush(int x)//evalstack에 원소 저장
{
	evalStack[++evalStackTop] = x;
}

int evalPop()//evalstac의 top 원소를 반환
{
	if (evalStackTop == -1)
		return -1;
	else
		return evalStack[evalStackTop--];
}


/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
	printf("Type the expression >>> ");
	scanf("%s", infixExp);
}

precedence getToken(char symbol)
{
	switch (symbol) {
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
	return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp; //infix 표현의 식
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while (*exp != '\0')
	{
		x = *exp;

		if (getPriority(x) == operand)//x에 저장된 infixExp의 원소가 피연산자인지 확인
		{
			charCat(&x);//postfixstack의 top에 있는 원소를  postfixExp에 넣음
		}

		else if (getPriority(x) == rparen)//x에 저장된 infixExp의 원소가 ')'인지 확인
		{
			while (getPriority(postfixStack[postfixStackTop]) != lparen) { //postfixstack의 top 원소가 '('가 아닌지 확인
				x = postfixPop();//postfixstack에서 pop하여 반환
				charCat(&x);
			}
			postfixStackTop--; //'('를 지우는 역할
		}

		else
		{
			if (getPriority(x) == lparen)//x에 저장된 infixExp의 원소가 '('인지 확인
			{
				postfixPush(x);//postfixstack에 x를 Pusg함
			}

			else
			{
				if(postfixStackTop != -1)
				while ((getPriority(x) <= getPriority(postfixStack[postfixStackTop])))
				{
					x = postfixPop();
					charCat(&x);//postfixstack의 top에 있는 원소를  postfixExp에 넣음
				}
				postfixPush(x);//postfixstack에 넣음
			}
		}
		exp++;
	}

	while (postfixStackTop != -1) //남은 연산자를 처리하기 위해 top을 -1까지 줄임
	{
		x = postfixPop();//postfixstack에 남은 원소를
		charCat(&x);//postfixExp에 저장
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
		printf("%c  ", postfixStack[i]);

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
	evalResult = 0;
}

void evaluation()
{
	precedence token; //우선순위 데이터를 담을 변수
	char *exp = postfixExp;
	int op1, op2;


	while (*exp != '\0')
	{
		token = getToken(*exp); //exp를 간접참조해 우선순위를 token에 저장
		if (token == operand) //token이 피연사자인지 확인
		{
			evalPush(*exp - '0'); //evalStack에 '0'(48)을 뺀 exp를 저장 -> 아스키코드 값이 아닌 정수형태로 저장하기 위해
		}

		else

		{
			op2 = evalPop();//evalstack에 저장된 데이터를 삭제하면서 반환해 저장
			op1 = evalPop();// (''')
			switch (token) { //token의 종류에 따른 계산을 switch문으로 나타냄
			case plus: evalPush(op1 + op2); break;
			case minus: evalPush(op1 - op2); break;
			case times: evalPush(op1*op2); break;
			case divide: evalPush(op1 / op2); break;
			default: break;
			}
		}
		exp++;//배열의 다음 주소를 가르키게 하기 위한 명령
	}
	evalResult = evalPop();//총 계산된 값이 마지막에 있으므로 pop을 통해 evalResult에 저장
}


int main()
{
	char command;
    printf("\n-------------- [김동규]   [2019038077] --------------\n");
    
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

	return 0;


}