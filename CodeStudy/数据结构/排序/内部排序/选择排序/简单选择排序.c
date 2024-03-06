#include<stdio.h>

typedef int ElemType;

/* 交换函数 */
void sawp(ElemType* a, ElemType* b) {
    ElemType temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

/* 简单选择排序 */
void SimpleSelectSort(ElemType a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[min])	min = j;
        if (min != i)
            sawp(&a[i], &a[min]);
    }
}

/* 打印结果 */
void SortPrint(ElemType* a, int len) {
    printf("简单选择排序: ");
    for (int i = 0; i < len; i++)
        printf("%d ", a[i]);
}

int main() {
    ElemType a[] = { 12,3,22,1,15,32,88,7,9 };
    int len = sizeof(a) / sizeof(a[0]);

    SimpleSelectSort(a, len);
    SortPrint(a, len);
}