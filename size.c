#include<stdio.h>
#include<stdlib.h>

void main()
{
        int **x;

        printf("[----- [�赿��]  [2019038077] -----]\n");
        printf("sizeof(x) = %lu\n", sizeof(x)); //vscode�� 32bitü���̹Ƿ� �ּҰ��� 4bytes�� ���
        printf("sizeof(*x) = %lu\n", sizeof(*x)); //vscode�� 32bitü���̹Ƿ� �ּҰ��� 4bytes�� ���
        printf("sizeof(**x) = %lu\n", sizeof(**x)); //x�� int�� �����̹Ƿ� 4Bytes ���
}
