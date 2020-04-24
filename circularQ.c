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
		printf("\n-------------- [김동규]   [2019038077] --------------\n");
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


QueueType *createQueue() //큐를 만드는 함수
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

element getElement() //큐에 들어갈 데이터를 받는 함수
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


/* complete the function */
int isEmpty(QueueType *cQ) //큐가 비었는지 확인하는 함수
{
	if(cQ->front == cQ->rear) //큐가 비었을 때는 front와 rear가 같다
	return 1;//맞는 경우 1 반환
	
    return 0;//아닌 경우 0 반환
}

/* complete the function */
int isFull(QueueType *cQ) //큐가 꽉찼는지 확인하는 함수
{
	if(cQ->rear == cQ->front) //큐가 꽉찼을 때는 front와 rear가 같다
	return 1;//맞는 경우 1 반환
	
    return 0;//아닌 경우 0 반환
}


/* complete the function */
void enQueue(QueueType *cQ, element item)
{
	int x;
	x = cQ->rear; //rear의 원래 위치 저장
	cQ->rear = (cQ->rear+1) % MAX_QUEUE_SIZE; //rear을 뒤로 움직이는 modulo 계산(rear가 큐의 끝 일//큐가 꽉찼을 때는 front와 rear가 같다때는 0번째로 돌아감)

	if(isFull(cQ)) //꽉찼는지 확인
	{
		printf("Circular Queue is full!\n");
		cQ->rear = x; //rear에 원래 위치를 저장
	}
	
	else
	{
		cQ->queue[cQ->rear] = item; //큐의 rear 자리에 데이터 저장
	}

	return 0;
}

/* complete the function */
void deQueue(QueueType *cQ, element *item)
{
	if(isEmpty(cQ)) //비었는지 확인
	{
		printf("Circular Queue is empty!\n");
	}

	else
	{
		cQ->front = (cQ->front+1) % MAX_QUEUE_SIZE; //front를 뒤로 움직이는 modulo 계산(front가 큐의 끝 일때는 0번째는 돌아감)
		cQ->queue[cQ->front]=NULL; //큐의 front 자리의 데이터를 삭제
	}
	
    return 0;
}


void printQ(QueueType *cQ) //큐를 출력하는 함수
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


void debugQ(QueueType *cQ) //큐의 자세한 정보를 출력하는 함수
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

