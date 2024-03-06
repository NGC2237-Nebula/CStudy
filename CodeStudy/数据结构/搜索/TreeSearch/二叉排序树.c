#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/* ���������� */
typedef int TreeType;
typedef struct BSTNode {
	TreeType data;
	struct BSTNode* lchild, * rchild;
}*BSTree, BSTNode;

BSTNode* CreateTreeNode(TreeType data); // �������������
BSTNode* InsertTree(TreeType data, BSTree root); // ����Ԫ��
void PreOrder(BSTree T); // �������
void InOrder(BSTree T);	 // �������
BSTree FindMin(BSTree T);  // ������Сֵ�����ظý��
BSTree FindMax(BSTree T);  // �������ֵ�����ظý��
BSTree FindKey_nonrecursion(BSTree T, TreeType key);	// ����ָ������Ԫ��(�ǵݹ�)
BSTree FindKey_recursion(BSTree T, TreeType key);		// ����ָ������Ԫ��(�ݹ�)
BSTree DeleteData(BSTree T, TreeType element);			// ɾ��ָ��Ԫ�صĽ��

// �������������
BSTNode* CreateTreeNode(TreeType data) {
	BSTNode* p = (BSTNode*)malloc(sizeof(struct BSTNode));
	p->lchild = p->rchild = NULL;
	p->data = data;
	return p;
}
// ����Ԫ��
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
// �������
void PreOrder(BSTree T){
	if (T == NULL) return;
	printf("%d ", T->data);
	PreOrder(T->lchild);
	PreOrder(T->rchild);
}
// �������
void InOrder(BSTree T){
	if (T == NULL) return;
	InOrder(T->lchild);
	printf("%d ", T->data);
	InOrder(T->rchild);
}
// ������Сֵ�����ظý��
BSTree FindMin(BSTree T){
	if (T == NULL) return NULL;
	BSTree min = T;
	while (min->lchild != NULL)
		min = min->lchild;
	return min;
}
// �������ֵ�����ظý��
BSTree FindMax(BSTree T){
	if (T == NULL) return NULL;
	BSTree max = T;
	while (max->rchild != NULL)
		max = max->rchild;
	return max;
}
// ����ָ������Ԫ��(�ǵݹ�)
BSTree FindKey_nonrecursion(BSTree T, TreeType key) {
	while (T != NULL && key != T->data) {
		if (T->data > key) T = T->lchild;
		else T = T->rchild;
	}
	return T;
}
// ����ָ������Ԫ��(�ݹ�)
BSTree FindKey_recursion(BSTree T, TreeType key) {
	if (T == NULL) return NULL;
	if (key == T->data) return T;
	else if (key < T->data) return FindKey_recursion(T->rchild, key);
	else return FindKey_recursion(T->lchild, key);
}
// ɾ��ָ��Ԫ�صĽ��
BSTree DeleteData(BSTree T, TreeType element){
	BSTree parent_p, p, r;
	p = T; parent_p = NULL;
	// �����ҽ��λ��p 
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
	return T; // ��ɾ���ɹ��򷵻ظý�㣬���򷵻�NULL
}

int main() {
	TreeType a[] = { 3, 2, 4, 5, 1 };
	BSTree T = NULL;
	for (int i = 0; i < 5; i++) 
		T = InsertTree(a[i], T);

	printf("�������: ");	InOrder(T);
	printf("\n�������: ");	PreOrder(T);

	BSTree p = FindMin(T);
	if (p) 	printf("\n���ֵ: %d", p->data);
	else 	printf("\nδ�ҵ����ֵ");

	BSTree q = FindMax(T);
	if (q) 	printf("\n��Сֵ: %d", q->data);
	else 	printf("\nδ�ҵ���Сֵ");

	int find_data;
	printf("\n��������ҵ�Ԫ��: ");
	scanf("%d", &find_data);
	p = FindKey_nonrecursion(T, find_data);
	if (p)	printf("�ҵ�ָ��Ԫ��: %d", p->data);
	else	printf("δ�ҵ�ָ��Ԫ��");

	int delete_data;
	printf("\n������ɾ����Ԫ��: ");
	scanf("%d", &delete_data);
	BSTree r = DeleteData(T, delete_data);
	printf("ɾ���� �������: "); InOrder(T);
	printf("\nɾ���� �������: "); PreOrder(T);
}