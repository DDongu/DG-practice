/*
프로그램 : Term-Progect
작성자 : 김동규
학과 : 소프트웨어학과
학번 : 2019038077
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_VERTEX 20 /* you can change value 20 */


/*구조체*/
typedef struct Vertex {
	int num; /* vertex number */
	struct Vertex* link; /* link to a next adjacent vertext */
} Vertex;

typedef struct VertexHead {
	Vertex* head; /* linked list of all adjacent vertices */
} VertexHead;

typedef struct Graph {
	VertexHead* vlist; /* list of all vertices: vlist[MAX_VERTEX] */
} Graph;

//큐
int queue[MAX_VERTEX] = { 0 };
int front = 0;
int rear = 0;

//스택
int stack[MAX_VERTEX] = { 0 };
int top = -1;


/*함수 프로토타입*/
int createGraph(Graph** list); /* empty graph creation */
int destroyGraph(Graph* list); /* deallocating all allocated memory */
int insertVertex(Graph* list, int key); /* vertex insertion */
int deleteVertex(Graph* list, int key); /* vertex deletion */
int insertEdge(Graph* list, int key1, int key2); /* new edge creation between two vertices */
int deleteEdge(Graph* list, int key1, int key2); /* edge removal */
int depthFS(Graph* list, int key); /* depth first search using stack || DFS pre-order 방식*/
int breadthFS(Graph* list, int key); /* breadth first search using queue || BFS level-order 방식*/
int printGraph(Graph* list); /* printing graph with vertices and edges || 각 노드간에 관계 즉 엣지 보여주기*/

//추가 구현 함수
void enQueue(int item);
int deQueue();

int visit(Graph* list, int key);

int main()
{
	char command;
	int key1, key2;
	Graph* list = NULL;

	do {
		printf("\n------------------ [김동규]   [2019038077] -------------------\n");
		printf("----------------------------------------------------------------\n");
		printf("                            Graph                               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Creat Graph    = z          Destroy Graph   = x\n");
		printf(" Insert Vertex  = i          Delete Vertex   = d\n");
		printf(" Insert Edge    = n          Delete Edge     = t\n");
		printf(" Depth FS       = f          Print Graph     = p\n");
		printf(" Breadth FS     = e          Quit            = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			createGraph(&list);
			break;
		case 'x': case 'X':
			destroyGraph(&list);
			break;
		case 'i': case 'I':
			printf("Vertex Key = ");
			scanf("%d", &key1);
			insertVertex(list, key1);
			break;
			break;
		case 'd': case 'D':
			printf("Vertex Key = ");
			scanf("%d", &key1);
			deleteVertex(list, key1);
			break;
		case 'n': case 'N':
			printf("Vertex Number 1 = ");
			scanf("%d", &key1);
			printf("Vertex Number 2 = ");
			scanf("%d", &key2);
			insertEdge(list, key1, key2);
			break;
		case 't': case 'T':
			printf("Vertex Number 1 = ");
			scanf("%d", &key1);
			printf("Vertex Number 2 = ");
			scanf("%d", &key2);
			deleteEdge(list, key1, key2);
			break;
		case 'f': case 'F':
			//depthFS()
			break;
		case 'p': case 'P':
			printGraph(list);
			break;
		case 'e': case 'E':
			//breadthFS()
			break;
		case 'q': case 'Q':
			return 0;
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int createGraph(Graph** list) 
{
	//그래프가 비어있지 않은 경우
	if (*list != NULL)
		destroyGraph(list);
	*list = (Graph*)malloc(sizeof(Graph));
	(*list)->vlist = (VertexHead*)malloc(sizeof(VertexHead) * MAX_VERTEX);

	for (int i = 0; i < MAX_VERTEX; i++) {
		(*list)->vlist[i].head = NULL;
	}

	return 0;
}

int destroyGraph(Graph** list)
{

	if (list == NULL) {
		printf("The Graph already empty.");
		return 1;
	}

	for (int i = 0; i < MAX_VERTEX; i++) {
		if ((*list)->vlist[i].head != NULL)
			deleteVertex(*list, (*list)->vlist[i].head->num);
	}

	free((*list)->vlist);
	free(*list);
	*list = NULL;

	return 0;
}

int insertVertex(Graph* list, int key) {

	if (list == NULL) {
		printf("The Graph is not created yet.");
		return 1;
	}

	Vertex* newvertex = (Vertex*)malloc(sizeof(Vertex));

	newvertex->num = key;
	newvertex->link = NULL;

	int i = 0;
	while (i != MAX_VERTEX) {

		if (list->vlist[i].head == NULL) break;
		i++;
	}

	list->vlist[i].head = newvertex;

	return 0;
}

int deleteVertex(Graph* list, int key) {

	if (list == NULL) {
		printf("There is no Graph.");
		return 1;
	}

	Vertex* head;
	int i = 0;

	while (1) {
		if (list->vlist[i].head != NULL) {
			if (list->vlist[i].head->num == key) {
				head = list->vlist[i].head;
				break;
			}
		}

		i++;

		if (i == MAX_VERTEX) {
			printf("There is no key you find");
			return 1;
		}
	}

	//해당 vertex가 포함된 엣지들을 모두 삭제해야한다.
	int edgh[MAX_VERTEX] = { 0 };
	Vertex* next = head;

	for (int k = 0; k < MAX_VERTEX; k++) {

		if (next->link == NULL) break;
		next = next->link;
		edgh[k] = next->num;
	}

	int j = 0;

	while (edgh[j] != 0) {
		deleteEdge(list, key, edgh[j]);
		j++;
	}

	free(head);
	list->vlist[i].head = NULL;
	return 0;
}

int insertEdge(Graph* list, int key1, int key2) {

	if (list == NULL) {
		printf("The Graph is not created yet.");
		return 1;
	}

	Vertex* one;
	Vertex* two;

	for (int i = 0; i < MAX_VERTEX + 1; i++) {
		if (i == MAX_VERTEX) {
			printf("There is no Key you find");
			return 1;
		}

		if (list->vlist[i].head->num == key1) {
			one = list->vlist[i].head;
			break;
		}
	}

	for (int i = 0; i < MAX_VERTEX + 1; i++) {
		if (i == MAX_VERTEX) {
			printf("There is no Key you find");
			return 1;
		}

		if (list->vlist[i].head->num == key2) {
			two = list->vlist[i].head;
			break;
		}
	}

	//key1값에 해당되는 vertex값에 key2 엣지 추가
	Vertex* key_1 = (Vertex*)malloc(sizeof(Vertex));
	key_1->link = NULL;

	Vertex* next1 = one;

	while (1) {
		if (next1->link == NULL) {
			key_1->num = key2;
			next1->link = key_1;
			break;
		}
		next1 = next1->link;
	}

	//key2값에 해당되는 vertex값에 key1 엣지 추가
	Vertex* key_2 = (Vertex*)malloc(sizeof(Vertex));
	key_2->link = NULL;

	Vertex* next2 = two;

	while (1) {
		if (next2->link == NULL) {
			key_2->num = key1;
			next2->link = key_2;
			break;
		}
		next2 = next2->link;
	}

	return 0;
}

int deleteEdge(Graph* list, int key1, int key2) {

	if (list == NULL) {
		printf("The Graph is not created yet.");
		return 1;
	}

	//key1값에 해당되는 vertex에 key2에 해당하는 엣지 값을 제거
	Vertex* post_1;
	Vertex* pre_1;
	Vertex* next_1;

	for (int i = 0; i < MAX_VERTEX + 1; i++) {
		if (i == MAX_VERTEX) {
			printf("There is no Key you find");
			return 1;
		}

		if (list->vlist[i].head->num == key1) {
			post_1 = list->vlist[i].head;
			pre_1 = post_1->link;
			next_1 = pre_1->link;
			break;
		}
	}

	while (pre_1 != NULL) {
		if (pre_1->num == key2) {
			post_1->link = next_1;
			pre_1->link = NULL;
			free(pre_1);
			break;
		}
		post_1 = pre_1;
		pre_1 = next_1;
		next_1 = next_1->link;
	}

	//key2값에 해당되는 vertex에 key1에 해당하는 엣지 값을 제거
	Vertex* post_2;
	Vertex* pre_2;
	Vertex* next_2;

	for (int i = 0; i < MAX_VERTEX + 1; i++) {
		if (i == MAX_VERTEX) {
			printf("There is no Key you find");
			return 1;
		}

		if (list->vlist[i].head->num == key2) {
			post_2 = list->vlist[i].head;
			pre_2 = post_2->link;
			next_2 = pre_2->link;
			break;
		}
	}

	while (pre_2 != NULL) {
		if (pre_2->num == key1) {
			post_2->link = next_2;
			pre_2->link = NULL;
			free(pre_2);
			break;
		}
		post_2 = pre_2;
		pre_2 = next_2;
		next_2 = next_2->link;
	}

	return 0;
}

int printGraph(Graph* list) {

	if (list == NULL) {
		printf("The Graph is not created yet.");
		return 1;
	}

	Vertex* printv;

	printf("   Vertex head\n");
	printf("===================================\n");
	for (int i = 0; i < MAX_VERTEX; i++) {

		if (list->vlist[i].head != NULL) {

			printv = list->vlist[i].head;
			printf("   ");
			for (int j = 0; j < MAX_VERTEX; j++) {
				printf("[%d] -> ", printv->num);
				printv = printv->link;

				if (printv == NULL) {
					printf("[NULL]\n");
					break;
				}
			}
		}
	}
}

void enQueue(int item) {
	rear = (rear + 1) % MAX_VERTEX;//rear를 한칸 뒤로 옮긴 후
	queue[rear] = item;//해당 rear에 새로운 item값을 저장
}

int deQueue() {
	front = (front + 1) % MAX_VERTEX;//있으면 front값을 한칸 뒤로
	return queue[front]; 
}


int visit(Graph* list, int key) { //키 값에 해당하는 그래프의 정점 반환
	for (int i = 0; i < MAX_VERTEX; i++)
	{
		if (list->vlist[i].head->num == key)
		{
			return i;
		}
	}
}