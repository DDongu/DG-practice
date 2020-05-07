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
/* �ʿ��� ������� �߰� if necessary */


typedef struct Node {
    int key;
    struct Node* llink;
    struct Node* rlink;
} listNode;



typedef struct Head {
    struct Node* first;
}headNode;

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ����
         singly-linked-list�� initialize�� �������� ���� �Ұ� */
int initialize(headNode** h);

/* note: freeList�� �̱������͸� �Ű������� ����
        - initialize�� �� �ٸ��� ���� �Ұ�
         - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
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
        printf("\n------------------- [�赿��]   [2019038077] ------------------\n");
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

    if(h != NULL) //����Ʈ�� �����Ѵٸ�
        freeList(h); //����Ʈ�� ��� ������Ŵ

    *h = (headNode**)malloc(sizeof(headNode ));//��� ��� ũ�⸸ŭ �޸� �Ҵ�
    (*h)->first = NULL;
    return 1;
}

int freeList(headNode* h){
    
    /* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
	 */
	listNode* p = h->first; //��带 �ϳ��� ����ų ������
	listNode* prev = NULL; //������ �޸� �ּҸ� ����ų ������

	while (p != NULL) { //��尡 ������� �ʴٸ� == ����Ʈ�� ���� �Ѵٸ�
		prev = p;
		p = p->rlink;//p�� ���� ���� �ű�
		free(prev);//p�� �������� �ű�� �� ��带 ����
	}
	free(h);//��� ��� ����

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
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {

    listNode *p = h;
    listNode *node = (listNode*)malloc(sizeof(listNode)); //���� ���� ���� ��ų ��� ����
    node->key = key; //��忡 ���� �� ����

    if(h)//����Ʈ�� �ִ��� ������ Ȯ��
    {
        if(h->first == NULL) //����Ʈ�� ��尡 �ϳ��� ���ٸ�
        {
            h->first = node;//���� ���ο� ��带 ����
            node->llink = h->first;//���ο� ����� llink�� ���ο� ��� �ڽſ��� ����
            node->rlink = node;//���ο� ����� rlink�� ���ο� ��� �ڽſ��� ����

            return 0;
        }

        p->llink = node;//���ο� ���� �� ���� ��带 ����
        while (p->rlink == h->first)
        {
            p = p->rlink;//����Ʈ�� ������ ��带 ã�� ����
        }
        
        p->rlink = node;//������ ��带 ���ο� ��忡 ����
        node->llink = p;//���ο� ��带 ������ ��忡 ����
        node->rlink = h->first;//���ο� ��带 ���� �� ���� ����
    }

    else
    {
        printf("There is no List!\n");
    }
    
    return 0;
}



/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {

    listNode *p = h;
    listNode *pre = NULL;

    if(h)
    {
        while(p->rlink != h)//������ ��带 ã�� ���ǹ�
        {
            pre = p;//�����ϴ� ����� ���� ��� �ּ� ����
            p = p->rlink;//������ ��带 ã�� ���� p�� ���� ���� �ű�� ����
        }
        free(p);//������ ��� �޸� ����
        
        pre->rlink = h->first;//������ ����� ���� ��带 ���� �� ���� ����
        p = h;//���� �� ��带 ������ ���� �����Ű�� ���� p�� ���� �� ��带 ����Ű�� ��
        p->llink = pre;//���� �� ��带 ������ ��忡 ����
    }

    else
    {
        printf("There is no List!\n");
    }
    
    return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {
    
    listNode *p = h;
    listNode *node = (listNode*)malloc(sizeof(listNode));//���� ���� ������ ��� ����
    node->key = key;//���� ������ ��忡 ����

    if(h)
    {
        if(h->first == NULL) //����Ʈ�� ��尡 �ϳ��� ���ٸ�
        {
            h->first = node;//���� ���ο� ��带 ����
            node->llink = h->first;//���ο� ����� llink�� ���ο� ��� �ڽſ��� ����
            node->rlink = node;//���ο� ����� rlink�� ���ο� ��� �ڽſ��� ����

            return 0;
        }   

        node->rlink = h->first;//���ο� ��带 ���� �տ� ����
        p->llink = node;//���� �� ��带 ���ο� ��忡 ����

        /*������ ��带 ã�� loop��*/
        while(p->rlink == h->first)
        {
            p = p->rlink;
        }

        node->llink = p;//���ο� ��带 ������ ��忡 ����
        p->rlink = node;//������ ��带 ���ο� ��忡 ����
    }

    else
    {
        printf("There is no List!\n");
    }
    
    return 0;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {

    listNode *p = h;//������ ����� ���� ��带 ����ų ������
    listNode *pre = NULL;//������ ��带 ����ų ������

    if(h)
    {
        pre = p;//���� �� ��带 ����Ű�� ��
        p = p->rlink;//p�� ���� ��带 ����Ű�� ��
        free(pre);//���� �� ��� �Ҵ� ����

        pre = p;//pre�� ���� �� ��带 ����Ű�� ��
        /*������ ��带 ã�� loop��*/
        while(p->rlink == h->first)
        {
            p = p->rlink;
        }

        pre->llink = p;//������ �� ���� �� ��带, ������ ��忡 ����
        p->rlink = pre;//������ ��带 ������ �� ���� �� ���� ����

    }

    else
    {
        printf("There is no List!\n");
    }
    

    return 0;
}



/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {

    listNode *p = h;
    listNode *tmp;

    if(h)
    {
        do
        {
            /*p�� ����Ű�� �ִ� ����� rlink, llink�� swap*/
            tmp = p->rlink;
            p->rlink = p->llink;
            p->llink = tmp;

            p = p->llink;//p�� ���� ���� �ű�
        }while(p != h);//p�� ��� ��带 ����Ű�� ����
        h->first = p->rlink;//����Ʈ ���� ��ġ �� ������ ��带 ���� ����
    }

    else
    {
        printf("There is no List!\n");
    }
    
    
    return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {

    listNode *node = (listNode*)malloc(sizeof(listNode));
    listNode *p = h, *pre = NULL;
    node->key = key;
    
    if(h)
    {
        if(h->first == NULL) //����Ʈ�� ��尡 �ϳ��� ���ٸ�
        {
            h->first = node;//���� ���ο� ��带 ����
            node->llink = h->first;//���ο� ����� llink�� ���ο� ��� �ڽſ��� ����
            node->rlink = node;//���ο� ����� rlink�� ���ο� ��� �ڽſ��� ����

            return 0;
        }   

        if(p->rlink > key)//�� �� ��尡 key ������ ũ�� == key ���� ���� ������
        {
            pre = p;//pre�� �� �� ��带 ����Ű�� ��
            /*������ ��带 ã�� loop��*/
            while(p->rlink == h->first)
            {
                p = p->rlink;
            }
            node->rlink = pre;//���ο� ��带 �� �� ��忡 ����
            pre->llink = node;//�� �� ��带 ���ο� ��忡 ����
            node->llink = p;//���ο� ��带 ������ ��忡 ����
            p->rlink = node;//������ ��带 ���ο� ��忡 ����
        }

        else
        {        
            /*key ������ ū ���� ã�� loop��*/
            while(p->key <= key)
            {
                pre = p;
                p = p->rlink;
            }
            pre->rlink = node;//key���� ū ���� ����ִ� ����� ���� ��带 ���ο� ��忡 ����
            node->llink = pre;//���ο� ��带 key���� ū ���� ����ִ� ����� ���� ��忡 ����
            p->llink = node;//key���� ū ���� ����ִ� ��带 ���ο� ��忡 ����
            node->rlink = p;//���ο� ��带 key���� ū ���� ����ִ� ��忡 ����
        }
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
int deleteNode(headNode* h, int key) {

    listNode *p = h;
    listNode *temp;
    listNode *node = h;

    if(h)
    {
        /*�� �� ��尡 key���� ���� ���*/
        if(p->key == key)//���� �� ����� ���� key�� ���ٸ�
        {
            node = p;//������ ����� �ּҸ� temp�� ����
            p = p->rlink;//������ ����� ���� ��带 ����Ŵ
            free(node);//�޸� ����
            
            temp = h;
            /*������ ��带 ã�� loop��*/
            while(temp->rlink == h->first)
            {
                temp = temp->rlink;
            }

            p->llink = temp;//�� �� ��带 ������ ��忡 ����
            temp->rlink = p;//������ ��带 �� �� ��忡 ����
        }

        else
        {
            /*key ���� �ִ� ��带 ã�� loop��*/
            while(p->key != key)
            {
                temp = p;//������ ����� ���� ���
                p = p->rlink;
            }

            /*������ ��尡 key ���� ���� ���*/
            if(p->rlink == h)//ã�� ����� ���� ��尡 ����� == ã�� ��尡 ������ �����
            {
                free(p);//ã�� ��� �Ҵ� ����
                p = h;//��� ��带 p�� ����Ŵ

                p->llink = temp;//�� �� ��带 ������ ����� ���� ��忡 ����
                temp->rlink = p;//������ ����� ���� ��带 ���� �� ��忡 ����
            }

            /*�� ���� ���*/
            else
            {
                node = p;//node�� ������ ��带 ����Ű�� ��
                p = p->rlink;//������ ����� ���� ��带 ����Ű�� ��
                free(node);//��� �Ҵ� ����

                temp->rlink = p;//������ ����� ���� ��带 ������ ����� ���� ��忡 ����
                p->llink = temp;//������ ����� ���� ��带 ������ ����� ���� ��忡 ����
            }
        }
    }

    else
    {
        printf("There is no List!\n");
    }

    return 1;
}