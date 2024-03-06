#include<stdio.h>

typedef int ElemType;

/* �������� */
void sawp(ElemType* a, ElemType* b) {
	ElemType temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

/*���������*/
void HeapAdjust(ElemType a[], int k, int len) {
	a[0] = a[k]; // kֵ��¼��ǰ�����Ľڵ�����Ҫ���õ�λ�ã���a[0]�ݴ�
	for (int i = 2 * k; i <= len; i *= 2) {
		// ��ȡ�����ڵ�ؼ��ֽϴ�ĺ���
		if (i<len && a[i + 1]>a[i])
			i++;
		// �������������ӵ�ֵ����ɸѡ����
		if (a[0] >= a[i]) break;
		// �����ͽϴ�ĺ��ӽ��н���
		else {
			a[k] = a[i];
			k = i;// ����kֵ������forѭ���ļ�������ɸѡ
		}
	}
	a[k] = a[0];
}

/* ��������� */
void BuildMaxHeap(ElemType a[], int len) {
	for (int i = len / 2; i > 0; i--)
		HeapAdjust(a, i, len);			//�����һ������㿪ʼ�����ѵ���
}

/*������*/
void HeapSort(ElemType a[], int len) {
	// ��������ѣ�ʱ�临�Ӷ�Ϊ O(n)
	BuildMaxHeap(a, len);
	// n-1�˽����ͽ��ѵĹ��̣�ʱ�临�Ӷ� O(logn)
	for (int i = len - 1; i >= 0; i--) {
		sawp(&a[i],&a[1]); // ������ѵĸ������ֵ���������
		HeapAdjust(a, 1, i-1); // ��������ʣ���n-1��Ԫ������ɴ����
	}
}

/* ��ӡ��� */
void SortPrint(ElemType a[], int len) {
	printf("������: ");
	for (int i = 1; i < len; i++)
		printf("%d ", a[i]);
}


int main() {
	ElemType a[] = { 0,12,3,22,1,15,32,88,7,9 };
	int len = sizeof(a) / sizeof(a[0]);

	HeapSort(a, len);
	SortPrint(a, len);
}