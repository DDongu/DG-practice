#include <stdio.h>

struct student { //����ü ����
    char lastName[13];   /* 13 bytes */    
    int studentId;       /* 4 bytes  */
    short grade;         /* 2 bytes  */

};
int main()
{
    struct student pst;

    printf("[----- [�赿��]  [2019038077] -----]\n");
    printf("size of student = %ld\n", sizeof(struct student)); // ����ü�� ũ�� ��� -> 13+3(�е�) + 4 + 2+2(�е�) = 24
    printf("size of int = %ld\n", sizeof(int)); //int���� ũ�� ���
    printf("size of short = %ld\n", sizeof(short)); //short���� ũ�� ���

    return 0;
}