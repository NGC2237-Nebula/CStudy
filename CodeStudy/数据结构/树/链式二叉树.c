#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


/* 链式二叉树 */
typedef char TreeType;
typedef struct BinaryTreeNode {
	TreeType data;
	struct BinaryTreeNode* lchild, * rchild;
}*BiTree, BiTNode;

/* 链式栈 */
typedef BiTNode* StackType;
typedef struct StackNode {
	StackType data;
	struct StackNode* next;
}StackNode;

typedef struct {
	StackNode* top;
}LinkStack;

/* 链式队列 */
typedef BiTNode* QueueType;
typedef struct QueueNode {
	QueueType data;
	struct QueueNode* next;
}QueueNode;

typedef struct {
	QueueNode* front, * rear;
}LinkQueue;


void InitQueue(LinkQueue* Q);//初始化队列
int IsQueueEmpty(LinkQueue Q);//判断队列是否为空
void EnQueue(LinkQueue* Q, QueueType data);//入队
int DeQueue(LinkQueue* Q, QueueType* x);//出队

void InitStack(LinkStack* S);//初始化栈
int IsStackEmpty(LinkStack S);//判断栈是否为空
int PushStack(LinkStack* L, StackType data);//入栈
int PopStack(LinkStack* L, StackType* data);//出栈
int GetStackTop(LinkStack* L, StackType* x);//取栈顶元素
int DestroyStack(LinkStack* L);//销毁栈

BiTree CreateTree();//先序方法创建二叉树
int Count_TreeSize(BiTree root);//计算所有结点数
int Count_LeafNode(BiTree root);//计算叶结点数
int Count_TreeDepth(BiTree root);//计算树的深度
int Count_TreeLevelSize(BiTNode* root, int level);//计算第i层节点个数
void ChangeRightLeft(BiTree root);//互换二叉树左右子树
void DestoryTree(BiTree* root);//二叉树销毁

void Visit(BiTNode* node);//对结点T的操作
void PreOrder_recursion(BiTree root);//先序遍历（递归） 
void InOrder_recursion(BiTree root);//中序遍历（递归） 
void PostOrder_recursion(BiTree root);//后序遍历（递归） 
void InOrder_non_recursion(BiTree root);//中序遍历（非递归）
void PreOrder_non_recursion(BiTree root);//先序遍历（非递归）
void LevelOrder(BiTree root);//层次遍历


/*------------- 队列基本操作 ---------------*/
//初始化队列
void InitQueue(LinkQueue* Q) {
	Q->front = Q->rear = (QueueNode*)malloc(sizeof(QueueNode)); // 分配头节点
	Q->front->next = NULL; //初始化为空
}
//判断队列是否为空
int IsQueueEmpty(LinkQueue Q) {
	if (Q.front == Q.rear) return 1;
	else return 0;
}
//入队
void EnQueue(LinkQueue* Q, QueueType data) {
	QueueNode* news = (QueueNode*)malloc(sizeof(QueueNode));
	news->data = data; // 创建新节点，插入队列尾部 
	news->next = NULL;
	Q->rear->next = news;
	Q->rear = news;
}
//出队
int DeQueue(LinkQueue* Q, QueueType* x) {
	if (Q->front == Q->rear) return 0;
	QueueNode* del = Q->front->next;
	*x = del->data;
	Q->front->next = del->next;
	if (Q->rear == del)
		Q->rear = Q->front; // 若原队列只有一个节点，删除后变空 
	free(del);
	return 1;
}


/*------------- 栈基本操作 ---------------*/
//初始化栈
void InitStack(LinkStack* S) {
	S->top = (StackNode*)malloc(sizeof(StackNode)); // 分配头节点
	S->top = NULL; //初始化为空
}
//判断栈是否为空
int IsStackEmpty(LinkStack S) {
	if (S.top == NULL) return 1;
	else return 0;
}
//入栈
int PopStack(LinkStack* L, StackType* data) {
	StackNode* del;
	if (L->top == NULL)	return -1;
	else {
		del = L->top;
		*data = del->data;
		L->top = L->top->next;
		free(del);
		return 0;
	}
}
//出栈
int PushStack(LinkStack* L, StackType data) {
	StackNode* news = (StackNode*)malloc(sizeof(struct StackNode));
	if (news == NULL)	return -1;
	else {
		news->data = data;
		news->next = L->top;
		L->top = news;
		return 0;
	}
}
//取栈顶元素
int GetStackTop(LinkStack* L, StackType* x) {
	if (L->top == NULL) {
		*x = NULL;
		return -1;
	}
	else {
		*x = L->top->data;
		return 1;
	}
}
//销毁栈
int DestroyStack(LinkStack* L) {
	int cnt = 0;
	if (L == NULL)	return 0;
	struct StackNode* p = L->top, * q;
	free(L);
	while (p->next != NULL) {
		q = p->next;
		cnt++;
		free(p);
		p = q;
	}
	return cnt;
}


/*------------- 树的操作 ---------------*/
//先序方法创建二叉树
BiTree CreateTree() {
	BiTree root;
	TreeType data;
	scanf("%c", &data);

	if (data == '#') root = NULL;
	else {
		root = (struct BinaryTreeNode*)malloc(sizeof(struct BinaryTreeNode));
		root->data = data;
		root->lchild = CreateTree();
		root->rchild = CreateTree();
	}
	return root;
}
//计算所有结点数
int Count_TreeSize(BiTree root) {
	if (root == NULL) return 0;
	return Count_TreeSize(root->lchild) + Count_TreeSize(root->rchild) + 1;
}
//计算叶结点数
int Count_LeafNode(BiTree root) {
	if (root == NULL)	return 0;
	else if (root->lchild == NULL && root->rchild == NULL)	return 1;
	else return Count_LeafNode(root->lchild) + Count_LeafNode(root->rchild);
}
//计算树的深度
int Count_TreeDepth(BiTree root) {
	if (root == NULL) {
		return 0;
	}
	else {
		int l = Count_TreeDepth(root->lchild);
		int r = Count_TreeDepth(root->rchild);
		return l > r ? l + 1 : r + 1;
	}
}
//计算第i层节点个数
int Count_TreeLevelSize(BiTNode* root, int level) {
	if (root == NULL)  return 0;
	if (level == 1) return 1;
	return Count_TreeLevelSize(root->lchild, level - 1) + Count_TreeLevelSize(root->rchild, level - 1);
}
//互换二叉树左右子树
void ChangeRightLeft(BiTree root) {
	BiTree temp;
	if (root == NULL);
	else if (root->lchild == NULL && root->rchild == NULL);
	else {
		temp = root->lchild;
		root->lchild = root->rchild;
		root->rchild = temp;
		ChangeRightLeft(root->lchild);
		ChangeRightLeft(root->rchild);
	}
}
//二叉树销毁
void DestoryTree(BiTree* root) {
	if (*root != NULL) {
		if ((*root)->lchild) //有左孩子
			DestoryTree(&(*root)->lchild);
		if ((*root)->rchild) //有右孩子
			DestoryTree(&(*root)->rchild);
		free(*root); 		//释放根结点
		*root = NULL; 		//空指针NULL
	}
}

//对结点T的操作
void Visit(BiTNode* node) {
	printf(" %c", node->data);
}
//先序遍历（递归） 
void PreOrder_recursion(BiTree root) {
	if (root != NULL) {
		Visit(root);
		PreOrder_recursion(root->lchild);
		PreOrder_recursion(root->rchild);
	}
}
//中序遍历（递归） 
void InOrder_recursion(BiTree root) {
	if (root != NULL) {
		InOrder_recursion(root->lchild);
		Visit(root);
		InOrder_recursion(root->rchild);
	}
}
//后序遍历（递归） 
void PostOrder_recursion(BiTree root) {
	if (root != NULL) {
		PostOrder_recursion(root->lchild);
		PostOrder_recursion(root->rchild);
		Visit(root);
	}
}
//先序遍历（非递归）
void PreOrder_non_recursion(BiTree root) {
	LinkStack S;
	InitStack(&S);
	BiTree p = root;
	while (p || !IsStackEmpty(S)) {
		if (p) {
			Visit(p);
			PushStack(&S, p);
			p = p->lchild;
		}
		else {
			PopStack(&S, &p);
			p = p->rchild;
		}
	}
}
//中序遍历（非递归）
void InOrder_non_recursion(BiTree root) {
	LinkStack S;
	InitStack(&S);
	BiTree p = root;
	while (p || !IsStackEmpty(S)) {
		if (p) {
			PushStack(&S, p);
			p = p->lchild;
		}
		else {
			PopStack(&S, &p);
			Visit(p);
			p = p->rchild;
		}
	}
}
//后续遍历（非递归）
void postOrder_non_recursion(BiTree root) {
	LinkStack S;
	InitStack(&S);
	BiTNode* p = root;
	BiTNode* r = NULL;
	while (p || !IsStackEmpty(S)) {
		if (p) {
			PushStack(&S, p);
			p = p->lchild;
		}
		else {
			GetStackTop(&S, &p);
			if (p->rchild && p->rchild != r) 
				p = p->rchild;
			else {
				PopStack(&S, &p);
				Visit(p);
				r = p;
				p = NULL;
			}
		}
	}
}
//层次遍历
void LevelOrder(BiTree root) {
	LinkQueue Q;
	InitQueue(&Q);
	BiTree p;
	EnQueue(&Q, root);
	while (!IsQueueEmpty(Q)) {
		DeQueue(&Q, &p);
		Visit(p);
		if (p->lchild != NULL) {
			EnQueue(&Q, p->lchild);
		}
		if (p->rchild != NULL) {
			EnQueue(&Q, p->rchild);
		}
	}
}


int main() {
	// 输入先序序列 ABD##E#H##CF##G## 创建二叉树
	printf("输入先序序列创建二叉树:");
	BiTree root = CreateTree();

	printf("\n先序遍历(递  归):");
	PreOrder_recursion(root);
	printf("\n先序遍历(非递归):");
	PreOrder_non_recursion(root);

	printf("\n中序遍历(递  归):");
	InOrder_recursion(root);
	printf("\n中序遍历(非递归):");
	InOrder_non_recursion(root);

	printf("\n后序遍历(递  归):");
	PostOrder_recursion(root);
	printf("\n后序遍历(非递归):");
	postOrder_non_recursion(root);

	printf("\n层次遍历:");
	LevelOrder(root);

	ChangeRightLeft(root);
	printf("\n交换左右子树后的先序遍历：");
	PostOrder_recursion(root);

	printf("\n树的深度 = %d", Count_TreeDepth(root));
	printf("\n所有结点数 = %d", Count_TreeSize(root));
	printf("\n叶结点数 = %d", Count_LeafNode(root));

	int level;
	printf("\n输入层数：");
	scanf("%d", &level);
	printf("第%d层结点数 = %d", level, Count_TreeLevelSize(root, level));

	return 0;
}