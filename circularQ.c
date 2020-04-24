/*
 * circularQ.c
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);

element getElement();


int main(void)
{
	QueueType *cQ = createQueue();
	element data;

	char command;

	do{
		printf("\n-------------- [�赿��]   [2019038077] --------------\n");
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ,&data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}


QueueType *createQueue() //ť�� ����� �Լ�
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

element getElement() //ť�� �� �����͸� �޴� �Լ�
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


/* complete the function */
int isEmpty(QueueType *cQ) //ť�� ������� Ȯ���ϴ� �Լ�
{
	if(cQ->front == cQ->rear) //ť�� ����� ���� front�� rear�� ����
	return 1;//�´� ��� 1 ��ȯ
	
    return 0;//�ƴ� ��� 0 ��ȯ
}

/* complete the function */
int isFull(QueueType *cQ) //ť�� ��á���� Ȯ���ϴ� �Լ�
{
	if(cQ->rear == cQ->front) //ť�� ��á�� ���� front�� rear�� ����
	return 1;//�´� ��� 1 ��ȯ
	
    return 0;//�ƴ� ��� 0 ��ȯ
}


/* complete the function */
void enQueue(QueueType *cQ, element item)
{
	int x;
	x = cQ->rear; //rear�� ���� ��ġ ����
	cQ->rear = (cQ->rear+1) % MAX_QUEUE_SIZE; //rear�� �ڷ� �����̴� modulo ���(rear�� ť�� �� ��//ť�� ��á�� ���� front�� rear�� ���ٶ��� 0��°�� ���ư�)

	if(isFull(cQ)) //��á���� Ȯ��
	{
		printf("Circular Queue is full!\n");
		cQ->rear = x; //rear�� ���� ��ġ�� ����
	}
	
	else
	{
		cQ->queue[cQ->rear] = item; //ť�� rear �ڸ��� ������ ����
	}

	return 0;
}

/* complete the function */
void deQueue(QueueType *cQ, element *item)
{
	if(isEmpty(cQ)) //������� Ȯ��
	{
		printf("Circular Queue is empty!\n");
	}

	else
	{
		cQ->front = (cQ->front+1) % MAX_QUEUE_SIZE; //front�� �ڷ� �����̴� modulo ���(front�� ť�� �� �϶��� 0��°�� ���ư�)
		cQ->queue[cQ->front]=NULL; //ť�� front �ڸ��� �����͸� ����
	}
	
    return 0;
}


void printQ(QueueType *cQ) //ť�� ����ϴ� �Լ�
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ) //ť�� �ڼ��� ������ ����ϴ� �Լ�
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}

