#include <stdio.h>

struct student1 { //����ü ����
        char lastName;
        int studentId;
        char grade;
};  
typedef struct { //typedef�� �̿��� ����ü ����
        char lastName;
        int studentId;
        char grade;
} student2;
int main()
{
    struct student1 st1 = {'A', 100, 'A'}; //st1 ���� �� �ʱ�ȭ

    printf("[----- [�赿��]  [2019038077] -----]\n");
    printf("st1.lastName = %c\n", st1.lastName); //����ü st1�� lastname ���� �� ���
    printf("st1.studentId = %d\n", st1.studentId); //����ü st1�� studentId ���� �� ���
    printf("st1.grade = %c\n", st1.grade); //����ü st1�� grade ���� �� ���

    student2 st2 = {'B', 200, 'B'}; //st2 ���� �� �ʱ�ȭ
 
    printf("\nst2.lastName = %c\n", st2.lastName); //����ü st2�� lastname ���� �� ���
    printf("st2.studentId = %d\n", st2.studentId); //����ü st2�� studentId ���� �� ���
    printf("st2.grade = %c\n", st2.grade); //����ü st2�� grade ���� �� ���

    student2 st3; //st3 ����

    st3 = st2; //st3 �ʱ�ȭ

    printf("\nst3.lastName = %c\n", st3.lastName); //����ü st3�� lastname ���� �� ���
    printf("st3.studentId = %d\n", st3.studentId); //����ü st3�� studentId ���� �� ���
    printf("st3.grade = %c\n", st3.grade); //����ü st3�� grade ���� �� ���

    /* equality test*/
    /* 
    if(st3 == st2)
        printf("equal\n");
    else
        printf("not equal\n");
    */
return 0;

}
