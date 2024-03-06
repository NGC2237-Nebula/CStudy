#include<stdio.h>

typedef int ElemType;

/* 折半插入排序 */
void BinaryInsertSort(ElemType*a, int len) {
	int i, j, low, mid, high;
	ElemType temp;
	for (i = 1; i < len; i++) {
		// 设置折半查找的范围
		low = 0;
		high = i - 1;
		temp = a[i];
		// 进入折半查找
		while (low <= high) {
			// 取中间点
			mid = (low + high) / 2;
			// 如果小于中间的元素，则查找左半子表
			// 否则查找右半子表
			if (temp < a[mid])
				high = mid - 1;
			else
				low = mid + 1;
		}

		// 统一后移元素，空出插入位置
		for (j = i - 1; j >= high + 1; j--)
			a[j + 1] = a[j];
		a[high + 1] = temp;
	}
}

/* 打印结果 */
void SortPrint(ElemType* a, int len) {
	printf("折半插入排序: ");
	for (int i = 0; i < len; i++)
		printf("%d ", a[i]);
}

int main() {
	ElemType a[] = { 12,3,22,1,15,32,88,7,9 };
	int len = sizeof(a) / sizeof(a[0]);

	BinaryInsertSort(a, len);
	SortPrint(a, len);
}