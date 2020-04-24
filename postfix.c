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

 /* stack ������ �켱����, lparen = 0 ���� ���� */
typedef enum {
	lparen = 0,  /* ( ���� ��ȣ */
	rparen = 9,  /* ) ������ ��ȣ*/
	times = 7,   /* * ���� */
	divide = 6,  /* / ������ */
	plus = 5,    /* + ���� */
	minus = 4,   /* - ���� */
	operand = 1 /* �ǿ����� */
} precedence;


char infixExp[MAX_EXPRESSION_SIZE];       /* infix expression�� �����ϴ� �迭 */
char postfixExp[MAX_EXPRESSION_SIZE];    /* postfix�� ����� ���ڿ��� �����ϴ� �迭 */
char postfixStack[MAX_STACK_SIZE];    /* postfix�� ��ȯ�� ���� �ʿ��� ���� */
int evalStack[MAX_STACK_SIZE];        /* ����� ���� �ʿ��� ���� */

int postfixStackTop = -1;  /* postfixStack�� top */
int evalStackTop = -1;       /* evalStack�� top */

int evalResult = 0;       /* ��� ����� ���� */

void postfixPush(char x)//postfixstack�� ���� ����
{
	postfixStack[++postfixStackTop] = x;
}

char postfixPop()//postfixstac�� top ����  ��ȯ
{
	char x;
	if (postfixStackTop == -1)
		return '\0';
	else {
		x = postfixStack[postfixStackTop--];
	}
	return x;
}


void evalPush(int x)//evalstack�� ���� ����
{
	evalStack[++evalStackTop] = x;
}

int evalPop()//evalstac�� top ���Ҹ� ��ȯ
{
	if (evalStackTop == -1)
		return -1;
	else
		return evalStack[evalStackTop--];
}


/**
 * infix expression�� �Է¹޴´�.
 * infixExp���� �Էµ� ���� �����Ѵ�.
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
 * �����ϳ��� ���޹޾�, postfixExp�� �߰�
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp�� ���ڸ� �ϳ��� �о�鼭 stack�� �̿��Ͽ� postfix�� �����Ѵ�.
 * ����� postfix�� postFixExp�� ����ȴ�.
 */
void toPostfix()
{
	/* infixExp�� ���� �ϳ����� �б����� ������ */
	char *exp = infixExp; //infix ǥ���� ��
	char x; /* �����ϳ��� �ӽ÷� �����ϱ� ���� ���� */

	/* exp�� �������Ѱ��鼭, ���ڸ� �а� postfix�� ���� */
	while (*exp != '\0')
	{
		x = *exp;

		if (getPriority(x) == operand)//x�� ����� infixExp�� ���Ұ� �ǿ��������� Ȯ��
		{
			charCat(&x);//postfixstack�� top�� �ִ� ���Ҹ�  postfixExp�� ����
		}

		else if (getPriority(x) == rparen)//x�� ����� infixExp�� ���Ұ� ')'���� Ȯ��
		{
			while (getPriority(postfixStack[postfixStackTop]) != lparen) { //postfixstack�� top ���Ұ� '('�� �ƴ��� Ȯ��
				x = postfixPop();//postfixstack���� pop�Ͽ� ��ȯ
				charCat(&x);
			}
			postfixStackTop--; //'('�� ����� ����
		}

		else
		{
			if (getPriority(x) == lparen)//x�� ����� infixExp�� ���Ұ� '('���� Ȯ��
			{
				postfixPush(x);//postfixstack�� x�� Pusg��
			}

			else
			{
				if(postfixStackTop != -1)
				while ((getPriority(x) <= getPriority(postfixStack[postfixStackTop])))
				{
					x = postfixPop();
					charCat(&x);//postfixstack�� top�� �ִ� ���Ҹ�  postfixExp�� ����
				}
				postfixPush(x);//postfixstack�� ����
			}
		}
		exp++;
	}

	while (postfixStackTop != -1) //���� �����ڸ� ó���ϱ� ���� top�� -1���� ����
	{
		x = postfixPop();//postfixstack�� ���� ���Ҹ�
		charCat(&x);//postfixExp�� ����
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
	precedence token; //�켱���� �����͸� ���� ����
	char *exp = postfixExp;
	int op1, op2;


	while (*exp != '\0')
	{
		token = getToken(*exp); //exp�� ���������� �켱������ token�� ����
		if (token == operand) //token�� �ǿ��������� Ȯ��
		{
			evalPush(*exp - '0'); //evalStack�� '0'(48)�� �� exp�� ���� -> �ƽ�Ű�ڵ� ���� �ƴ� �������·� �����ϱ� ����
		}

		else

		{
			op2 = evalPop();//evalstack�� ����� �����͸� �����ϸ鼭 ��ȯ�� ����
			op1 = evalPop();// (''')
			switch (token) { //token�� ������ ���� ����� switch������ ��Ÿ��
			case plus: evalPush(op1 + op2); break;
			case minus: evalPush(op1 - op2); break;
			case times: evalPush(op1*op2); break;
			case divide: evalPush(op1 / op2); break;
			default: break;
			}
		}
		exp++;//�迭�� ���� �ּҸ� ����Ű�� �ϱ� ���� ���
	}
	evalResult = evalPop();//�� ���� ���� �������� �����Ƿ� pop�� ���� evalResult�� ����
}


int main()
{
	char command;
    printf("\n-------------- [�赿��]   [2019038077] --------------\n");
    
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