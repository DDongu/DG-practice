#include <stdio.h>

struct student1 { //구조체 선언
        char lastName;
        int studentId;
        char grade;
};  
typedef struct { //typedef를 이용한 구조체 선언
        char lastName;
        int studentId;
        char grade;
} student2;
int main()
{
    struct student1 st1 = {'A', 100, 'A'}; //st1 생성 및 초기화

    printf("[----- [김동규]  [2019038077] -----]\n");
    printf("st1.lastName = %c\n", st1.lastName); //구조체 st1의 lastname 안의 값 출력
    printf("st1.studentId = %d\n", st1.studentId); //구조체 st1의 studentId 안의 값 출력
    printf("st1.grade = %c\n", st1.grade); //구조체 st1의 grade 안의 값 출력

    student2 st2 = {'B', 200, 'B'}; //st2 생성 및 초기화
 
    printf("\nst2.lastName = %c\n", st2.lastName); //구조체 st2의 lastname 안의 값 출력
    printf("st2.studentId = %d\n", st2.studentId); //구조체 st2의 studentId 안의 값 출력
    printf("st2.grade = %c\n", st2.grade); //구조체 st2의 grade 안의 값 출력

    student2 st3; //st3 생성

    st3 = st2; //st3 초기화

    printf("\nst3.lastName = %c\n", st3.lastName); //구조체 st3의 lastname 안의 값 출력
    printf("st3.studentId = %d\n", st3.studentId); //구조체 st3의 studentId 안의 값 출력
    printf("st3.grade = %c\n", st3.grade); //구조체 st3의 grade 안의 값 출력

    /* equality test*/
    /* 
    if(st3 == st2)
        printf("equal\n");
    else
        printf("not equal\n");
    */
return 0;

}
