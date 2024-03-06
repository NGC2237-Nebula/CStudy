#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define InitSize 50

/*˳���*/
typedef int ElemType;
typedef struct {
	ElemType* elem;
	int TableLen;
}Table;

// ��ʼ��˳���
Table InitTable() {
	ElemType input[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	Table table;
	table.elem = (ElemType*)malloc(sizeof(ElemType) * InitSize);
	table.TableLen = sizeof(input) / sizeof(ElemType);
	for (int i = 0; i < table.TableLen; i++) {
		table.elem[i] = input[i];
	}
	return table;
}

// ���ֲ���
int BinarySearch(Table table, ElemType key) {
	int low = 0, high = table.TableLen - 1, mid;

	while (low <= high) {
		mid = (low + high) / 2;
		// ��ǰ�벿�ֿ�ʼ��                                                                                                   
		if (key < table.elem[mid]) {
			high = mid - 1;
		}
		// �Ӻ�벿�ֿ�ʼ��
		else if (key > table.elem[mid]) {
			low = mid + 1;
		}
		else {
			return mid;
		}
	}
	return -1;
}


int main() {
	Table table = InitTable();
	ElemType key = 5;
	printf("Ԫ�� %d λ���±� %d ��", key, BinarySearch(table, key));
}