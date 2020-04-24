#include <stdio.h>

void print1 (int *ptr, int rows); 

int main()
{
    int one[] = {0, 1, 2, 3, 4,};  
    printf("[----- [김동규]  [2019038077] -----]\n");
    printf("one    =%p\n",one); //one의 시작 주소 출력(배열의 이름 = 배열의 시작 주소)
    printf("&one   =%p\n",&one); //one의 제일 처음 주소 출력
    printf("&one[] =%p\n",&one[0]); //one[0]의 주소 출력
    printf("\n");

    print1(&one[0], 5); 

    return 0;
}

void print1 (int *ptr, int rows) //ptr = 배열을 받기 위한 포인터, rows = 배열 인덱스의 총 개수
{    
    int i;
    printf("Address \t Contents\n"); 
    for (i = 0; i < rows; i++) //rows번, 즉 5번 반복
        printf("%p \t  %5d\n",ptr + i, *(ptr + i)); //ptr이 가리키고 있는 배열,즉 one의 각 인덱스 주소와 안의 값을 차례대로 출력 
    printf("\n");
}
    

