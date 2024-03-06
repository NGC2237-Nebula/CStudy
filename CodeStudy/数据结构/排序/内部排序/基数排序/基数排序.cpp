#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node* next;
}Node, * List;

void InitList(Node* plist)
{
    assert(plist != NULL);
    plist->next = NULL;
}

Node* GetNode(int val)
{
    Node* pGet = (Node*)malloc(sizeof(Node));
    assert(pGet != NULL);

    pGet->data = val;
    pGet->next = NULL;
    return pGet;
}

void Insert_tail(Node* plist, int val)
{
    assert(plist != NULL);

    Node* p = plist;
    while (p->next != NULL)
    {
        p = p->next;
    }
    Node* pGet = GetNode(val);
    p->next = pGet;
}

bool DelHeadNode(Node* plist, int* res)
{
    assert(plist != NULL);

    Node* pDel = plist->next;
    if (pDel == NULL)
    {
        return false;
    }

    *res = pDel->data;
    plist->next = pDel->next;
    free(pDel);
    pDel = NULL;
    return true;
}

int GetMaxBit(int* arr, int length)
{
    assert(arr != NULL);
    int max = INT_MIN;
    for (int i = 0; i < length; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    int digit = 0;
    while (max != 0)
    {
        digit++;
        max /= 10;
    }
    return digit;
}

int GetNum(int num, int figures)   // 123   123 / 1 % 10 == 3      123 / 10 % 10 == 2   123 / 100 % 10 == 1   
{
    int base = pow((double)10, (figures));
    return num / base % 10;
}


//figures --> ������������figuresλ������
void Radix(int* arr, int length, int figures)
{
    Node head[10];
    for (int i = 0; i < 10; i++)
    {
        InitList(&head[i]);  // ��ʼ��10��Ͱ
    }

    int tmp = 0;
    // 1����Ͱ == �� �õ����֣��жϵ�figuresλ������Ϊ���٣�������Ӧ��Ͱ
    int i = 0;
    for (; i < length; i++)
    {
        tmp = GetNum(arr[i], figures);  // ��figuresλ������Ϊtmp
        Insert_tail(&head[tmp], arr[i]); // �� arr[i] ���� tmpͰ��
    }

    // 2����Ͱ
    i = 0; // i ���������±�
    int j = 0;
    while (j < 10)    // j ����Ͱ�ĸ���
    {
        while (DelHeadNode(&head[j], &arr[i]))
        {
            i++;
        }
        j++;
    }
}


void RadixSort(int* arr, int length)
{
    int count = GetMaxBit(arr, length);
    for (int i = 0; i < count; i++)
    {
        Radix(arr, length, i);
    }
}

void Show(int* arr, int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


void test(int* arr, int length)
{
    RadixSort(arr, length);
    Show(arr, length);
}

void test1()
{
    int arr[] = { 1,2,3,4,12,4444,2222,1112,11 };
    int length = sizeof(arr) / sizeof(arr[0]);
    test(arr, length);
}

void test2()
{
    int arr[] = { 336,719,329,170,66,511,36,519,200,504 };
    int length = sizeof(arr) / sizeof(arr[0]);
    test(arr, length);
}

int main()
{
    test1();
    test2();
    return 0;
}