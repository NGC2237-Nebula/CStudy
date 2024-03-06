#include<stdio.h>

typedef int ElemType;

/* 希尔排序 */
void ShellSort(ElemType* a, int n) {
	int i, j, dk;
	ElemType temp;
	//增量dk的变化，dk = dk/2
	for (dk = n / 2; dk > 0; dk /= 2) {
		for (i = dk; i < n; i++) {
			//需将a[i]插入有序增量子表中
			if (a[i] < a[i - dk]) {
				//存到临时变量中
				temp = a[i];
				for (j = i - dk; j >= 0 && temp < a[j]; j -= dk)
					//统一记录后移，查找插入的位置
					a[j + dk] = a[j];
				a[j + dk] = temp;
			}
		}
	}
}

/* 打印结果 */
void SortPrint(ElemType* a, int len) {
	printf("希尔排序: ");
	for (int i = 0; i < len; i++)
		printf("%d ", a[i]);
}

int main() {
	ElemType a[] = { 12,3,22,1,15,32,88,7,9 };
	int len = sizeof(a) / sizeof(a[0]);

	ShellSort(a, len);
	SortPrint(a, len);
}