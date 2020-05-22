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
		printf("-------------------- [김동규]   [2019038077] -------------------\n");
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
	if (ptr) //리프노드인지 판별
	{
		inorderTraversal(ptr->left); //왼쪽 자식으로 이동(처음에는 왼쪽의 리프노드까지)
		printf(" [%d] ", ptr->key); //해당 노드 출력
		inorderTraversal(ptr->right); //오른쪽 자식으로 이동(왼쪽 자식과 부모 노드를 출력한 뒤 이동)
	}
}

void preorderTraversal(Node* ptr)
{
	if (ptr) //리프노드인지 판별
	{
		printf(" [%d] ", ptr->key); //해당 노드 출력(처음에는 root노드)
		preorderTraversal(ptr->left); //왼쪽 자식으로 이동(root노드 출력 뒤에는 맨 왼쪽의 리프 노드까지 이동)
		preorderTraversal(ptr->right); //오른쪽 자식으로 이동(부모 모드와 왼쪽 자식 노드를 출력한 뒤 이동)
	}
}

void postorderTraversal(Node* ptr)
{
	if (ptr) //리프노드인지 판별
	{
		preorderTraversal(ptr->left); //왼쪽 자식 노드로 이동(처음에는 맨 왼쪽의 리프 노드까지 이동)
		preorderTraversal(ptr->right); //오른쪽 자식 노드로 이동
		printf(" [%d] ", ptr->key); //해당 노드 출력
	}
}


int insert(Node* head, int key)
{
	Node *New, *temp;
	New = (Node*)malloc(sizeof(Node)); //새로운 노드 생성
	New->key = key; //받아온 키 값 저장
	New->left = NULL;
	New->right = NULL;

	if (key == head->key) {
		printf("It already exists in Tree!\n");
		return 1;
	}
	if (!(head->left)) { //노드가 하나도 없다면
		head->left = New; //헤느 노드와 새로운 노드를 연결
		return 0;
	}

	head = head->left;
	while (head) //부모 노드(temp)가 리프 노드일 때(이동한 자식 노드가 NULL이므로)
	{
		temp = head; //부모 노드의 위치 기억
		if (key < head->key) { //key값이 해당노드의 값보다 작으면 
			head = head->left; //해당 노드를 왼쪽 자식노드로 이동
		}
		else { //key값이 해당노드의 값보다 크면
			head = head->right; //해당 노드를 오른쪽 자식노드로 이동
		}
	}

	if (key < temp->key) { //key값이 해당노드의 값보다 작으면 
		temp->left = New; //해당 노드를 왼쪽 자식노드로 이동
	}
	else { //key값이 해당노드의 값보다 크면
		temp->right = New; //해당 노드를 오른쪽 자식노드로 이동
	}
	return 0;
}

int deleteLeafNode(Node* head, int key)
{
	Node *del, *temp;
	int x;

	head = head->left; //root노드로 이동
	while (head)
	{
		if (key == head->key) {
			break; //key값과 해당 노드의 값이 같으면 반복 중지
		}
		if (key < head->key) { //key값이 해당노드의 값보다 작으면 
			temp = head;
			head = head->left; //해당 노드를 왼쪽 자식노드로 이동
			x = 0;
		}
		else { //key값이 해당노드의 값보다 크면
			temp = head;
			head = head->right; //해당 노드를 오른쪽 자식노드로 이동
			x = 1;
		}
	}

	if (!del->left && !del->right) { //리프노드이면
		free(head); //할당해제
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
	if (!ptr) return NULL; //트리가 없을 경우 NULL반환
	if (key == ptr->key) return ptr; //key값과 해당 노드의 값이 같으면 해당 노드 반환
	if (key < ptr->key) return searchRecursive(ptr->left, key); //key값이 해당노드의 값보다 작으면 해당 노드를 왼쪽 자식노드로 이동
	else return searchRecursive(ptr->right, key); //key값이 해당노드의 값보다 크면 해당 노드를 오른쪽 자식노드로 이동
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
		if (key == head->key) return head; //key값과 해당 노드의 값이 같으면 해당 노드 반환
		if (key < head->key) { //key값이 해당노드의 값보다 작으면 
			head = head->left; //해당 노드를 왼쪽 자식노드로 이동
		}
		else { //key값이 해당노드의 값보다 크면
			head = head->right; //해당 노드를 오른쪽 자식노드로 이동
		}
	}
	return NULL;
}


int freeBST(Node* head)
{
	Node *ptr = head;

	if (!ptr) //해제할 노드가 없을 경우
	{
		printf("There is no Tree!\n"); //에러 출력
		return 1;
	}
	/*후위순회 방식을 가져와서 하나씩 해제*/
	else
	{
		if (ptr) //리프노드인지 판별
		{
			freeBST(ptr->left); //왼쪽 자식 노드로 이동(처음에는 맨 왼쪽의 리프 노드까지 이동)
			freeBST(ptr->right); //오른쪽 자식 노드로 이동
			free(ptr); //해당 노드 출력
		}
	}
	free(head);
	return 0;
}




