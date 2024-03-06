#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


/* 顺序二叉树 */
typedef char TreeType;
typedef struct seqTree{
	int MAXNUM;		// 最大元素个数
	int curNum;		// 元素的个数
	TreeType nodelist[];	// 顺序二叉树节点存储
} *SeqTree;

/* 链式栈 */
typedef char StackType;
typedef struct StackNode {
	StackType data;
	struct StackNode* next;
}StackNode;

typedef struct {
	StackNode* top;
}LinkStack;

void InitStack(LinkStack* S);//初始化栈
int IsStackEmpty(LinkStack S);//判断栈是否为空
int PushStack(LinkStack* L, StackType data);//入栈
int PopStack(LinkStack* L, StackType* data);//出栈
int GetStackTop(LinkStack* L, StackType* x);//取栈顶元素
int DestroyStack(LinkStack* L);//销毁栈

SeqTree CreateSeqTree(TreeType node[]); // 创建二叉树
int FindTreeNode(SeqTree T, char ch); // 查找指定结点的下标
char GetRoot(SeqTree T); // 求根结点的值
int GetParentIndex(SeqTree T, char ch);		// 求指定结点的双亲结点的下标
int GetLeftChildIndex(SeqTree T, char ch);	// 求指定结点的左孩子的下标
int GetRightChildIndex(SeqTree T, char ch); // 求指定结点的右孩子的下标
void LevelOrder(SeqTree T); // 层序遍历二叉树
void PreOrder(SeqTree T); // 先序遍历二叉树

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

/*------------- 树基本操作 ---------------*/
// 创建二叉树
SeqTree CreateSeqTree(TreeType node[]) {
	SeqTree T = (SeqTree)malloc(sizeof(struct seqTree));
	for (T->curNum = 0; T->curNum < strlen(node); T->curNum++)
		T->nodelist[T->curNum] = node[T->curNum];
	return T;
}
// 查找指定结点的下标
int FindTreeNode(SeqTree T, char ch) {
	for (int i = 0; i < T->curNum; i++)
		if (T->nodelist[i] == ch)
			return i;
	return -1;
}
// 求根结点的值
char GetRoot(SeqTree T){
	// 若二叉树为空，则返回#
	if (T->curNum == 0) return '#';
	return(T->nodelist[0]);
}
// 求指定结点的双亲结点的下标
int GetParentIndex(SeqTree T, char ch){
	int i, p;
	// 返回双亲结点的下标
	for (i = 0; i < T->curNum; i++) {
		if (T->nodelist[i] == ch) p = i;
	}
	// 若双亲不存在，则返回-1
	if (p <= 0 || p >= T->curNum || T->nodelist[(p - 1) / 2] == 32) return -1;
	return (p - 1) / 2;
}
// 求指定结点的左孩子的下标
int GetLeftChildIndex(SeqTree T, char ch){
	int i, p;
	for (i = 0; i < T->curNum; i++) {
		if (T->nodelist[i] == ch) p = i;
	}
	// 若左孩子不存在，则返回-1
	if (p < 0 || p >= T->curNum || T->nodelist[2 * p + 1] == 32)
		return -1;
	return 2 * p + 1;
}
// 求指定结点的右孩子的下标
int GetRightChildIndex(SeqTree T, char ch){
	int i, p;
	for (i = 0; i < T->curNum; i++) {
		if (T->nodelist[i] == ch) p = i;
	}
	// 若左孩子不存在，则返回-1
	if (p < 0 || p >= T->curNum || T->nodelist[2 * (p + 1)] == 32) 
		return -1;
	return 2 * (p + 1);
}

// 层序遍历二叉树
void LevelOrder(SeqTree T){
	for (int i = 0; i < T->curNum; i++) {
		if (T->nodelist[i] == '#');
		else printf("%c ", T->nodelist[i]);
	}
}
// 先序遍历二叉树
void PreOrder(SeqTree T){
	char c;
	LinkStack s;
	InitStack(&s);
	PushStack(&s, T->nodelist[0]);

	while (!IsStackEmpty(s)) {
		GetStackTop(&s, &c);
		PopStack(&s, &c);
		if (FindTreeNode(T, c) != -1) {
			if (c == '#');
			else printf("%c ", c);
			PushStack(&s, T->nodelist[GetRightChildIndex(T, c)]);
			PushStack(&s, T->nodelist[GetLeftChildIndex(T, c)]);
		}
	}
}


int main(void) {
	TreeType node[15] = { 'A','B','C','D','E','F','G','#','#','#','H'};
	SeqTree T = CreateSeqTree(node);

	printf("根结点的值: %c", GetRoot(T));
	printf("\n结点B双亲的下标: %d", GetParentIndex(T, 'B'));
	printf("\n结点B左孩子的下标: %d", GetLeftChildIndex(T, 'B'));
	printf("\n结点B右孩子的下标: %d", GetRightChildIndex(T, 'B'));

	printf("\n层序遍历结果:");
	LevelOrder(T);
	printf("\n先序遍历结果:");
	PreOrder(T);
}