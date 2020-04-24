#include <stdio.h>
int main()
{
char charType;
int integerType;
float floatType;
double doubleType;

printf("[----- [김동규]    [2019038077] -----]\n");
printf("Size of char: %ld byte\n",sizeof(charType)); //변수 charType의 크기 출력
printf("Size of int: %ld bytes\n",sizeof(integerType)); //변수 integerType의 크기 출력
printf("Size of float: %ld bytes\n",sizeof(floatType)); //변수 floatType의 크기 출력
printf("Size of double: %ld bytes\n",sizeof(doubleType)); //변수 doubleType의 크기 출력

printf("-----------------------------------------\n");

printf("Size of char: %ld byte\n",sizeof(char)); //자료형 char의 크키 출력
printf("Size of int: %ld bytes\n",sizeof(int)); //자료형 int의 크기 출력
printf("Size of float: %ld bytes\n",sizeof(float)); //자료형 float의 크키 출력
printf("Size of double: %ld bytes\n",sizeof(double)); //자료형 double의 크기 출력

printf("-----------------------------------------\n");

printf("Size of char*: %ld byte\n",sizeof(char*)); //자료형 char 포인터의 크기 출력
printf("Size of int*: %ld bytes\n",sizeof(int*)); //자료형 int 포인터의 크기 출력
printf("Size of float*: %ld bytes\n",sizeof(float*)); //자료형 float 포인터의 크기 출력
printf("Size of double*: %ld bytes\n",sizeof(double*)); //자료형 double 포인터의 크기 출력

return 0;
}