#include <stdio.h>

void print1 (int *ptr, int rows); 

int main()
{
    int one[] = {0, 1, 2, 3, 4,};  
    printf("[----- [�赿��]  [2019038077] -----]\n");
    printf("one    =%p\n",one); //one�� ���� �ּ� ���(�迭�� �̸� = �迭�� ���� �ּ�)
    printf("&one   =%p\n",&one); //one�� ���� ó�� �ּ� ���
    printf("&one[] =%p\n",&one[0]); //one[0]�� �ּ� ���
    printf("\n");

    print1(&one[0], 5); 

    return 0;
}

void print1 (int *ptr, int rows) //ptr = �迭�� �ޱ� ���� ������, rows = �迭 �ε����� �� ����
{    
    int i;
    printf("Address \t Contents\n"); 
    for (i = 0; i < rows; i++) //rows��, �� 5�� �ݺ�
        printf("%p \t  %5d\n",ptr + i, *(ptr + i)); //ptr�� ����Ű�� �ִ� �迭,�� one�� �� �ε��� �ּҿ� ���� ���� ���ʴ�� ��� 
    printf("\n");
}
    

