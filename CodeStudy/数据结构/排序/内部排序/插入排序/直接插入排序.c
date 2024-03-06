#include<stdio.h>

typedef int ElemType;

/* 直接插入排序（使用临时变量） */
void DirectInsertSort_temp(ElemType* a, int len) {
	// 排序
	int i, j, temp;
	for (i = 1; i < len; i++) {
		temp = a[i];
		if (a[i] < a[i - 1]) {
			for (j = i - 1; j >= 0 && temp < a[j]; --j)
				a[j + 1] = a[j];
			a[j + 1] = temp;
		}
	}
	// 打印排序结果
	printf("\n直接插入排序（使用临时变量）: ");
	for (i = 0; i < len; i++)
		printf("%d ", a[i]);
}

/* 直接插入排序（使用哨兵） */
void DirectInsertSort_sentry(ElemType* a, int len) {
	// 排序
	int i, j;
	for (i = 2; i < len; i++) {
		a[0] = a[i];
		if (a[i] < a[i - 1]) {
			for (j = i - 1; a[0] < a[j]; --j)
				a[j + 1] = a[j];
			a[j + 1] = a[0];
		}
	}
	// 打印排序结果
	printf("\n直接插入排序（使用哨兵）: ");
	for (i = 1; i < len; i++)
		printf("%d ", a[i]);
}

int main() {
	ElemType a[] = { 12,3,22,1,15,32,88,7,9 };
	int a_len = sizeof(a) / sizeof(a[0]);
	
	ElemType b[] = { 0,12,3,22,1,15,32,88,7,9 };
	int b_len = sizeof(b) / sizeof(b[0]);

	DirectInsertSort_temp(a, a_len);
	DirectInsertSort_sentry(b, b_len);
}