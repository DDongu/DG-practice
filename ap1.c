#include <stdio.h>
#include <stdlib.h>

void main()
{
    int list[5];      
    int *plist[5] ={NULL,}; 

    plist[0] = (int*)malloc(sizeof(int)); //�����Ҵ����� 4Bytes��ŭ �޸𸮸� �Ҵ��� �Ҵ�� �ּҸ� plist[0]�� ���� 


    list[0] = 1; 
    list[1] = 100; 

    *plist[0] = 200; 

    printf("[----- [�赿��]  [2019038077] -----]\n");
    printf("value of list[0]          = %d\n", list[0]); //�迭 list 0��° �� ���
    printf("address of list[0]        = %p\n", &list[0]); //�迭 list 0��° �ε��� �ּ� ���
    printf("value of list             = %p\n", list); //�迭 list�� �ּ�(�迭�� �̸� = �迭�� ���� �ּ�) ���
    printf("address of list (&list)   = %p\n", &list); //�迭 list�� �ּ�(�迭�� ���� �ּ�) ���

    printf("---------------------------------------\n\n");
    printf("value of list[1]          = %d\n", list[1]); //�迭 list�� 1��° �ε��� �� ���
    printf("address of list[1]        = %p\n", &list[1]); //�迭 list�� 1��° �ε��� �ּ� ���

    printf("value of *(list+1)        = %d\n",*(list + 1)); //list(�迭�� �̸�) + 1 = �迭�� ���� �ּ� + ���� �ε��� -> list[1]�� �� ���
    printf("address of list+1         = %p\n", list+1 ); //list(�迭�� �̸�) + 1 = �迭�� ���� �ּ� + ���� �ε��� -> list[1] �ּ� ���

    printf("---------------------------------------\n\n");

    printf("value of *plist[0]        = %d\n", *plist[0]); //plist�� ����Ű�� �޸� ���� �� ���
    printf("&plist[0]                 = %p\n", &plist[0]); //plist[0]�� �ּ� ���
    printf("&plist                    = %p\n", &plist); //plist�� �ּ� ���
    printf("plist                     = %p\n", plist); //plist�� ���� �ּ� ���
    printf("plist[0]                  = %p\n", plist[0]); //9�࿡�� �����Ҵ�� �޸��� �ּ� ���
    printf("plist[1]                  = %p\n", plist[1]); //NULL �� ���(�ʱ�ȭ �� �� �ƹ� �͵� ���߱� ����)
    printf("plist[2]                  = %p\n", plist[2]); //NULL �� ���(''')
    printf("plist[3]                  = %p\n", plist[3]); //NULL �� ���(''')
    printf("plist[4]                  = %p\n", plist[4]); //NULL �� ���(''')
    

    free(plist[0]); //�����Ҵ�� �޸� ����

    
} 
