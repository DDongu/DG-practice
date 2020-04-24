#include <stdio.h>
#include <stdlib.h>

void main()
{
    int list[5];      
    int *plist[5] ={NULL,}; 

    plist[0] = (int*)malloc(sizeof(int)); //동적할당으로 4Bytes만큼 메모리를 할당해 할당된 주소를 plist[0]에 저장 


    list[0] = 1; 
    list[1] = 100; 

    *plist[0] = 200; 

    printf("[----- [김동규]  [2019038077] -----]\n");
    printf("value of list[0]          = %d\n", list[0]); //배열 list 0번째 값 출력
    printf("address of list[0]        = %p\n", &list[0]); //배열 list 0번째 인덱스 주소 출력
    printf("value of list             = %p\n", list); //배열 list의 주소(배열의 이름 = 배열의 시작 주소) 출력
    printf("address of list (&list)   = %p\n", &list); //배열 list의 주소(배열의 시작 주소) 출력

    printf("---------------------------------------\n\n");
    printf("value of list[1]          = %d\n", list[1]); //배열 list의 1번째 인덱스 값 출력
    printf("address of list[1]        = %p\n", &list[1]); //배열 list의 1번째 인덱스 주소 출력

    printf("value of *(list+1)        = %d\n",*(list + 1)); //list(배열의 이름) + 1 = 배열의 시작 주소 + 다음 인덱스 -> list[1]의 값 출력
    printf("address of list+1         = %p\n", list+1 ); //list(배열의 이름) + 1 = 배열의 시작 주소 + 다음 인덱스 -> list[1] 주소 출력

    printf("---------------------------------------\n\n");

    printf("value of *plist[0]        = %d\n", *plist[0]); //plist가 가리키는 메모리 안의 값 출력
    printf("&plist[0]                 = %p\n", &plist[0]); //plist[0]의 주소 출력
    printf("&plist                    = %p\n", &plist); //plist의 주소 출력
    printf("plist                     = %p\n", plist); //plist의 시작 주소 출력
    printf("plist[0]                  = %p\n", plist[0]); //9행에서 동적할당된 메모리의 주소 출력
    printf("plist[1]                  = %p\n", plist[1]); //NULL 값 출력(초기화 한 뒤 아무 것도 안했기 때문)
    printf("plist[2]                  = %p\n", plist[2]); //NULL 값 출력(''')
    printf("plist[3]                  = %p\n", plist[3]); //NULL 값 출력(''')
    printf("plist[4]                  = %p\n", plist[4]); //NULL 값 출력(''')
    

    free(plist[0]); //동적할당된 메모리 해제

    
} 
