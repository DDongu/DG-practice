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
 /* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
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
		printf("\n------------------- [김동규]   [2019038077] ------------------\n");
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

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;	
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h) {

	listNode *tmp, *last = h->rlink, *del;
	del = h->rlink; //해제할 노드의 다음 노드를 가리키게 함

	/*마지막 노드를 찾기 위한 loop문*/
	while (last->rlink != h)//마지막 노드의 rlink는 헤드노드이기 때문
	{
		last = last->rlink; //다음 노드로 이동
	}

	while (del != h) {
		tmp = del->rlink; //해제할 노드의 다음 노드를 가리키게 함
		free(del); //노드 해제
		del = tmp; //해제한 노드의 다음 노드를 가리키게 함
	}
	free(del);//남은 마지막 노드(헤드 노드) 해제
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
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

	listNode *node, *last = h->rlink;
	node = (listNode*)malloc(sizeof(listNode)); //받은 값을 저장 시킬 노드 생성
	node->key = key;
	
	if (h) //리스트의 존재유무 검사
	{
		if (h->rlink == h) { //노드에 들어온 값이 하나도 없다면
			h->rlink = node; //헤드 노드를 새로운 노드에 연결
			h->llink = node; //헤드 노드를 새로운 노드에 연결
			node->llink = h; //새로운 노드를 헤드 노드에 연결
			node->rlink = h; //새로운 노드를 헤드 노드에 연결
			return 1;
		}

		/*마지막 노드를 찾기 위한 loop문*/
		while (last->rlink != h)//마지막 노드의 rlink는 헤드노드이기 때문
		{
			last = last->rlink; //다음 노드로 이동
		}
		
		last->rlink = node; //마지막 노드를 새로운 노드에 연결
		node->llink = last; //새로운 노드를 마지막 노드에 연결
		h->llink = node; //헤드 노드를 새로운 노드에 연결
		node->rlink = h; //새로운 노드를 헤드 노드에 연결
	}

	else
	{
		printf("There is no List!\n");
	}
	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

	listNode *last = h->rlink, *pre;

	if (h) //리스트의 존재유무 검사
	{
		if (h->rlink == h) { //노드에 들어온 값이 하나도 없다면
			printf("There is nothing to delete!\n");
			return 1;
		}

		/*마지막 노드를 찾기 위한 loop문*/
		while (last->rlink != h)//마지막 노드의 rlink는 헤드노드이기 때문
		{
			last = last->rlink; //다음 노드로 이동
		}
		pre = last->llink; //마지막 이전의 노드를 가리키게 함
		free(last); //마지막 노드 해제

		if (h->rlink == NULL) //이때는 노드가 없을 경우이다. 
		{
			h->rlink = h; //헤드를 초기화된 상태로
			h->llink = h; //헤드를 초기화된 상태로
			return 1; //따라서 그대로 종료
		}
		
		else
		{
			pre->rlink = h; //마지막 노드가 된 pre를 헤드 노드에 연결
			h->llink = pre; //헤드 노드를 pre 노드에 연결
		}
	}

	else
	{
		printf("There is no List!\n");
	}

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

	listNode *node;
	node = (listNode*)malloc(sizeof(listNode)); //받은 값을 저장 시킬 노드 생성
	node->key = key; //노드에 key값 저장

	if (h) //리스트의 존재유무 검사
	{
		if (h->rlink == h) { //노드에 들어온 값이 하나도 없다면
			h->rlink = node; //헤드 노드를 새로운 노드에 연결
			h->llink = node; //헤드 노드를 새로운 노드에 연결
			node->llink = h; //새로운 노드를 헤드 노드에 연결
			node->rlink = h; //새로운 노드를 헤드 노드에 연결
			return 1;
		}

		h->rlink->llink = node; //헤드 노드를 제외한 맨 앞 노드를 새로운 노드에 연결
		node->rlink = h->rlink; //새로운 노드를 헤드 노드를 제외한 맨 앞 노드에 연결
		h->rlink = node; //헤드 노드를 새로운 노드에 연결
		node->llink = h; //새로운 노드를 헤드 노드에 연결
	}

	else
	{
		printf("There is no List!\n");
	}

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	listNode *del, *nxt;

	if (h) //리스트의 존재유무 검사
	{
		if (h->rlink == h) { //노드에 들어온 값이 하나도 없다면
			printf("There is nothing to delete!\n");
			return 1;
		}

		del = h->rlink; //맨 앞 노드를 가리키게 함
		nxt = del->rlink; //해제할 노드의 다음 노드를 가리키게 함
		free(del); //노드 해제

		if (h->rlink == NULL) //이때는 노드가 하나 밖에 안남았을 경우이다.
		{
			h->rlink = h; //헤드를 초기화된 상태로
			h->llink = h; //헤드를 초기화된 상태로
			return 1;//따라서 그대로 종료
		}

		else
		{
			h->rlink = nxt; //헤드 노드를 맨 앞 노드와 연결
			nxt->llink = h; //맨 앞 노드를 헤드 노드와 연결
		}
	}

	else
	{
		printf("There is no List!\n");
	}

	return 1;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {

	listNode *x = h->rlink, *tmp;
	listNode *k = h->llink; //바꾸기 전 리스트의 마지막 노드를 기억하는 포인터

	while (h->rlink != k) //노드의 순서를 뒤집어주고 헤드까지 뒤집어주고 나면, h->rlink는 바꾸기 전 맨 앞 노드에서 바꾸기 전 맨 뒤 노드로 바뀜
	{					  //따라서 h->rlink == k 즉, 바뀐 뒤 맨 앞 노드 == 바뀌기 전 마지막 노드 일 때 loop 종료
		
		/*노드의 llink와 rlink를 뒤집는 과정*/
		tmp = x->llink; //x->llink를 임시저장
		x->llink = x->rlink; //x->llink와 x->rlink를 swap
		x->rlink = tmp; //x->llink와 x->rlink를 swap

		x = x->llink; //x를 다음 노드로 이동
	}

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {

	listNode *tmp = h->rlink, *pre;
	listNode *node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	if (h) //리스트의 존재유무 검사
	{
		if (h->rlink == h) { //노드에 들어온 값이 하나도 없다면
			h->rlink = node; //헤드 노드를 새로운 노드에 연결
			h->llink = node; //헤드 노드를 새로운 노드에 연결
			node->llink = h; //새로운 노드를 헤드 노드에 연결
			node->rlink = h; //새로운 노드를 헤드 노드에 연결
			return 1;
		}

		while (tmp->key <= key) //key값보다 큰 값을 가진 노드를 찾는 loop문
		{
			tmp = tmp->rlink; //다음 노드로 이동
			if (tmp == h) //key값보다 큰 값이 없다면 tmp는 리스트를 한 바퀴 돌고 헤드를 가리키게 됨
			{
				break; //이때 loop문 탈출
			}
		}
		pre = tmp->llink; //찾은 노드의 앞 노드
		
		pre->rlink = node; //찾은 노드의 앞 노드를 새로운 노드에 연결
		node->llink = pre; //새로운 노드를 찾은 노드의 앞 노드에 연결
		node->rlink = tmp; //새로운 노드를 찾은 노드에 연결
		tmp->llink = node; //찾은 노드를 새로운 노드에 연결
	}

	else
	{
		printf("There is no List!\n");
	}

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	listNode *del = h->rlink;
	listNode *pre, *nxt;

	if (h) //리스트의 존재유무 검사
	{
		if (h->rlink == h) { //노드에 들어온 값이 하나도 없다면
			printf("There is nothing to delete!\n");
			return 1;
		}

		while (del->key != key) //key값이 들어있는 노드를 찾는 조건
		{
			del = del->rlink; //del의 위치를 다음 노드로 수정
			if (del == h) //key값이 있는 노드가 없어 한 바퀴 돈 것이므로 이때는 에려 출력
			{
				printf("Cannot find node with key value!\n");
				return 0;
			}
		}

		pre = del->llink; //삭제될 노드의 전 노드를 가리키게 함
		nxt = del->rlink; //삭제된 노드의 후 노드를 가리키게 함
		free(del); //노드 해제

		pre->rlink = nxt; //삭제된 노드 전의 노드를 뒤의 노드와 연결
		nxt->llink = pre; //삭제된 노드 뒤의 노드를 전의 노드와 연결
	}

	else
	{
		printf("There is no List!\n");
	}

	return 0;
}