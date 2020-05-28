/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */

int LeftMax(Node* head); //���� Ʈ������ ���� ū ���� ã�� �Լ�

int main()
{
	char command;
	int key;
	Node* head = NULL;

	do {
		printf("\n\n");
		printf("-------------------- [�赿��]   [2019038077] -------------------\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if (ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)
{
	if (!node) { //Ʈ���� ������ �Լ� ����
			printf("There is no Tree!\n");
			return; 
		}

	while (1)
	{
		for (; node; node = node->left) { //���� �ڽ� ���� �̵��ϸ鼭 �̵��� ��尡 ������� üũ
			push(node); //���ÿ� ��� ����
		}
		node = pop(); //���ÿ��� ��� ����

		if (!node) break; //������ ������ ��

		printf(" [%d] ", node->key); //��� �� ���
		node = node->right; //������ �ڽ����� �̵�
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	if (!ptr) { //Ʈ���� ������ �Լ� ����
		printf("There is no Tree!\n");
		return; 
	}
	enQueue(ptr); //ť�� ��� ��� ����

	while (1)
	{
		ptr = deQueue(); //ť�� �ִ� ��� ��������
		if (ptr) //ť���� ����� ��� �ϳ��� ����������
		{
			printf(" [%d] ", ptr->key); //����� �� ���
			if (ptr->left) enQueue(ptr->left); //����� ���� �ڽĳ�带 ť�� ����
			if (ptr->right) enQueue(ptr->right); //����� ������ �ڽĳ�带 ť�� ����
		}
		else break;
	}

}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while (ptr != NULL) {

		/* if there is a node for the key, then just return */
		if (ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if (ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if (parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	Node *del = head, *parent = head;
	int x = -1, tmp = -9999;

	del = head->left; //root���� �̵�

	if(!del){
		printf("There is no Tree!\n");
		return 1;
	}

	while (del)
	{
		/*key�� ���� ���� ���� ��带 ã���� ��*/
		if (del->key == key) { 
			/*������ ��尡 ���� �ڽ� ��带 ���� ��*/
			if (del->left) { 
				if (del->right) { //������ �ڽ� ��嵵 ���� ��(�ڽ� ��尡 2��) <case 3>
					tmp = LeftMax(del); //������ ����� ���� Ʈ������ ���� ū �� ��ȯ
					del->key = tmp; //�� �Լ��� ���ؼ� �޾ƿ� ���� ū ���� �ش� ��忡 ����
					return 0;
				}

				else { //������ �ڽ� ���� ���� ��(�ڽ� ��尡 1��) <case 2>
					/*������ ��尡 �θ� ����� ��� ������� ã��*/
					if (x == -1) { //���� �ڽ��� ��
						parent->left = del->left; //�θ��� left�� del�� ���� �ڽ��� ����
						free(del); //��� ����
					}
					else { //������ �ڽ� �϶�
						parent->right = del->left;
						free(del); //��� ����
					}
					return 0;
				}
			}

			/*������ ��尡 ������ �ڽ� ��带 ���� ��*/
			else if (del->right) {
			//���� �ڽ� ���� ���� ��(�ڽ� ��尡 1��) <case 2>
				/*������ ��尡 �θ� ����� ��� ������� ã��*/
				if (x == -1) { //���� �ڽ��� ��
					parent->left = del->right; //�θ��� right�� del�� ���� �ڽ��� ����
					free(del); //��� ����
				}
				else { //������ �ڽ� �϶�
					parent->right = del->right; //�θ��� right�� del�� ������ �ڽ��� ����
					free(del); //��� ����
				}
				return 0;	
			}

			else { //�ڽ� ��尡 ���� �� == ���� ����� �� <case 1>
				free(del); //��� ����
				if (x == -1) //������ ��尡 �θ��� ���� �ڽ� ����� ��
					parent->left = NULL;
				else //������ ��尡 �θ��� ������ �ڽ� ����� ��
					parent->right = NULL;
				return 0;
			}
		}

		else if (key < del->key) { //key���� �ش����� ������ ������ 
			parent = del;
			del = del->left; //�ش� ��带 ���� �ڽĳ��� �̵�
			x = -1;
		}

		else { //key���� �ش����� ������ ũ��
			parent = del;
			del = del->right; //�ش� ��带 ������ �ڽĳ��� �̵�
			x = 1;
		}
	}

	printf("This Key is no there!\n");
	return 1;
}

void freeNode(Node* ptr)
{
	if (ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if (head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}

Node* pop()
{
	Node* x;
	if (top == -1) //������ ��������Ƿ�
		return NULL; //NULL��ȯ
	else {
		x = stack[top--]; //���ÿ� top�� ���� ���� ��, top�� �ϳ� ������ �̵�
	}
	return x;
}

void push(Node* aNode)
{
	stack[++top] = aNode; //top�� �ϳ� Ű��� key���� ���ÿ� ����
}



Node* deQueue()
{
	if (front == rear) //������ ��������Ƿ�
		return 0;
	else
	{
		front = (front + 1) % MAX_QUEUE_SIZE; //front�� �̵��ϸ鼭 ���� �����ϸ� �ٽ� ������ �����ϱ� ���� �ڵ�
		return queue[front]; //�� ���� �� �����
	}

	return 0;
}

void enQueue(Node* aNode)
{
	Node* x;
	x = rear;
	rear = (rear + 1) % MAX_QUEUE_SIZE; //rear�� �̵��ϸ鼭 ���� �����ϸ� �ٽ� ������ �����ϱ� ���� �ڵ�

	if (rear == front) //������ �� á���Ƿ�
	{
		printf("Queue is full!\n"); //���� �޼��� ���
		rear = x;
	}

	else
	{
		queue[rear] = aNode; //ť�� rear�ڸ��� key�� ����
	}
}

int LeftMax(Node* head) //���� Ʈ������ ���� ū ���� ã�� �Լ�
{
	Node* P = head; //�θ� ��� ��ġ ������ ������ 
	int key = 0;
	head = head->left; //���� Ʈ���� �̵� 
	
	/*�Լ��� �Ѱ��� del ��� ������ level�� 1�� �ۿ� ���� ��*/
	if (head->right == NULL) { //���� �����(���� ū ���� ���� ���)
			key = head->key; //���� ����� ���� ���� ����(���� ū ���� ���� ����)
			free(head); //���� ��� ����(���� ū ���� ���� ��� ����)
			P->left = NULL; //�θ� ����� left�� NULL�� ����(���� Ʈ�� �� ���� ū ���̶� ó������ ���� �ڽ����� �̵��߾��� ����)
			return key; //key��(���� ū ��) ��ȯ
		}

	/*�Լ��� �Ѱ��� del ��� ������ level�� 2�� �̻��� ��*/
	P = head; //�θ� ��� ����
	head = head->right; //������ �ڽ����� �̵�
	while (1)
	{
		if (head->right == NULL) { //���� �����(���� ū ���� ���� ���)
			key = head->key; //���� ����� ���� ���� ����(���� ū ���� ���� ����) 
			free(head); //���� ��� ����(���� ū ���� ���� ��� ����)
			P->right = NULL; //�θ� ����� right�� NULL�� ����
			return key; //key��(���� ū ��) ��ȯ
		}
		P = head; //�̵���ų ����� �θ� ��� == ���� ���
		head = head->right;	//������ �ڽ����� �̵�(������ �ڽ��� �θ� ��庸�� ū ���� ������ ����)
	}
	return -9999;
}