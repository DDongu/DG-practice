#include <stdio.h>
int main()
{
char charType;
int integerType;
float floatType;
double doubleType;

printf("[----- [�赿��]    [2019038077] -----]\n");
printf("Size of char: %ld byte\n",sizeof(charType)); //���� charType�� ũ�� ���
printf("Size of int: %ld bytes\n",sizeof(integerType)); //���� integerType�� ũ�� ���
printf("Size of float: %ld bytes\n",sizeof(floatType)); //���� floatType�� ũ�� ���
printf("Size of double: %ld bytes\n",sizeof(doubleType)); //���� doubleType�� ũ�� ���

printf("-----------------------------------------\n");

printf("Size of char: %ld byte\n",sizeof(char)); //�ڷ��� char�� ũŰ ���
printf("Size of int: %ld bytes\n",sizeof(int)); //�ڷ��� int�� ũ�� ���
printf("Size of float: %ld bytes\n",sizeof(float)); //�ڷ��� float�� ũŰ ���
printf("Size of double: %ld bytes\n",sizeof(double)); //�ڷ��� double�� ũ�� ���

printf("-----------------------------------------\n");

printf("Size of char*: %ld byte\n",sizeof(char*)); //�ڷ��� char �������� ũ�� ���
printf("Size of int*: %ld bytes\n",sizeof(int*)); //�ڷ��� int �������� ũ�� ���
printf("Size of float*: %ld bytes\n",sizeof(float*)); //�ڷ��� float �������� ũ�� ���
printf("Size of double*: %ld bytes\n",sizeof(double*)); //�ڷ��� double �������� ũ�� ���

return 0;
}