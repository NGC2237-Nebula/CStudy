#include<stdio.h>
#define Len 99

typedef int ElemType;

void Merge(ElemType a[], int low, int mid, int high) {
	int i, j, k;
	// ���ø������飬����a[low..mid]��a[mid+1..high]�����ݿ�����b��
	ElemType b[Len];
	for (k = low; k <= high; k++)
		b[k] = a[k];
	// �ж�a[low..mid]��a[mid+1..high]��ǰ����ĸ�С����С����һ����������ǰ��
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
	// ��һ�����н�������һ�����л�û�н�����˵�� δ���������� �����ֵ���� ���������е� ����
	// ֱ�ӿ������Ѿ��ź���ĺ���
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
	printf("�鲢����: ");
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