#include<stdio.h>
#include<stdlib.h>

void main()
{
        int **x;

        printf("[----- [김동규]  [2019038077] -----]\n");
        printf("sizeof(x) = %lu\n", sizeof(x)); //vscode는 32bit체제이므로 주소값이 4bytes로 출력
        printf("sizeof(*x) = %lu\n", sizeof(*x)); //vscode는 32bit체제이므로 주소값이 4bytes로 출력
        printf("sizeof(**x) = %lu\n", sizeof(**x)); //x가 int가 기준이므로 4Bytes 출력
}
