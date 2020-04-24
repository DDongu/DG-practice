#include <stdio.h>

#define MAX_SIZE 100

float sum(float [], int); 
float input[MAX_SIZE],answer;
int i;

void main(void)
{
    for(i=0; i< MAX_SIZE; i++)
       input[i] = i; 
 
    printf("[----- [김동규]  [2019038077] -----]\n");
       printf("address of input = %p\n", input);  //input의 시작 주소 출력
       
      answer = sum(input, MAX_SIZE); //반환된 인덱스 안의 값 저장
      printf("The sum is: %f\n", answer); //저장된 값 출력
}

float sum(float list[], int n) 
{
    printf("value of list = %p\n", list); //list의 인자가 input이므로 input의 시작 주소 출력
    printf("address of list = %p\n\n", &list); //list 자체의 주소(!= input의 시작 주소) 출력
    

   int i;
   float tempsum = 0;
   for(i = 0; i <n; i++)
             tempsum += list[i]; //list의 각 인덱스, 즉 input의 인덱스에 있는 모든 값을 더함
        return tempsum; //list의 모든 인덱스 안의 값들의 합 반환
}