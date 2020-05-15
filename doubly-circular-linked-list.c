/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
 /* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* �Լ� ����Ʈ */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode = NULL;

	do {
		printf("\n------------------- [�赿��]   [2019038077] ------------------\n");
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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
			initialize(&headnode);
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


int initialize(listNode** h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if (*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;	
	return 1;
}

/* �޸� ���� */
int freeList(listNode* h) {

	listNode *tmp, *last = h->rlink, *del;
	del = h->rlink; //������ ����� ���� ��带 ����Ű�� ��

	/*������ ��带 ã�� ���� loop��*/
	while (last->rlink != h)//������ ����� rlink�� ������̱� ����
	{
		last = last->rlink; //���� ���� �̵�
	}

	while (del != h) {
		tmp = del->rlink; //������ ����� ���� ��带 ����Ű�� ��
		free(del); //��� ����
		del = tmp; //������ ����� ���� ��带 ����Ű�� ��
	}
	free(del);//���� ������ ���(��� ���) ����
	return 0;
}


void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(listNode* h, int key) {

	listNode *node, *last = h->rlink;
	node = (listNode*)malloc(sizeof(listNode)); //���� ���� ���� ��ų ��� ����
	node->key = key;
	
	if (h) //����Ʈ�� �������� �˻�
	{
		if (h->rlink == h) { //��忡 ���� ���� �ϳ��� ���ٸ�
			h->rlink = node; //��� ��带 ���ο� ��忡 ����
			h->llink = node; //��� ��带 ���ο� ��忡 ����
			node->llink = h; //���ο� ��带 ��� ��忡 ����
			node->rlink = h; //���ο� ��带 ��� ��忡 ����
			return 1;
		}

		/*������ ��带 ã�� ���� loop��*/
		while (last->rlink != h)//������ ����� rlink�� ������̱� ����
		{
			last = last->rlink; //���� ���� �̵�
		}
		
		last->rlink = node; //������ ��带 ���ο� ��忡 ����
		node->llink = last; //���ο� ��带 ������ ��忡 ����
		h->llink = node; //��� ��带 ���ο� ��忡 ����
		node->rlink = h; //���ο� ��带 ��� ��忡 ����
	}

	else
	{
		printf("There is no List!\n");
	}
	return 1;
}


/**
 * list�� ������ ��� ����
 */
int deleteLast(listNode* h) {

	listNode *last = h->rlink, *pre;

	if (h) //����Ʈ�� �������� �˻�
	{
		if (h->rlink == h) { //��忡 ���� ���� �ϳ��� ���ٸ�
			printf("There is nothing to delete!\n");
			return 1;
		}

		/*������ ��带 ã�� ���� loop��*/
		while (last->rlink != h)//������ ����� rlink�� ������̱� ����
		{
			last = last->rlink; //���� ���� �̵�
		}
		pre = last->llink; //������ ������ ��带 ����Ű�� ��
		free(last); //������ ��� ����

		if (h->rlink == NULL) //�̶��� ��尡 ���� ����̴�. 
		{
			h->rlink = h; //��带 �ʱ�ȭ�� ���·�
			h->llink = h; //��带 �ʱ�ȭ�� ���·�
			return 1; //���� �״�� ����
		}
		
		else
		{
			pre->rlink = h; //������ ��尡 �� pre�� ��� ��忡 ����
			h->llink = pre; //��� ��带 pre ��忡 ����
		}
	}

	else
	{
		printf("There is no List!\n");
	}

	return 1;
}


/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(listNode* h, int key) {

	listNode *node;
	node = (listNode*)malloc(sizeof(listNode)); //���� ���� ���� ��ų ��� ����
	node->key = key; //��忡 key�� ����

	if (h) //����Ʈ�� �������� �˻�
	{
		if (h->rlink == h) { //��忡 ���� ���� �ϳ��� ���ٸ�
			h->rlink = node; //��� ��带 ���ο� ��忡 ����
			h->llink = node; //��� ��带 ���ο� ��忡 ����
			node->llink = h; //���ο� ��带 ��� ��忡 ����
			node->rlink = h; //���ο� ��带 ��� ��忡 ����
			return 1;
		}

		h->rlink->llink = node; //��� ��带 ������ �� �� ��带 ���ο� ��忡 ����
		node->rlink = h->rlink; //���ο� ��带 ��� ��带 ������ �� �� ��忡 ����
		h->rlink = node; //��� ��带 ���ο� ��忡 ����
		node->llink = h; //���ο� ��带 ��� ��忡 ����
	}

	else
	{
		printf("There is no List!\n");
	}

	return 1;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(listNode* h) {

	listNode *del, *nxt;

	if (h) //����Ʈ�� �������� �˻�
	{
		if (h->rlink == h) { //��忡 ���� ���� �ϳ��� ���ٸ�
			printf("There is nothing to delete!\n");
			return 1;
		}

		del = h->rlink; //�� �� ��带 ����Ű�� ��
		nxt = del->rlink; //������ ����� ���� ��带 ����Ű�� ��
		free(del); //��� ����

		if (h->rlink == NULL) //�̶��� ��尡 �ϳ� �ۿ� �ȳ����� ����̴�.
		{
			h->rlink = h; //��带 �ʱ�ȭ�� ���·�
			h->llink = h; //��带 �ʱ�ȭ�� ���·�
			return 1;//���� �״�� ����
		}

		else
		{
			h->rlink = nxt; //��� ��带 �� �� ���� ����
			nxt->llink = h; //�� �� ��带 ��� ���� ����
		}
	}

	else
	{
		printf("There is no List!\n");
	}

	return 1;
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(listNode* h) {

	listNode *x = h->rlink, *tmp;
	listNode *k = h->llink; //�ٲٱ� �� ����Ʈ�� ������ ��带 ����ϴ� ������

	while (h->rlink != k) //����� ������ �������ְ� ������ �������ְ� ����, h->rlink�� �ٲٱ� �� �� �� ��忡�� �ٲٱ� �� �� �� ���� �ٲ�
	{					  //���� h->rlink == k ��, �ٲ� �� �� �� ��� == �ٲ�� �� ������ ��� �� �� loop ����
		
		/*����� llink�� rlink�� ������ ����*/
		tmp = x->llink; //x->llink�� �ӽ�����
		x->llink = x->rlink; //x->llink�� x->rlink�� swap
		x->rlink = tmp; //x->llink�� x->rlink�� swap

		x = x->llink; //x�� ���� ���� �̵�
	}

	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(listNode* h, int key) {

	listNode *tmp = h->rlink, *pre;
	listNode *node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	if (h) //����Ʈ�� �������� �˻�
	{
		if (h->rlink == h) { //��忡 ���� ���� �ϳ��� ���ٸ�
			h->rlink = node; //��� ��带 ���ο� ��忡 ����
			h->llink = node; //��� ��带 ���ο� ��忡 ����
			node->llink = h; //���ο� ��带 ��� ��忡 ����
			node->rlink = h; //���ο� ��带 ��� ��忡 ����
			return 1;
		}

		while (tmp->key <= key) //key������ ū ���� ���� ��带 ã�� loop��
		{
			tmp = tmp->rlink; //���� ���� �̵�
			if (tmp == h) //key������ ū ���� ���ٸ� tmp�� ����Ʈ�� �� ���� ���� ��带 ����Ű�� ��
			{
				break; //�̶� loop�� Ż��
			}
		}
		pre = tmp->llink; //ã�� ����� �� ���
		
		pre->rlink = node; //ã�� ����� �� ��带 ���ο� ��忡 ����
		node->llink = pre; //���ο� ��带 ã�� ����� �� ��忡 ����
		node->rlink = tmp; //���ο� ��带 ã�� ��忡 ����
		tmp->llink = node; //ã�� ��带 ���ο� ��忡 ����
	}

	else
	{
		printf("There is no List!\n");
	}

	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) {

	listNode *del = h->rlink;
	listNode *pre, *nxt;

	if (h) //����Ʈ�� �������� �˻�
	{
		if (h->rlink == h) { //��忡 ���� ���� �ϳ��� ���ٸ�
			printf("There is nothing to delete!\n");
			return 1;
		}

		while (del->key != key) //key���� ����ִ� ��带 ã�� ����
		{
			del = del->rlink; //del�� ��ġ�� ���� ���� ����
			if (del == h) //key���� �ִ� ��尡 ���� �� ���� �� ���̹Ƿ� �̶��� ���� ���
			{
				printf("Cannot find node with key value!\n");
				return 0;
			}
		}

		pre = del->llink; //������ ����� �� ��带 ����Ű�� ��
		nxt = del->rlink; //������ ����� �� ��带 ����Ű�� ��
		free(del); //��� ����

		pre->rlink = nxt; //������ ��� ���� ��带 ���� ���� ����
		nxt->llink = pre; //������ ��� ���� ��带 ���� ���� ����
	}

	else
	{
		printf("There is no List!\n");
	}

	return 0;
}