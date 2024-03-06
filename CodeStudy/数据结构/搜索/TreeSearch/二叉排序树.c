#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/* 二叉排序树 */
typedef int TreeType;
typedef struct BSTNode {
	TreeType data;
	struct BSTNode* lchild, * rchild;
}*BSTree, BSTNode;

BSTNode* CreateTreeNode(TreeType data); // 创建二叉树结点
BSTNode* InsertTree(TreeType data, BSTree root); // 插入元素
void PreOrder(BSTree T); // 先序遍历
void InOrder(BSTree T);	 // 中序遍历
BSTree FindMin(BSTree T);  // 查找最小值，返回该结点
BSTree FindMax(BSTree T);  // 查找最大值，返回该结点
BSTree FindKey_nonrecursion(BSTree T, TreeType key);	// 查找指定数据元素(非递归)
BSTree FindKey_recursion(BSTree T, TreeType key);		// 查找指定数据元素(递归)
BSTree DeleteData(BSTree T, TreeType element);			// 删除指定元素的结点

// 创建二叉树结点
BSTNode* CreateTreeNode(TreeType data) {
	BSTNode* p = (BSTNode*)malloc(sizeof(struct BSTNode));
	p->lchild = p->rchild = NULL;
	p->data = data;
	return p;
}
// 插入元素
BSTNode* InsertTree(TreeType data, BSTree root){
	if (root == NULL) {
		root = CreateTreeNode(data);
		return root;
	}
	if (data < root->data)
		root->lchild = InsertTree(data, root->lchild);
	if (data > root->data)
		root->rchild = InsertTree(data, root->rchild);
	return root;
}
// 先序遍历
void PreOrder(BSTree T){
	if (T == NULL) return;
	printf("%d ", T->data);
	PreOrder(T->lchild);
	PreOrder(T->rchild);
}
// 中序遍历
void InOrder(BSTree T){
	if (T == NULL) return;
	InOrder(T->lchild);
	printf("%d ", T->data);
	InOrder(T->rchild);
}
// 查找最小值，返回该结点
BSTree FindMin(BSTree T){
	if (T == NULL) return NULL;
	BSTree min = T;
	while (min->lchild != NULL)
		min = min->lchild;
	return min;
}
// 查找最大值，返回该结点
BSTree FindMax(BSTree T){
	if (T == NULL) return NULL;
	BSTree max = T;
	while (max->rchild != NULL)
		max = max->rchild;
	return max;
}
// 查找指定数据元素(非递归)
BSTree FindKey_nonrecursion(BSTree T, TreeType key) {
	while (T != NULL && key != T->data) {
		if (T->data > key) T = T->lchild;
		else T = T->rchild;
	}
	return T;
}
// 查找指定数据元素(递归)
BSTree FindKey_recursion(BSTree T, TreeType key) {
	if (T == NULL) return NULL;
	if (key == T->data) return T;
	else if (key < T->data) return FindKey_recursion(T->rchild, key);
	else return FindKey_recursion(T->lchild, key);
}
// 删除指定元素的结点
BSTree DeleteData(BSTree T, TreeType element){
	BSTree parent_p, p, r;
	p = T; parent_p = NULL;
	// 查找找结点位置p 
	while (p != NULL) {
		if (p->data == element) break;
		parent_p = p;
		if (p->data > element) p = p->lchild;
		else p = p->rchild;
	}
	if (p == NULL) return T;
	if (p->lchild == NULL) {
		if (parent_p == NULL) T = p->rchild;
		else if (parent_p->lchild == p) parent_p->lchild = p->lchild;
		else parent_p->rchild = p->rchild;
	}
	else {
		BSTree rr = p;
		for (r = p->rchild; r->lchild != NULL; r = r->lchild) rr = r;
		p->data = r->data;
		if (rr == p)
			p->rchild = r->rchild;
		else rr->lchild = r->rchild;
		p = r;
	}
	free(p);
	return T; // 若删除成功则返回该结点，否则返回NULL
}

int main() {
	TreeType a[] = { 3, 2, 4, 5, 1 };
	BSTree T = NULL;
	for (int i = 0; i < 5; i++) 
		T = InsertTree(a[i], T);

	printf("中序遍历: ");	InOrder(T);
	printf("\n先序遍历: ");	PreOrder(T);

	BSTree p = FindMin(T);
	if (p) 	printf("\n最大值: %d", p->data);
	else 	printf("\n未找到最大值");

	BSTree q = FindMax(T);
	if (q) 	printf("\n最小值: %d", q->data);
	else 	printf("\n未找到最小值");

	int find_data;
	printf("\n输入需查找的元素: ");
	scanf("%d", &find_data);
	p = FindKey_nonrecursion(T, find_data);
	if (p)	printf("找到指定元素: %d", p->data);
	else	printf("未找到指定元素");

	int delete_data;
	printf("\n输入需删除的元素: ");
	scanf("%d", &delete_data);
	BSTree r = DeleteData(T, delete_data);
	printf("删除后 中序遍历: "); InOrder(T);
	printf("\n删除后 先序遍历: "); PreOrder(T);
}