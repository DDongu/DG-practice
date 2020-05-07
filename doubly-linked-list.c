/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
    int key;
    struct Node* llink;
    struct Node* rlink;
} listNode;



typedef struct Head {
    struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
    char command;
    int key;
    headNode* headnode=NULL;

    do{
        printf("\n------------------- [김동규]   [2019038077] ------------------\n");
        printf("----------------------------------------------------------------\n");
        printf("                       Doubly Linked  List                      \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize    = z           Print         = p \n");
        printf(" Insert Node   = i           Delete Node   = d \n");
        printf(" Insert Last   = n           Delete Last   = e\n");
        printf(" Insert First  = f           Delete First  = t\n");
        printf(" Invert List   = r           Quit          = q\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch(command) {
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

    }while(command != 'q' && command != 'Q');

    return 1;
}


int initialize(headNode** h) {

    if(h != NULL) //리스트가 존재한다면
        freeList(h); //리스트를 모두 해제시킴

    *h = (headNode**)malloc(sizeof(headNode ));//헤드 노드 크기만큼 메모리 할당
    (*h)->first = NULL;
    return 1;
}

int freeList(headNode* h){
    
    /* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first; //노드를 하나씩 가리킬 포인터
	listNode* prev = NULL; //해제할 메모리 주소를 가리킬 포인터

	while (p != NULL) { //헤드가 비어있지 않다면 == 리스트가 존재 한다면
		prev = p;
		p = p->rlink;//p를 다음 노드로 옮김
		free(prev);//p가 다음으로 옮기기 전 노드를 해제
	}
	free(h);//헤드 노드 해제

    return 0;
}


void printList(headNode* h) {
    int i = 0;
    listNode* p;

    printf("\n---PRINT\n");

    if(h == NULL) {
        printf("Nothing to print....\n");
        return;
    }

    p = h->first;

    while(p != NULL) {
        printf("[ [%d]=%d ] ", i, p->key);
        p = p->rlink;
        i++;
    }

    printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

    listNode *p = h;
    listNode *node = (listNode*)malloc(sizeof(listNode)); //받은 값을 저장 시킬 노드 생성
    node->key = key; //노드에 받은 값 저장

    if(h)//리스트가 있는지 없는지 확인
    {
        if(h->first == NULL) //리스트에 노드가 하나도 없다면
        {
            h->first = node;//헤드와 새로운 노드를 연결
            node->llink = h->first;//새로운 노드의 llink를 새로운 노드 자신에게 연결
            node->rlink = node;//새로운 노드의 rlink를 새로운 노드 자신에게 연결

            return 0;
        }

        p->llink = node;//새로운 노드와 젤 앞의 노드를 연결
        while (p->rlink == h->first)
        {
            p = p->rlink;//리스트의 마지막 노드를 찾는 과정
        }
        
        p->rlink = node;//마지막 노드를 새로운 노드에 연결
        node->llink = p;//새로운 노드를 마지막 노드에 연결
        node->rlink = h->first;//새로운 노드를 제일 앞 노드와 연결
    }

    else
    {
        printf("There is no List!\n");
    }
    
    return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

    listNode *p = h;
    listNode *pre = NULL;

    if(h)
    {
        while(p->rlink != h)//마지막 노드를 찾는 조건문
        {
            pre = p;//해제하는 노드의 직전 노드 주소 저장
            p = p->rlink;//마지막 노드를 찾기 위해 p를 다음 노드로 옮기는 과정
        }
        free(p);//마지막 노드 메모리 해제
        
        pre->rlink = h->first;//삭제된 노드의 직전 노드를 제일 앞 노드와 연결
        p = h;//제일 앞 노드를 마지막 노드와 연결시키기 위해 p가 제일 앞 노드를 가리키게 함
        p->llink = pre;//제일 앞 노드를 마지막 노드에 연결
    }

    else
    {
        printf("There is no List!\n");
    }
    
    return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
    
    listNode *p = h;
    listNode *node = (listNode*)malloc(sizeof(listNode));//받은 값을 저장할 노드 생성
    node->key = key;//값을 생성한 노드에 저장

    if(h)
    {
        if(h->first == NULL) //리스트에 노드가 하나도 없다면
        {
            h->first = node;//헤드와 새로운 노드를 연결
            node->llink = h->first;//새로운 노드의 llink를 새로운 노드 자신에게 연결
            node->rlink = node;//새로운 노드의 rlink를 새로운 노드 자신에게 연결

            return 0;
        }   

        node->rlink = h->first;//새로운 노드를 제일 앞에 연결
        p->llink = node;//제일 앞 노드를 새로운 노드에 연결

        /*마지막 노드를 찾는 loop문*/
        while(p->rlink == h->first)
        {
            p = p->rlink;
        }

        node->llink = p;//새로운 노드를 마지막 노드에 연결
        p->rlink = node;//마지막 노드를 새로운 노드에 연결
    }

    else
    {
        printf("There is no List!\n");
    }
    
    return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

    listNode *p = h;//해제할 노드의 다음 노드를 가리킬 포인터
    listNode *pre = NULL;//해제할 노드를 가리킬 포인터

    if(h)
    {
        pre = p;//제일 앞 노드를 가리키게 함
        p = p->rlink;//p가 다음 노드를 가리키게 함
        free(pre);//제일 앞 노드 할당 해제

        pre = p;//pre가 제일 앞 노드를 가리키게 함
        /*마지막 노드를 찾는 loop문*/
        while(p->rlink == h->first)
        {
            p = p->rlink;
        }

        pre->llink = p;//삭제된 후 제일 앞 노드를, 마지막 노드에 연결
        p->rlink = pre;//마지막 노드를 삭제된 후 제일 앞 노드와 연결

    }

    else
    {
        printf("There is no List!\n");
    }
    

    return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

    listNode *p = h;
    listNode *tmp;

    if(h)
    {
        do
        {
            /*p가 가리키고 있는 노드의 rlink, llink를 swap*/
            tmp = p->rlink;
            p->rlink = p->llink;
            p->llink = tmp;

            p = p->llink;//p를 다음 노드로 옮김
        }while(p != h);//p가 헤드 노드를 가리키면 종료
        h->first = p->rlink;//리스트 역순 배치 전 마지막 노드를 헤드로 변경
    }

    else
    {
        printf("There is no List!\n");
    }
    
    
    return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

    listNode *node = (listNode*)malloc(sizeof(listNode));
    listNode *p = h, *pre = NULL;
    node->key = key;
    
    if(h)
    {
        if(h->first == NULL) //리스트에 노드가 하나도 없다면
        {
            h->first = node;//헤드와 새로운 노드를 연결
            node->llink = h->first;//새로운 노드의 llink를 새로운 노드 자신에게 연결
            node->rlink = node;//새로운 노드의 rlink를 새로운 노드 자신에게 연결

            return 0;
        }   

        if(p->rlink > key)//젤 앞 노드가 key 값보다 크면 == key 값이 가장 작으면
        {
            pre = p;//pre를 젤 앞 노드를 가리키게 함
            /*마지막 노드를 찾는 loop문*/
            while(p->rlink == h->first)
            {
                p = p->rlink;
            }
            node->rlink = pre;//새로운 노드를 젤 앞 노드에 연결
            pre->llink = node;//젤 앞 노드를 새로운 노드에 연결
            node->llink = p;//새로운 노드를 마지막 노드에 연결
            p->rlink = node;//마지막 노드를 새로운 노드에 연결
        }

        else
        {        
            /*key 값보다 큰 값을 찾는 loop문*/
            while(p->key <= key)
            {
                pre = p;
                p = p->rlink;
            }
            pre->rlink = node;//key보다 큰 값이 들어있는 노드의 직전 노드를 새로운 노드에 연결
            node->llink = pre;//새로운 노드를 key보다 큰 값이 들어있는 노드의 직전 노드에 연결
            p->llink = node;//key보다 큰 값이 들어있는 노드를 새로운 노드에 연결
            node->rlink = p;//새로운 노드를 key보다 큰 값이 들어있는 노드에 연결
        }
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
int deleteNode(headNode* h, int key) {

    listNode *p = h;
    listNode *temp;
    listNode *node = h;

    if(h)
    {
        /*젤 앞 노드가 key값과 같을 경우*/
        if(p->key == key)//제일 앞 노드의 값이 key와 같다면
        {
            node = p;//해제할 노드의 주소를 temp에 저장
            p = p->rlink;//해제할 노드의 다음 노드를 가리킴
            free(node);//메모리 해제
            
            temp = h;
            /*마지막 노드를 찾는 loop문*/
            while(temp->rlink == h->first)
            {
                temp = temp->rlink;
            }

            p->llink = temp;//젤 앞 노드를 마지막 노드에 연결
            temp->rlink = p;//마지막 노드를 젤 앞 노드에 연결
        }

        else
        {
            /*key 값이 있는 노드를 찾는 loop문*/
            while(p->key != key)
            {
                temp = p;//해제할 노드의 직전 노드
                p = p->rlink;
            }

            /*마지막 노드가 key 값과 같은 경우*/
            if(p->rlink == h)//찾은 노드의 다음 노드가 헤드라면 == 찾은 노드가 마지막 노드라면
            {
                free(p);//찾은 노드 할당 해제
                p = h;//헤드 노드를 p가 가리킴

                p->llink = temp;//젤 앞 노드를 삭제된 노드의 직전 노드에 연결
                temp->rlink = p;//삭제된 노드의 직전 노드를 제일 앞 노드에 연결
            }

            /*그 외의 경우*/
            else
            {
                node = p;//node가 삭제할 노드를 가리키게 함
                p = p->rlink;//삭제할 노드의 다음 노드를 가리키게 함
                free(node);//노드 할당 해제

                temp->rlink = p;//삭제된 노드의 직전 노드를 삭제된 노드의 다음 노드에 연결
                p->llink = temp;//삭제된 노드의 다음 노드를 삭제된 노드의 직전 노드에 연결
            }
        }
    }

    else
    {
        printf("There is no List!\n");
    }

    return 1;
}