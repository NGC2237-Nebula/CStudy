#include<stdio.h>

typedef int ElemType;

/* 交换函数 */
void sawp(ElemType* a, ElemType* b) {
	ElemType temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

/*调整大根堆*/
void HeapAdjust(ElemType a[], int k, int len) {
	a[0] = a[k]; // k值记录当前调整的节点最终要放置的位置，用a[0]暂存
	for (int i = 2 * k; i <= len; i *= 2) {
		// 获取调整节点关键字较大的孩子
		if (i<len && a[i + 1]>a[i])
			i++;
		// 若根比两个孩子的值都大，筛选结束
		if (a[0] >= a[i]) break;
		// 将根和较大的孩子进行交换
		else {
			a[k] = a[i];
			k = i;// 调整k值，用于for循环的继续向下筛选
		}
	}
	a[k] = a[0];
}

/* 创建大根堆 */
void BuildMaxHeap(ElemType a[], int len) {
	for (int i = len / 2; i > 0; i--)
		HeapAdjust(a, i, len);			//从最后一个父结点开始做最大堆调整
}

/*堆排序*/
void HeapSort(ElemType a[], int len) {
	// 创建大根堆，时间复杂度为 O(n)
	BuildMaxHeap(a, len);
	// n-1趟交换和建堆的过程，时间复杂度 O(logn)
	for (int i = len - 1; i >= 0; i--) {
		sawp(&a[i],&a[1]); // 将大根堆的根（最大值）换到最后
		HeapAdjust(a, 1, i-1); // 调整，将剩余的n-1个元素整理成大根堆
	}
}

/* 打印结果 */
void SortPrint(ElemType a[], int len) {
	printf("堆排序: ");
	for (int i = 1; i < len; i++)
		printf("%d ", a[i]);
}


int main() {
	ElemType a[] = { 0,12,3,22,1,15,32,88,7,9 };
	int len = sizeof(a) / sizeof(a[0]);

	HeapSort(a, len);
	SortPrint(a, len);
}