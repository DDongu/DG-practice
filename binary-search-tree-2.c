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

int LeftMax(Node* head); //왼쪽 트리에서 가장 큰 값을 찾는 함수

int main()
{
	char command;
	int key;
	Node* head = NULL;

	do {
		printf("\n\n");
		printf("-------------------- [김동규]   [2019038077] -------------------\n");
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
	if (!node) { //트리가 없으면 함수 종료
			printf("There is no Tree!\n");
			return; 
		}

	while (1)
	{
		for (; node; node = node->left) { //왼쪽 자식 노드로 이동하면서 이동한 노드가 비었는지 체크
			push(node); //스택에 노드 삽입
		}
		node = pop(); //스택에서 노드 삭제

		if (!node) break; //스택이 공백일 때

		printf(" [%d] ", node->key); //노드 값 출력
		node = node->right; //오른쪽 자식으로 이동
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	if (!ptr) { //트리가 없으면 함수 종료
		printf("There is no Tree!\n");
		return; 
	}
	enQueue(ptr); //큐에 헤드 노드 삽입

	while (1)
	{
		ptr = deQueue(); //큐에 있는 노드 가져오기
		if (ptr) //큐에서 노드을 어느 하나를 가져왔으면
		{
			printf(" [%d] ", ptr->key); //노드의 값 출력
			if (ptr->left) enQueue(ptr->left); //노드의 왼쪽 자식노드를 큐에 삽입
			if (ptr->right) enQueue(ptr->right); //노드의 오른쪽 자식노드를 큐에 삽입
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

	del = head->left; //root노드로 이동

	if(!del){
		printf("There is no Tree!\n");
		return 1;
	}

	while (del)
	{
		/*key과 같은 값을 가진 노드를 찾았을 때*/
		if (del->key == key) { 
			/*삭제할 노드가 왼쪽 자식 노드를 가질 때*/
			if (del->left) { 
				if (del->right) { //오른쪽 자식 노드도 있을 때(자식 노드가 2개) <case 3>
					tmp = LeftMax(del); //삭제할 노드의 왼쪽 트리에서 가장 큰 값 반환
					del->key = tmp; //위 함수를 통해서 받아온 가장 큰 값을 해당 노드에 저장
					return 0;
				}

				else { //오른쪽 자식 노드는 없을 때(자식 노드가 1개) <case 2>
					/*삭제할 노드가 부모 노드의 어디 노드인지 찾기*/
					if (x == -1) { //왼쪽 자식일 때
						parent->left = del->left; //부모의 left와 del의 왼쪽 자식을 연결
						free(del); //노드 삭제
					}
					else { //오른쪽 자식 일때
						parent->right = del->left;
						free(del); //노드 삭제
					}
					return 0;
				}
			}

			/*삭제할 노드가 오른쪽 자식 노드를 가질 때*/
			else if (del->right) {
			//왼쪽 자식 노드는 없을 때(자식 노드가 1개) <case 2>
				/*삭제할 노드가 부모 노드의 어디 노드인지 찾기*/
				if (x == -1) { //왼쪽 자식일 때
					parent->left = del->right; //부모의 right와 del의 왼쪽 자식을 연결
					free(del); //노드 삭제
				}
				else { //오른쪽 자식 일때
					parent->right = del->right; //부모의 right와 del의 오른쪽 자식을 연결
					free(del); //노드 삭제
				}
				return 0;	
			}

			else { //자식 노드가 없을 때 == 리프 노드일 때 <case 1>
				free(del); //노드 삭제
				if (x == -1) //삭제된 노드가 부모의 왼쪽 자식 노드일 때
					parent->left = NULL;
				else //삭제된 노드가 부모의 오른쪽 자식 노드일 때
					parent->right = NULL;
				return 0;
			}
		}

		else if (key < del->key) { //key값이 해당노드의 값보다 작으면 
			parent = del;
			del = del->left; //해당 노드를 왼쪽 자식노드로 이동
			x = -1;
		}

		else { //key값이 해당노드의 값보다 크면
			parent = del;
			del = del->right; //해당 노드를 오른쪽 자식노드로 이동
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
	if (top == -1) //스택이 비어있으므로
		return NULL; //NULL반환
	else {
		x = stack[top--]; //스택에 top의 값을 꺼낸 뒤, top을 하나 밑으로 이동
	}
	return x;
}

void push(Node* aNode)
{
	stack[++top] = aNode; //top을 하나 키우고 key값을 스택에 삽입
}



Node* deQueue()
{
	if (front == rear) //스택이 비어있으므로
		return 0;
	else
	{
		front = (front + 1) % MAX_QUEUE_SIZE; //front가 이동하면서 끝에 도달하면 다시 앞으로 도달하기 위한 코드
		return queue[front]; //맨 앞의 값 지우기
	}

	return 0;
}

void enQueue(Node* aNode)
{
	Node* x;
	x = rear;
	rear = (rear + 1) % MAX_QUEUE_SIZE; //rear이 이동하면서 끝에 도달하면 다시 앞으로 도달하기 위한 코드

	if (rear == front) //스택이 꽉 찼으므로
	{
		printf("Queue is full!\n"); //에러 메세지 출력
		rear = x;
	}

	else
	{
		queue[rear] = aNode; //큐의 rear자리에 key값 삽입
	}
}

int LeftMax(Node* head) //왼쪽 트리에서 가장 큰 값을 찾는 함수
{
	Node* P = head; //부모 노드 위치 저장할 포인터 
	int key = 0;
	head = head->left; //왼쪽 트리로 이동 
	
	/*함수로 넘겨준 del 노드 밑으로 level이 1개 밖에 없을 때*/
	if (head->right == NULL) { //리프 노드라면(가장 큰 값을 가진 노드)
			key = head->key; //리프 노드의 값을 따로 저장(가장 큰 값을 따로 저장)
			free(head); //리프 노드 삭제(가장 큰 값을 가진 노드 삭제)
			P->left = NULL; //부모 노드의 left를 NULL로 변경(왼쪽 트리 중 가장 큰 것이라서 처음에는 왼쪽 자식으로 이동했었기 때문)
			return key; //key값(가장 큰 값) 반환
		}

	/*함수로 넘겨준 del 노드 밑으로 level이 2개 이상일 때*/
	P = head; //부모 노드 수정
	head = head->right; //오른쪽 자식으로 이동
	while (1)
	{
		if (head->right == NULL) { //리프 노드라면(가장 큰 값을 가진 노드)
			key = head->key; //리프 노드의 값을 따로 저장(가장 큰 값을 따로 저장) 
			free(head); //리프 노드 삭제(가장 큰 값을 가진 노드 삭제)
			P->right = NULL; //부모 노드의 right를 NULL로 변경
			return key; //key값(가장 큰 값) 반환
		}
		P = head; //이동시킬 노드의 부모 노드 == 현재 노드
		head = head->right;	//오른쪽 자식으로 이동(오른쪽 자식은 부모 노드보다 큰 값을 가지기 때문)
	}
	return -9999;
}