#include <stdio.h>
int main()
{
int i;
int *ptr;
int **dptr;

i = 1234;

printf("[----- [김동규]    [2019038077] -----]\n");
printf("[checking values before ptr = &i] \n");
printf("value of i == %d\n", i); //변수 i에 저장된 값 출력
printf("address of i == %p\n", &i); //변수 i의 주소 출력
printf("value of ptr == %p\n", ptr); //포인터 ptr에 있는 주소(쓰레기값) 출력
printf("address of ptr == %p\n", &ptr); //포인터 ptr의 주소 출력

ptr = &i; /* ptr is now holding the address of i */

printf("\n[checking values after ptr = &i] \n");
printf("value of i == %d\n", i); //변수 i에 저장된 값 출력
printf("address of i == %p\n", &i); //변수 i의 주소 출력
printf("value of ptr == %p\n", ptr); //포인터 ptr에 저장된 값(주소) 출력
printf("address of ptr == %p\n", &ptr); //포인터 ptr의 주소 출력
printf("value of *ptr == %d\n", *ptr); //포인터 ptr이 가리키는 변수 i의 값 출력

dptr = &ptr; /* dptr is now holding the address of ptr */

printf("\n[checking values after dptr = &ptr] \n");
printf("value of i == %d\n", i); //변수 i에 저장된 값 출력
printf("address of i == %p\n", &i); //변수 i의 주소 출력
printf("value of ptr == %p\n", ptr); //포인터 ptr에 저장된 값(주소) 출력
printf("address of ptr == %p\n", &ptr); //포인터 ptr의 주소 출력
printf("value of *ptr == %d\n", *ptr); //포인터 ptr이 가리키는 변수 i의 값 출력
printf("value of dptr == %p\n", dptr); //이중포인터 dptr에 있는 ptr의 주소 출력
printf("address of dptr == %p\n", &dptr); //이중포인터 dptr의 주소 출력
printf("value of *dptr == %p\n", *dptr); //이중포인터 dptr에 간접참조하여 ptr 안의 i 주소 출력
printf("value of **dptr == %d\n", **dptr); //이중포인터 dptr에 간접 참조를 두 번하여 i의 값 출력

*ptr = 7777; /* changing the value of *ptr */

printf("\n[after *ptr = 7777] \n"); 
printf("value of i == %d\n", i); //변수 i에 저장된 값 출력(7777로 바뀌어서 출력됨)
printf("value of *ptr == %d\n", *ptr); //포인터 ptr에 간접 참조하여 i의 값 출력
printf("value of **dptr == %d\n", **dptr); //이중포인터 dptr에 두 번 간접참조하여 i의 값 출력

**dptr = 8888; /* changing the value of **dptr */

printf("\n[after **dptr = 8888] \n");
printf("value of i == %d\n", i); //변수 i에 저장된 값 출력(8888로 바뀌어서 출력됨)
printf("value of *ptr == %d\n", *ptr); //포인터 ptr에 간접참조하여 i의 값 출력
printf("value of **dptr == %d\n", **dptr); //이중포인터 dptr에 두 번 간접참조하여 i의 값 출력

return 0;
}