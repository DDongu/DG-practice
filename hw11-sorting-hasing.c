/*
 * hw5-sorting.c
 *
 *  Created on: May 22, 2019
 *
 *  Homework 5: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE            13    /* prime number */
#define MAX_HASH_TABLE_SIZE     MAX_ARRAY_SIZE

/* �ʿ信 ���� �Լ� �߰� ���� */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function���� ���� */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a���� �� hash table�� �����. */
int hashing(int *a, int **ht);

/* hash table���� key�� ã�� hash table�� index return */
int search(int *ht, int key);


int main()
{
    char command;
    int *array = NULL;
    int *hashtable = NULL;
    int key = -1;
    int index = -1;

    srand(time(NULL));

    do{
        printf("----------------------------------------------------------------\n");
        printf("                        Sorting & Hashing                       \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize       = z           Quit             = q\n");
        printf(" Selection Sort   = s           Insertion Sort   = i\n");
        printf(" Bubble Sort      = b           Shell Sort       = l\n");
        printf(" Quick Sort       = k           Print Array      = p\n");
        printf(" Hashing          = h           Search(for Hash) = e\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch(command) {
        case 'z': case 'Z':
            initialize(&array);
            break;
        case 'q': case 'Q':
            freeArray(array);
            break;
        case 's': case 'S':
            selectionSort(array);
            break;
        case 'i': case 'I':
            insertionSort(array);
            break;
        case 'b': case 'B':
            bubbleSort(array);
            break;
        case 'l': case 'L':
            shellSort(array);
            break;
        case 'k': case 'K':
            printf("Quick Sort: \n");
            printf("----------------------------------------------------------------\n");
            printArray(array);
            quickSort(array, MAX_ARRAY_SIZE);
            printf("----------------------------------------------------------------\n");
            printArray(array);

            break;

        case 'h': case 'H':
            printf("Hashing: \n");
            printf("----------------------------------------------------------------\n");
            printArray(array);
            hashing(array, &hashtable);
            printArray(hashtable);
            break;

        case 'e': case 'E':
            printf("Your Key = ");
            scanf("%d", &key);
            printArray(hashtable);
            index = search(hashtable, key);
            printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
            break;

        case 'p': case 'P':
            printArray(array);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q');

    return 1;
}

int initialize(int** a)
{
    int *temp = NULL;

    /* array�� NULL�� ��� �޸� �Ҵ� */
    if(*a == NULL) {
        temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
        *a = temp;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
    } else
        temp = *a;

    /* �������� �迭�� ������ ���� */
    for(int i = 0; i < MAX_ARRAY_SIZE; i++)
        temp[i] = rand() % MAX_ARRAY_SIZE;

    return 0;
}

int freeArray(int *a)
{
    if(a != NULL)
        free(a);
    return 0;
}

void printArray(int *a)
{
    if (a == NULL) {
        printf("nothing to print.\n");
        return;
    }
    for(int i = 0; i < MAX_ARRAY_SIZE; i++)
        printf("a[%02d] ", i);
    printf("\n");
    for(int i = 0; i < MAX_ARRAY_SIZE; i++)
        printf("%5d ", a[i]);
    printf("\n");
}


int selectionSort(int *a)
{
    int min;
    int minindex;
    int i, j;

    printf("Selection Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a);

    for (i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        minindex = i; //���� ���� ������ ��ġ
        min = a[i]; //���� ���� ����
        for(j = i+1; j < MAX_ARRAY_SIZE; j++) //������ �����ϴ� ��ġ�� �ϳ��� Ŀ��(i+1)
        {
            if (min > a[j]) //���� ���� ���Һ��� j�� ���Ұ� �� �۴ٸ�
            {
                min = a[j]; //���� ���� ���Ҹ� j�� ���ҷ� ����
                minindex = j; //j�� ��ġ�� ���� ���� ������ ��ġ�� ����
            } //������ ���鼭 �ּ� �� ã��
        }
        a[minindex] = a[i]; //ã�� �ּҰ��� ���ĵ��� ���� ����Ʈ�� �� �տ� ����
        a[i] = min; //�ּҰ��� ����� �ִ� ��ġ�� ���ĵ��� �ʾҴ� ����Ʈ �� �տ� �ִ� ���Ҹ� ����
    }

    printf("----------------------------------------------------------------\n");
    printArray(a);
    return 0;
}

int insertionSort(int *a)
{
    int i, j, t;

    printf("Insertion Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a);

    for(i = 1; i < MAX_ARRAY_SIZE; i++)
    {
        t = a[i]; //������ ����
        j = i; //������ ������ ��ġ(�ʱ�)
        while (a[j-1] > t && j > 0) //������ ���ҿ� �� �տ� ��ġ�� ���ĵ� ���ҵ���� ũ�� ��
        {
            a[j] = a[j-1]; //j-1��°�� t(������ ����)���� ũ�Ƿ� �� ĭ �ڷ� �б�
            j--; //j�� ��ġ�� �� ĭ ������ �̵�
        }
        a[j] = t; //t�� �� ��ġ�� t ����
    }

    printf("----------------------------------------------------------------\n");
    printArray(a);

    return 0;
}

int bubbleSort(int *a)
{
    int i, j, t;

    printf("Bubble Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a);

    for(i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        for (j = 0; j < MAX_ARRAY_SIZE; j++)
        {
            if (a[j-1] > a[j])//j-1�� ���Ұ� j�� ���Һ��� ũ�ٸ�
            { //j�� j-1�� ���Ҹ� swap
                t = a[j-1];
                a[j-1] = a[j];
                a[j] = t;
            }
        }
    }

    printf("----------------------------------------------------------------\n");
    printArray(a);

    return 0;
}

int shellSort(int *a)
{
    int i, j, k, h, v;

    printf("Shell Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a);

    for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) //�ʱ� h�� ���� �Ϲ������� ��ü ������ ���� / 2
    {
        for (i = 0; i < h; i++)
        {
            for(j = i + h; j < MAX_ARRAY_SIZE; j += h) //h��ŭ ���� ��Ű�鼭 ��
            {
                v = a[j]; //������ ����
                k = j; //������ ������ ��ġ
                while (k > h-1 && a[k-h] > v) //������
                {
                    a[k] = a[k-h]; //k-h�� ������ h��ŭ �ڷ� �б�
                    k -= h; //k(���� ����)�� ��ġ�� h��ŭ ����
                }
                a[k] = v; //������ ��ġ�� ������ ���� ����
            }
        }
    }
    printf("----------------------------------------------------------------\n");
    printArray(a);

    return 0;
}

int quickSort(int *a, int n)
{
    int v, t;
    int i, j;

    if (n > 1)
    {
        v = a[n-1]; //���� ������ ��ġ�� �Ǻ�
        i = -1; //ó���� left��
        j = n - 1; //ó���� right��

        while(1)
        {
            while(a[++i] < v); //�Ǻ� ������ ū �� ã��
            while(a[--j] > v); //�Ǻ� ������ ���� �� ã��

            if (i >= j) break; //i�� j���� ũ�ų� ��������
            //i�� j�� ���� swap
            t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
        //i�� ���ҿ� �Ǻ� �� swap
        t = a[i];
        a[i] = a[n-1];
        a[n-1] = t;

        quickSort(a, i); //�Ǻ� ���� ���� ����Ʈ ������
        quickSort(a+i+1, n-i-1); //�Ǻ� ���� ������ ����Ʈ ������
    }


    return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE; //���� �Լ� �̿�
}

int hashing(int *a, int **ht)
{
    int *hashtable = NULL;

    /* hash table�� NULL�� ��� �޸� �Ҵ� */
    if(*ht == NULL) {
        hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
        *ht = hashtable;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
    } else {
        hashtable = *ht;    /* hash table�� NULL�� �ƴѰ��, table ��Ȱ��, reset to -1 */
    }

    for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
        hashtable[i] = -1;

    /*
    for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
        printf("hashtable[%d] = %d\n", i, hashtable[i]);
    */

    int key = -1;
    int hashcode = -1;
    int index = -1;
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        key = a[i];
        hashcode = hashCode(key); //key ���� �ؽ��ڵ�� ��ȯ
        /*
        printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
        */
        if (hashtable[hashcode] == -1) //��Ŷ�� ����ִٸ�
        {
            hashtable[hashcode] = key; //��Ŷ�� key�� ����
        } 
        else     {

            index = hashcode;

            while(hashtable[index] != -1) //��Ŷ�� ������� �ʴٸ�(����ִ� ��Ŷ�� ã�� ������)
            {
                index = (++index) % MAX_HASH_TABLE_SIZE; //���� ��Ŷ���� �̵�
                /*
                printf("index = %d\n", index);
                */
            }
            hashtable[index] = key; //�̵��� ��Ŷ�� key �� ����
        }
    }

    return 0;
}

int search(int *ht, int key)
{
    int index = hashCode(key); //key ���� �ؽ��ڵ�� ��ȯ

    if(ht[index] == key) //�ش� ��Ŷ�� ���� key ���� ���ٸ�
        return index; //�ش� ��Ŷ�� �ؽ��ڵ� ��ȯ

    while(ht[++index] != key) //key ���� ����ִ� ��Ŷ�� ��ġ�� ã�� ������
    {
        index = index % MAX_HASH_TABLE_SIZE; //��Ŷ�� ��ġ�� ���� �Լ� ������� ����
    }
    return index; //�ش� ��Ŷ�� ã���� �� ��Ŷ�� �ؽ��ڵ� ��ȯ
}