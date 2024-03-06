#include<stdio.h>

typedef int ElemType;

/* ϣ������ */
void ShellSort(ElemType* a, int n) {
	int i, j, dk;
	ElemType temp;
	//����dk�ı仯��dk = dk/2
	for (dk = n / 2; dk > 0; dk /= 2) {
		for (i = dk; i < n; i++) {
			//�轫a[i]�������������ӱ���
			if (a[i] < a[i - dk]) {
				//�浽��ʱ������
				temp = a[i];
				for (j = i - dk; j >= 0 && temp < a[j]; j -= dk)
					//ͳһ��¼���ƣ����Ҳ����λ��
					a[j + dk] = a[j];
				a[j + dk] = temp;
			}
		}
	}
}

/* ��ӡ��� */
void SortPrint(ElemType* a, int len) {
	printf("ϣ������: ");
	for (int i = 0; i < len; i++)
		printf("%d ", a[i]);
}

int main() {
	ElemType a[] = { 12,3,22,1,15,32,88,7,9 };
	int len = sizeof(a) / sizeof(a[0]);

	ShellSort(a, len);
	SortPrint(a, len);
}