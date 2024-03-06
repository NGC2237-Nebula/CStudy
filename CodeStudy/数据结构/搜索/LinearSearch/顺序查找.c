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

// 顺序查找
int SequentialSearch(Table table, ElemType key) {
	int i;
	for (i = 0; i < table.TableLen && table.elem[i] != key; ++i);
	return i == table.TableLen ? -1:i;
}


int main() {
	Table table = InitTable();
	ElemType key = 5;
	printf("元素 %d 位于下标 %d 处", key, SequentialSearch(table, key));
}