#include <stdio.h>

typedef int ElemType;

/* ½»»»º¯Êý */
void sawp(ElemType* a, ElemType* b) {
	ElemType temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

/* Ã°ÅÝÅÅÐò */
void BubbleSort(ElemType a[], int n) {
	for (int i = 0; i < n - 1; i++) {
		int flag = 0;
		for (int j = n - 1; j > i; j--) {
			if (a[j - 1] > a[j]) {
				sawp(&a[j - 1], &a[j]);
				flag = 1;
			}
		}
		if (flag == 0)
			return;
	}
}

/* ´òÓ¡½á¹û */
void SortPrint(ElemType* a, int len) {
	printf("Ã°ÅÝÅÅÐò: ");
	for (int i = 0; i < len; i++)
		printf("%d ", a[i]);
}

int main() {
	ElemType a[] = { 12,3,22,1,15,32,88,7,9 };
	int len = sizeof(a) / sizeof(a[0]);

	BubbleSort(a, len);
	SortPrint(a, len);
}