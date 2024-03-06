#include<stdio.h>
#define Len 99

typedef int ElemType;

void Merge(ElemType a[], int low, int mid, int high) {
	int i, j, k;
	// 设置辅助数组，并将a[low..mid]和a[mid+1..high]的数据拷贝到b中
	ElemType b[Len];
	for (k = low; k <= high; k++)
		b[k] = a[k];
	// 判断a[low..mid]和a[mid+1..high]最前面的哪个小，把小的那一个拷贝到最前面
	for (i = low, j = mid + 1, k = i; i <= mid && j <= high; k++) {
		if (b[i] <= b[j]) {
			a[k] = b[i];
			i++;
		}
		else {
			a[k] = b[j];
			j++;
		}
	}
	// 若一个序列结束后，另一个序列还没有结束，说明 未结束的序列 后面的值都比 结束的序列的 都大
	// 直接拷贝到已经排好序的后面
	while (i <= mid) a[k++] = b[i++];
	while (j <= high) a[k++] = b[j++];
}

void MergeSort(ElemType a[], int low, int high) {
	if (low < high) {
		int mid = (low + high) / 2;
		MergeSort(a, low, mid);
		MergeSort(a, mid + 1, high);
		Merge(a, low, mid, high);
	}
}

void SortPrint(int* a, int len) {
	printf("归并排序: ");
	for (int i = 0; i < len; i++)
		printf("%d ", a[i]);
}

int main() {
	ElemType a[] = { 12,3,22,1,15,32,88,7,9 };
	int len = sizeof(a) / sizeof(a[0]);

	MergeSort(a, 0, len - 1);
	SortPrint(a, len);

	return 0;
}