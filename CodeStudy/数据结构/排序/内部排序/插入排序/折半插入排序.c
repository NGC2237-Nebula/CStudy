#include<stdio.h>

typedef int ElemType;

/* �۰�������� */
void BinaryInsertSort(ElemType*a, int len) {
	int i, j, low, mid, high;
	ElemType temp;
	for (i = 1; i < len; i++) {
		// �����۰���ҵķ�Χ
		low = 0;
		high = i - 1;
		temp = a[i];
		// �����۰����
		while (low <= high) {
			// ȡ�м��
			mid = (low + high) / 2;
			// ���С���м��Ԫ�أ����������ӱ�
			// ��������Ұ��ӱ�
			if (temp < a[mid])
				high = mid - 1;
			else
				low = mid + 1;
		}

		// ͳһ����Ԫ�أ��ճ�����λ��
		for (j = i - 1; j >= high + 1; j--)
			a[j + 1] = a[j];
		a[high + 1] = temp;
	}
}

/* ��ӡ��� */
void SortPrint(ElemType* a, int len) {
	printf("�۰��������: ");
	for (int i = 0; i < len; i++)
		printf("%d ", a[i]);
}

int main() {
	ElemType a[] = { 12,3,22,1,15,32,88,7,9 };
	int len = sizeof(a) / sizeof(a[0]);

	BinaryInsertSort(a, len);
	SortPrint(a, len);
}