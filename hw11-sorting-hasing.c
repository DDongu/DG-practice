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

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
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

    /* array가 NULL인 경우 메모리 할당 */
    if(*a == NULL) {
        temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
        *a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
    } else
        temp = *a;

    /* 랜덤값을 배열의 값으로 저장 */
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
        minindex = i; //가장 작은 원소의 위치
        min = a[i]; //가장 작은 원소
        for(j = i+1; j < MAX_ARRAY_SIZE; j++) //정렬을 시작하는 위치가 하나씩 커짐(i+1)
        {
            if (min > a[j]) //가장 작은 원소보다 j의 원소가 더 작다면
            {
                min = a[j]; //가장 작은 원소를 j의 원소로 변경
                minindex = j; //j의 위치를 가장 작은 원소의 위치로 변경
            } //끝까지 돌면서 최소 값 찾기
        }
        a[minindex] = a[i]; //찾은 최소값을 정렬되지 않은 리스트의 맨 앞에 저장
        a[i] = min; //최소값이 저장돼 있던 위치에 정렬되지 않았던 리스트 맨 앞에 있던 원소를 저장
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
        t = a[i]; //정렬할 원소
        j = i; //정렬할 원소의 위치(초기)
        while (a[j-1] > t && j > 0) //정렬할 원소와 그 앞에 위치한 정렬된 원소들과의 크기 비교
        {
            a[j] = a[j-1]; //j-1번째가 t(정렬할 원소)보다 크므로 한 칸 뒤로 밀기
            j--; //j의 위치를 한 칸 앞으로 이동
        }
        a[j] = t; //t가 들어갈 위치에 t 삽입
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
            if (a[j-1] > a[j])//j-1의 원소가 j의 원소보다 크다면
            { //j와 j-1의 원소를 swap
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

    for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) //초기 h의 값은 일반적으로 전체 원소의 개수 / 2
    {
        for (i = 0; i < h; i++)
        {
            for(j = i + h; j < MAX_ARRAY_SIZE; j += h) //h만큼 증가 시키면서 비교
            {
                v = a[j]; //정렬할 원소
                k = j; //정렬할 원소의 위치
                while (k > h-1 && a[k-h] > v) //정렬할
                {
                    a[k] = a[k-h]; //k-h의 원소을 h만큼 뒤로 밀기
                    k -= h; //k(비교할 원소)의 위치를 h만큼 당기기
                }
                a[k] = v; //정렬할 위치에 정렬할 원소 저장
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
        v = a[n-1]; //가장 오른쪽 위치가 피봇
        i = -1; //처음은 left값
        j = n - 1; //처음은 right값

        while(1)
        {
            while(a[++i] < v); //피봇 값보다 큰 값 찾기
            while(a[--j] > v); //피봇 값보다 작은 값 찾기

            if (i >= j) break; //i가 j보다 크거나 같아지면
            //i와 j의 원소 swap
            t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
        //i의 원소와 피봇 값 swap
        t = a[i];
        a[i] = a[n-1];
        a[n-1] = t;

        quickSort(a, i); //피봇 기준 왼쪽 리스트 퀵정렬
        quickSort(a+i+1, n-i-1); //피봇 기준 오른쪽 리스트 퀵정렬
    }


    return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE; //제산 함수 이용
}

int hashing(int *a, int **ht)
{
    int *hashtable = NULL;

    /* hash table이 NULL인 경우 메모리 할당 */
    if(*ht == NULL) {
        hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
        *ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
    } else {
        hashtable = *ht;    /* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
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
        hashcode = hashCode(key); //key 값을 해시코드로 변환
        /*
        printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
        */
        if (hashtable[hashcode] == -1) //버킷이 비어있다면
        {
            hashtable[hashcode] = key; //버킷에 key값 저장
        } 
        else     {

            index = hashcode;

            while(hashtable[index] != -1) //버킷이 비어있지 않다면(비어있는 버킷을 찾을 때까지)
            {
                index = (++index) % MAX_HASH_TABLE_SIZE; //다음 버킷으로 이동
                /*
                printf("index = %d\n", index);
                */
            }
            hashtable[index] = key; //이동한 버킷에 key 값 저장
        }
    }

    return 0;
}

int search(int *ht, int key)
{
    int index = hashCode(key); //key 값을 해시코드로 변환

    if(ht[index] == key) //해당 버킷의 값이 key 값과 같다면
        return index; //해당 버킷의 해시코드 반환

    while(ht[++index] != key) //key 값이 들어있는 버킷의 위치를 찾을 때까지
    {
        index = index % MAX_HASH_TABLE_SIZE; //버킷의 위치를 제산 함수 방식으로 증가
    }
    return index; //해당 버킷을 찾으면 그 버킷의 해시코드 반환
}