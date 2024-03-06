#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define InitSize 50

/*顺序表*/
typedef int ElemType;
typedef struct {
	ElemType* elem;
	int TableLen;
}Table;

// 初始化顺序表
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

// 二分查找
int BinarySearch(Table table, ElemType key) {
	int low = 0, high = table.TableLen - 1, mid;

	while (low <= high) {
		mid = (low + high) / 2;
		// 从前半部分开始找                                                                                                   
		if (key < table.elem[mid]) {
			high = mid - 1;
		}
		// 从后半部分开始找
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
	printf("元素 %d 位于下标 %d 处", key, BinarySearch(table, key));
}