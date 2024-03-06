#include<stdio.h>

typedef int ElemType;

/* 划分操作 */
int Partition(ElemType A[], int low, int high) {
    ElemType pivot = A[low];
    while (low < high) {
        while (low < high && A[high] >= pivot) high--;
        A[low] = A[high];
        while (low < high && A[low] <= pivot) low++;
        A[high] = A[low];
    }
    A[low] = pivot;
    return low;
}

/* 快速排序 */
void QuickSort(ElemType* a, int low, int high) {
    if (low < high) {
        int pivotops = Partition(a, low, high);
        QuickSort(a, low, pivotops - 1);
        QuickSort(a, pivotops + 1, high);
    }
}

/* 打印结果 */
void SortPrint(ElemType* a, int len) {
    printf("快速排序:");
    for (int i = 0; i < len; i++)
        printf("%d ", a[i]);
}

int main() {
    ElemType a[] = { 12,3,22,4,44,44,1,5,32,88,7,9 };
    int len = sizeof(a) / sizeof(a[0]);

    QuickSort(a, 0, len - 1);
    SortPrint(a, len);
    return 0;
}