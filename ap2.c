#include <stdio.h>
#include <stdlib.h>

void main(){

    int list[5]; 
    int *plist[5]; 

    list[0] = 10; 
    list[1] = 11;

    plist[0] = (int*)malloc(sizeof(int)); 

    printf("[----- [�赿��]  [2019038077] -----]\n");
    printf("list[0] \t= %d\n", list[0]); //list[0] �ȿ� ����� �� ���
    printf("address of list \t= %p\n", list); //list�� ���� �ּ� ���(�迭�� �̸� = �迭�� ���� �ּ��̱� ����)
    printf("address of list[0]  \t= %p\n",&list[0]); //list[0]�� �ּ� ���
    printf("address of list + 0 \t= %p\n",list+0); //list�� ���� �ּ� ���(0�� �������Ƿ� list�� ���� �ּҸ� ����Ŵ)
    printf("address of list + 1 \t= %p\n",list+1); //list�� ���ۺ��� �� ĭ �� �ε��� �ּ� ���
    printf("address of list + 2 \t= %p\n",list+2); //list�� ���ۺ��� �� ĭ �� �ε��� �ּ� ���
    printf("address of list + 3 \t= %p\n",list+3); //list�� ���ۺ��� �� ĭ �� �ε��� �ּ� ���
    printf("address of list + 4 \t= %p\n",list+4); //list�� ���ۺ��� �� ĭ �� �ε��� �ּ� ���
    printf("address of list[4] \t= %p\n",&list[4]); //list[�� 4���� �ε��� �ּ� ���

    free(plist[0]); //�����Ҵ� ����
    

}
