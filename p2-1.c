#include <stdio.h>

#define MAX_SIZE 100

float sum(float [], int); 
float input[MAX_SIZE],answer;
int i;

void main(void)
{
    for(i=0; i< MAX_SIZE; i++)
       input[i] = i; 
 
    printf("[----- [�赿��]  [2019038077] -----]\n");
       printf("address of input = %p\n", input);  //input�� ���� �ּ� ���
       
      answer = sum(input, MAX_SIZE); //��ȯ�� �ε��� ���� �� ����
      printf("The sum is: %f\n", answer); //����� �� ���
}

float sum(float list[], int n) 
{
    printf("value of list = %p\n", list); //list�� ���ڰ� input�̹Ƿ� input�� ���� �ּ� ���
    printf("address of list = %p\n\n", &list); //list ��ü�� �ּ�(!= input�� ���� �ּ�) ���
    

   int i;
   float tempsum = 0;
   for(i = 0; i <n; i++)
             tempsum += list[i]; //list�� �� �ε���, �� input�� �ε����� �ִ� ��� ���� ����
        return tempsum; //list�� ��� �ε��� ���� ������ �� ��ȯ
}