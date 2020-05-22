/*
 * Binary Search Tree #1
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

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
 {
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do {
		printf("\n\n");
		printf("-------------------- [�赿��]   [2019038077] -------------------\n");
		printf("----------------------------------------------------------------\n");
		printf("                     Binary Search Tree #1                      \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
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
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
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
	return 1;
}



void inorderTraversal(Node* ptr)
{
	if (ptr) //����������� �Ǻ�
	{
		inorderTraversal(ptr->left); //���� �ڽ����� �̵�(ó������ ������ ����������)
		printf(" [%d] ", ptr->key); //�ش� ��� ���
		inorderTraversal(ptr->right); //������ �ڽ����� �̵�(���� �ڽİ� �θ� ��带 ����� �� �̵�)
	}
}

void preorderTraversal(Node* ptr)
{
	if (ptr) //����������� �Ǻ�
	{
		printf(" [%d] ", ptr->key); //�ش� ��� ���(ó������ root���)
		preorderTraversal(ptr->left); //���� �ڽ����� �̵�(root��� ��� �ڿ��� �� ������ ���� ������ �̵�)
		preorderTraversal(ptr->right); //������ �ڽ����� �̵�(�θ� ���� ���� �ڽ� ��带 ����� �� �̵�)
	}
}

void postorderTraversal(Node* ptr)
{
	if (ptr) //����������� �Ǻ�
	{
		preorderTraversal(ptr->left); //���� �ڽ� ���� �̵�(ó������ �� ������ ���� ������ �̵�)
		preorderTraversal(ptr->right); //������ �ڽ� ���� �̵�
		printf(" [%d] ", ptr->key); //�ش� ��� ���
	}
}


int insert(Node* head, int key)
{
	Node *New, *temp;
	New = (Node*)malloc(sizeof(Node)); //���ο� ��� ����
	New->key = key; //�޾ƿ� Ű �� ����
	New->left = NULL;
	New->right = NULL;

	if (key == head->key) {
		printf("It already exists in Tree!\n");
		return 1;
	}
	if (!(head->left)) { //��尡 �ϳ��� ���ٸ�
		head->left = New; //��� ���� ���ο� ��带 ����
		return 0;
	}

	head = head->left;
	while (head) //�θ� ���(temp)�� ���� ����� ��(�̵��� �ڽ� ��尡 NULL�̹Ƿ�)
	{
		temp = head; //�θ� ����� ��ġ ���
		if (key < head->key) { //key���� �ش����� ������ ������ 
			head = head->left; //�ش� ��带 ���� �ڽĳ��� �̵�
		}
		else { //key���� �ش����� ������ ũ��
			head = head->right; //�ش� ��带 ������ �ڽĳ��� �̵�
		}
	}

	if (key < temp->key) { //key���� �ش����� ������ ������ 
		temp->left = New; //�ش� ��带 ���� �ڽĳ��� �̵�
	}
	else { //key���� �ش����� ������ ũ��
		temp->right = New; //�ش� ��带 ������ �ڽĳ��� �̵�
	}
	return 0;
}

int deleteLeafNode(Node* head, int key)
{
	Node *del, *temp;
	int x;

	head = head->left; //root���� �̵�
	while (head)
	{
		if (key == head->key) {
			break; //key���� �ش� ����� ���� ������ �ݺ� ����
		}
		if (key < head->key) { //key���� �ش����� ������ ������ 
			temp = head;
			head = head->left; //�ش� ��带 ���� �ڽĳ��� �̵�
			x = 0;
		}
		else { //key���� �ش����� ������ ũ��
			temp = head;
			head = head->right; //�ش� ��带 ������ �ڽĳ��� �̵�
			x = 1;
		}
	}

	if (!del->left && !del->right) { //��������̸�
		free(head); //�Ҵ�����
		if (x == 0)
			temp->left = NULL;
		return 0;
	}
	else
		printf("the node [%d] is not a leaf\n", key);
	return 1;
}

Node* searchRecursive(Node* ptr, int key)
{
	if (!ptr) return NULL; //Ʈ���� ���� ��� NULL��ȯ
	if (key == ptr->key) return ptr; //key���� �ش� ����� ���� ������ �ش� ��� ��ȯ
	if (key < ptr->key) return searchRecursive(ptr->left, key); //key���� �ش����� ������ ������ �ش� ��带 ���� �ڽĳ��� �̵�
	else return searchRecursive(ptr->right, key); //key���� �ش����� ������ ũ�� �ش� ��带 ������ �ڽĳ��� �̵�
	return NULL;
}

Node* searchIterative(Node* head, int key)
{
	if (!head)
	{
		return NULL;
	}

	head = head->left;
	while (head)
	{
		if (key == head->key) return head; //key���� �ش� ����� ���� ������ �ش� ��� ��ȯ
		if (key < head->key) { //key���� �ش����� ������ ������ 
			head = head->left; //�ش� ��带 ���� �ڽĳ��� �̵�
		}
		else { //key���� �ش����� ������ ũ��
			head = head->right; //�ش� ��带 ������ �ڽĳ��� �̵�
		}
	}
	return NULL;
}


int freeBST(Node* head)
{
	Node *ptr = head;

	if (!ptr) //������ ��尡 ���� ���
	{
		printf("There is no Tree!\n"); //���� ���
		return 1;
	}
	/*������ȸ ����� �����ͼ� �ϳ��� ����*/
	else
	{
		if (ptr) //����������� �Ǻ�
		{
			freeBST(ptr->left); //���� �ڽ� ���� �̵�(ó������ �� ������ ���� ������ �̵�)
			freeBST(ptr->right); //������ �ڽ� ���� �̵�
			free(ptr); //�ش� ��� ���
		}
	}
	free(head);
	return 0;
}




