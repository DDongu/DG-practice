#include <stdio.h>

struct student { //구조체 선언
    char lastName[13];   /* 13 bytes */    
    int studentId;       /* 4 bytes  */
    short grade;         /* 2 bytes  */

};
int main()
{
    struct student pst;

    printf("[----- [김동규]  [2019038077] -----]\n");
    printf("size of student = %ld\n", sizeof(struct student)); // 구조체의 크기 출력 -> 13+3(패딩) + 4 + 2+2(패딩) = 24
    printf("size of int = %ld\n", sizeof(int)); //int형의 크기 출력
    printf("size of short = %ld\n", sizeof(short)); //short형의 크기 출력

    return 0;
}