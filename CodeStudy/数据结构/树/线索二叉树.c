#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/* 线索二叉树 */
typedef char ThreadType;
typedef struct ThreadNode {
	ThreadType data;
	struct ThreadNode* lchild, * rchild;
	int ltag, rtag; //左右线索标志
}ThreadNode, *ThreadTree;


ThreadTree createTree(); //先序方法创建二叉树
void threaded(ThreadNode* q); //对当前结点进行线索化操作
void createInThreadTree(ThreadTree T); //中序线索化二叉树T
void inThread(ThreadTree T); //中序遍历二叉树，边遍历边线索化
void preThread(ThreadTree T); //先序遍历二叉树，边遍历边线索化
void postThread(ThreadTree T); //后序遍历二叉树，边遍历边线索化

void visit(ThreadNode* node); //对结点T的操作
ThreadNode* firstNode(ThreadNode* p); // 找到以P为根节点的子树中，中序遍历首先被遍历的节点
ThreadNode* lastNode(ThreadNode* p); // 找到以P为根节点的子树中，中序遍历最后被遍历的节点
ThreadNode* nextNode(ThreadNode* p); // 在中序线索二叉树中找到P的后继节点
ThreadNode* preNode(ThreadNode* p); // 在中序线索二叉树中找到P的前驱节点
void inOrder_thread(ThreadNode* T); // 中序遍历二叉树（利用线索实现的非递归算法，空间复杂度O（1））
void revInOrder_thread(ThreadNode* T); // 逆向中序遍历二叉树

//指向当前访问节点的前驱
ThreadNode* pre = NULL;

/*-------- 线索化二叉树 --------*/
//先序方法创建二叉树
ThreadTree createTree() {
	ThreadTree root;
	ThreadType data;
	scanf("%c", &data);

	if (data == '#') root = NULL;
	else {
		root = (ThreadNode*)malloc(sizeof(ThreadNode));
		root->data = data;
		root->ltag = root->rtag = 0;
		root->lchild = createTree();
		root->rchild = createTree();
	}
	return root;
}
//对当前结点进行线索化操作
void threaded(ThreadNode* p) {
	// 左指针为空，建立前驱线索
	if (p->lchild == NULL) {
		p->lchild = pre;
		p->ltag = 1;
	}
	// 建立前驱节点的后继线索
	if (pre != NULL && pre->rchild == NULL) {
		pre->rchild = p;
		pre->rtag = 1;
	}
	// 指针后移
	pre = p;
}
//中序线索化二叉树T
void createInThreadTree(ThreadTree T) {
	pre = NULL;
	if (T != NULL) {
		inThread(T);
		if (pre->rchild == NULL)
			pre->rtag = 1;
	}
}
//中序遍历二叉树，边遍历边线索化
void inThread(ThreadTree T) {
	if (T != NULL) {
		inThread(T->lchild);
		threaded(T);
		inThread(T->rchild);
	}
}
//先序遍历二叉树，边遍历边线索化
void preThread(ThreadTree T) {
	if (T != NULL) {
		threaded(T);
		// lchild不是前驱线索时才访问其左孩子
		// 不加该条件，可能会出现两个指针无限循环打转
		if(T->ltag==0) 
			preThread(T->lchild);
		preThread(T->rchild);
	}
}
//后序遍历二叉树，边遍历边线索化
void postThread(ThreadTree T) {
	if (T != NULL) {
		// 不会出现先序遍历的情况
		// 因为进行 visit(T) 的时候，其左孩子、右孩子已经处理完，不会再访问了
		postThread(T->lchild);
		postThread(T->rchild);
		threaded(T);
	}
}

/*-------- 遍历线索二叉树 --------*/
//对结点T的操作
void visit(ThreadNode* node) {
	printf("%c ", node->data);
}
// 找到以P为根节点的子树中，中序遍历首先被遍历的节点
ThreadNode* firstNode(ThreadNode* p) {
	//循环找到中序遍历的最左下角的节点（不一定是叶子节点）
	while (p->ltag == 0) p = p->lchild;
	return p;
}
// 找到以P为根节点的子树中，中序遍历最后被遍历的节点
ThreadNode* lastNode(ThreadNode* p) {
	//循环找到中序遍历的最右下角的节点（不一定是叶子节点）
	while (p->rtag == 0) p = p->rchild;
	return p;
}
// 在中序线索二叉树中找到P的后继节点
ThreadNode* nextNode(ThreadNode* p) {
	// p->rtag = 0(指示P节点的左孩子),返回右子树最左下节点
	if (p->rtag == 0) return firstNode(p->rchild);
	// p->rtag = 1(指示线索),直接返回后继线索
	else return p->rchild;
}
// 在中序线索二叉树中找到P的前驱节点
ThreadNode* preNode(ThreadNode* p) {
	// p->rtag = 0(指示P节点的右孩子),返回左子树最右下节点
	if (p->ltag == 0) return lastNode(p->lchild);
	// p->rtag = 1(指示线索),直接返回前驱线索
	else return p->lchild;
}
// 中序遍历二叉树（利用线索实现的非递归算法，空间复杂度O（1））
void inOrder_thread(ThreadNode* T) {
	for (ThreadNode* p = firstNode(T); p != NULL; p = nextNode(p)) {
		visit(p);
	}
}
// 逆向中序遍历二叉树
void revInOrder_thread(ThreadNode* T) {
	for (ThreadNode* p = lastNode(T); p != NULL; p = preNode(p)) {
		visit(p);
	}
}


int main() {
	// 输入先序序列 ABD##E#H##CF##G## 创建二叉树
	printf("输入先序序列创建二叉树:");
	ThreadTree root = createTree();
	createInThreadTree(root);

	printf("\n中序遍历:");
	inOrder_thread(root);
	printf("\n逆向中序遍历:");
	revInOrder_thread(root);
}