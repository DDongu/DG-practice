/*
 * single linked list
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

 /* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* �Լ� ����Ʈ */
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
		printf("\n-------------- [�赿��]   [2019038077] --------------\n");
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

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if (h != NULL)
		freeList(h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h) {
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
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
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {

	listNode* p = h->first; //key���� ū ���� ����ִ� ��带 ã�� �����ϴ� ������
	listNode* pre; //key���� ū �Է°��� ����ִ� p����� ���� ��带 �����ϴ� ������
	listNode* node = (listNode*)malloc(sizeof(listNode)); //key ���� ������ �� ���
	node->key = key;

	if (h->first) //��尡 �ϳ��� ������ Ȯ���ϴ� ���ǹ�
	{
		while (p->key <= key) //key ������ ū ���� ���� ������ �ݺ�
		{
			pre = p; //p�� ���� ��带 ����Ű�� �� p�� ����Ű�� ��� ����
			p = p->link; //���� ���� �̵�
			if (p == NULL) //p==NULL => key ���� ū ���� ����
				break; //loop Ż��
		}

		pre->link = node; //p�� ���� ���� key ���� ����ִ� ��� ����(p�� �տ� ����)
		node->link = p; //key ���� ����ִ� ���� p ��� ����
	}

	else //��尡 �ϳ��� ���ٸ�
	{
		node->link = NULL; //�� ����� link�� NULL�� �ʱ�ȭ
		h->first = node; //�� ��带 ��尡 ����Ű�� ��
	}

	return 0;
}

/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //key�� ���� ���
	listNode* rear = h->first; //������ ��带 ã�Ƽ� ����Ű�� ������
	node->key = key;


	if (h->first) //��尡 �ϳ��� ������ Ȯ���ϴ� ���ǹ�
	{
		while (rear->link != NULL) //������ ����� link�� NULL�̹Ƿ� rear==NULL�� ��, �� ������ ��带 ����Ű�� loop ����
		{
			rear = rear->link; //���� ��带 ����Ű�� �ٲ�
		}

		rear->link = node; //���� key�� ����ִ� ���� ������ ��带 ����
		node->link = NULL; //������ ��尡 �� node ����� link�� NULL�� ����
	}

	else //��尡 �ϳ��� ���ٸ�
	{
		node->link = NULL; //�� ����� link�� NULL�� �ʱ�ȭ
		h->first = node; //�� ��带 ��尡 ����Ű�� ��
	}

	return 0;
}


/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {

	if (!h)
	{
		printf("There are no nodes to delete.\n"); //��尡 ����� ��� ���� ���
		return 0;
	}

	listNode* p = h->first; //ù ��° ����� ��ġ�� ����� ������

	h->first = p->link; //����� ��ġ�� �� ��° ���� �ű�

	free(p); //ù ��° ��� ����

	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {

	listNode* p = h->first; //key ���� ���� ���� ���� ��带 ã�� �����ϴ� ������
	listNode* pre; //p�� ã�� ����� ���� ��带 �����ϴ� ������

	while (p->key != key) //key�� ���� ���� ������ ��带 ã�� ���� ���ǽ�
	{
		pre = p;
		p = p->link; //���� ���� �̵�
		if (p == NULL) //p==NULL => key�� ��ġ�ϴ� ���� ����
			break; //loop Ż��
	}

	if (p == NULL) //key ���� ���� ���
	{
		printf("cannot find the node for key = %d\n", key); //key ���� ���� ��带 ã�� �� ���ٰ� ���� ���
		return 0;
	}

	pre->link = p->link; //ã�� ����� ���� ��带 ã�� ����� �ٷ� ���� ���� ����
	free(p); //ã�� ��� ����

	return 0;
}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {

	listNode* rear = h->first; //������ ��带 ã�Ƽ� ����Ű�� ������
	listNode* pre;
	
	if (!h)
	{
		printf("There are no nodes to delete.\n"); //��尡 ����� ��� ���� ���
		return 0;
	}

	while (rear->link != NULL) //������ ����� link�� NULL�̹Ƿ� rear==NULL�� ��, �� ������ ��带 ����Ű�� loop ����
	{
		pre = rear;
		rear = rear->link; //���� ���� �̵�
	}

	free(rear); //������ ��� ����
	pre->link = NULL;

	return 0;
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {

	listNode* middle;
	listNode* trail;
	middle = NULL;

	while (h->first)//��尡 NULL�� ����ų ������ �ݺ�
	{
		trail = middle; //������ �������� �ٲ� ����� ���� ��带 trail�� ����Ű�� ��
		middle = h->first; //������ �ȵ� �� �� ���� �̵�
		h->first = middle->link; //��尡 ����Ű�� ��ġ�� ���� �������� ��ġ�� ���̹Ƿ� �� ���� ��带 ����Ű�� ��
		middle->link = trail; //�������� ��ġ�� ���� �� ����� ���� ���� ����(������ ����)
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