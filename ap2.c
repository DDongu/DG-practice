#include <stdio.h>
#include <stdlib.h>

void main(){

    int list[5]; 
    int *plist[5]; 

    list[0] = 10; 
    list[1] = 11;

    plist[0] = (int*)malloc(sizeof(int)); 

    printf("[----- [김동규]  [2019038077] -----]\n");
    printf("list[0] \t= %d\n", list[0]); //list[0] 안에 저장된 값 출력
    printf("address of list \t= %p\n", list); //list의 시작 주소 출력(배열의 이름 = 배열의 시작 주소이기 때문)
    printf("address of list[0]  \t= %p\n",&list[0]); //list[0]의 주소 출력
    printf("address of list + 0 \t= %p\n",list+0); //list의 시작 주소 출력(0을 더했으므로 list의 시작 주소를 가리킴)
    printf("address of list + 1 \t= %p\n",list+1); //list의 시작보다 한 칸 뒤 인덱스 주소 출력
    printf("address of list + 2 \t= %p\n",list+2); //list의 시작보다 두 칸 뒤 인덱스 주소 출력
    printf("address of list + 3 \t= %p\n",list+3); //list의 시작보다 세 칸 뒤 인덱스 주소 출력
    printf("address of list + 4 \t= %p\n",list+4); //list의 시작보다 네 칸 뒤 인덱스 주소 출력
    printf("address of list[4] \t= %p\n",&list[4]); //list[의 4번재 인덱스 주소 출력

    free(plist[0]); //동적할당 해제
    

}
