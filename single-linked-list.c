/*
 * single linked list
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

 /* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode = NULL;

	do {
		printf("\n-------------- [김동규]   [2019038077] --------------\n");
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h) {
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while (p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* p = h->first; //key보다 큰 값이 들어있는 노드를 찾아 저장하는 포인터
	listNode* pre; //key보다 큰 입력값이 들어있는 p노드의 직전 노드를 저장하는 포인터
	listNode* node = (listNode*)malloc(sizeof(listNode)); //key 값을 저장할 새 노드
	node->key = key;

	if (h->first) //노드가 하나도 없는지 확인하는 조건문
	{
		while (p->key <= key) //key 값보다 큰 값이 나올 때까지 반복
		{
			pre = p; //p가 다음 노드를 가리키기 전 p가 가리키는 노드 저장
			p = p->link; //다음 노드로 이동
			if (p == NULL) //p==NULL => key 보다 큰 값이 없다
				break; //loop 탈출
		}

		pre->link = node; //p의 직전 노드와 key 값이 들어있는 노드 연결(p의 앞에 삽입)
		node->link = p; //key 값이 들어있는 노드와 p 노드 연결
	}

	else //노드가 하나도 없다면
	{
		node->link = NULL; //새 노드의 link를 NULL로 초기화
		h->first = node; //새 노드를 헤드가 가리키게 함
	}

	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //key를 받은 노드
	listNode* rear = h->first; //마지막 노드를 찾아서 가리키는 포인터
	node->key = key;


	if (h->first) //노드가 하나도 없는지 확인하는 조건문
	{
		while (rear->link != NULL) //마지막 노드의 link는 NULL이므로 rear==NULL일 때, 즉 마지막 노드를 가리키면 loop 종료
		{
			rear = rear->link; //다음 노드를 가리키게 바꿈
		}

		rear->link = node; //받은 key가 들어있는 노드와 마지막 노드를 연결
		node->link = NULL; //마지막 노드가 된 node 노드의 link를 NULL로 만듦
	}

	else //노드가 하나도 없다면
	{
		node->link = NULL; //새 노드의 link를 NULL로 초기화
		h->first = node; //새 노드를 헤드가 가리키게 함
	}

	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (!h)
	{
		printf("There are no nodes to delete.\n"); //노드가 비었을 경우 오류 출력
		return 0;
	}

	listNode* p = h->first; //첫 번째 노드의 위치를 기억할 포인터

	h->first = p->link; //헤드의 위치를 두 번째 노드로 옮김

	free(p); //첫 번째 노드 해제

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	listNode* p = h->first; //key 값과 같은 값을 가진 노드를 찾아 저장하는 포인터
	listNode* pre; //p가 찾은 노드의 직전 노드를 저장하는 포인터

	while (p->key != key) //key와 값은 값을 가지는 노드를 찾기 위한 조건식
	{
		pre = p;
		p = p->link; //다음 노드로 이동
		if (p == NULL) //p==NULL => key와 일치하는 값이 없다
			break; //loop 탈출
	}

	if (p == NULL) //key 값이 없을 경우
	{
		printf("cannot find the node for key = %d\n", key); //key 값을 가진 노드를 찾을 수 없다고 오류 출력
		return 0;
	}

	pre->link = p->link; //찾은 노드의 직전 노드를 찾은 노드의 바로 다음 노드와 연결
	free(p); //찾은 노드 해제

	return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	listNode* rear = h->first; //마지막 노드를 찾아서 가리키는 포인터
	listNode* pre;
	
	if (!h)
	{
		printf("There are no nodes to delete.\n"); //노드가 비었을 경우 오류 출력
		return 0;
	}

	while (rear->link != NULL) //마지막 노드의 link는 NULL이므로 rear==NULL일 때, 즉 마지막 노드를 가리키면 loop 종료
	{
		pre = rear;
		rear = rear->link; //다음 노드로 이동
	}

	free(rear); //마지막 노드 해제
	pre->link = NULL;

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	listNode* middle;
	listNode* trail;
	middle = NULL;

	while (h->first)//헤드가 NULL을 가리킬 때까지 반복
	{
		trail = middle; //방향을 역순으로 바꿀 노드의 직전 노드를 trail이 가리키게 함
		middle = h->first; //역순이 안된 맨 앞 노드로 이동
		h->first = middle->link; //헤드가 가리키던 위치의 노드는 역순으로 배치될 것이므로 그 다음 노드를 가리키게 함
		middle->link = trail; //역순으로 배치할 노드와 이 노드의 직전 노드와 연결(방향은 역순)
	}

	h->first = middle;

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}