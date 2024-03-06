#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


/* ��ʽ������ */
typedef char TreeType;
typedef struct BinaryTreeNode {
	TreeType data;
	struct BinaryTreeNode* lchild, * rchild;
}*BiTree, BiTNode;

/* ��ʽջ */
typedef BiTNode* StackType;
typedef struct StackNode {
	StackType data;
	struct StackNode* next;
}StackNode;

typedef struct {
	StackNode* top;
}LinkStack;

/* ��ʽ���� */
typedef BiTNode* QueueType;
typedef struct QueueNode {
	QueueType data;
	struct QueueNode* next;
}QueueNode;

typedef struct {
	QueueNode* front, * rear;
}LinkQueue;


void InitQueue(LinkQueue* Q);//��ʼ������
int IsQueueEmpty(LinkQueue Q);//�ж϶����Ƿ�Ϊ��
void EnQueue(LinkQueue* Q, QueueType data);//���
int DeQueue(LinkQueue* Q, QueueType* x);//����

void InitStack(LinkStack* S);//��ʼ��ջ
int IsStackEmpty(LinkStack S);//�ж�ջ�Ƿ�Ϊ��
int PushStack(LinkStack* L, StackType data);//��ջ
int PopStack(LinkStack* L, StackType* data);//��ջ
int GetStackTop(LinkStack* L, StackType* x);//ȡջ��Ԫ��
int DestroyStack(LinkStack* L);//����ջ

BiTree CreateTree();//���򷽷�����������
int Count_TreeSize(BiTree root);//�������н����
int Count_LeafNode(BiTree root);//����Ҷ�����
int Count_TreeDepth(BiTree root);//�����������
int Count_TreeLevelSize(BiTNode* root, int level);//�����i��ڵ����
void ChangeRightLeft(BiTree root);//������������������
void DestoryTree(BiTree* root);//����������

void Visit(BiTNode* node);//�Խ��T�Ĳ���
void PreOrder_recursion(BiTree root);//����������ݹ飩 
void InOrder_recursion(BiTree root);//����������ݹ飩 
void PostOrder_recursion(BiTree root);//����������ݹ飩 
void InOrder_non_recursion(BiTree root);//����������ǵݹ飩
void PreOrder_non_recursion(BiTree root);//����������ǵݹ飩
void LevelOrder(BiTree root);//��α���


/*------------- ���л������� ---------------*/
//��ʼ������
void InitQueue(LinkQueue* Q) {
	Q->front = Q->rear = (QueueNode*)malloc(sizeof(QueueNode)); // ����ͷ�ڵ�
	Q->front->next = NULL; //��ʼ��Ϊ��
}
//�ж϶����Ƿ�Ϊ��
int IsQueueEmpty(LinkQueue Q) {
	if (Q.front == Q.rear) return 1;
	else return 0;
}
//���
void EnQueue(LinkQueue* Q, QueueType data) {
	QueueNode* news = (QueueNode*)malloc(sizeof(QueueNode));
	news->data = data; // �����½ڵ㣬�������β�� 
	news->next = NULL;
	Q->rear->next = news;
	Q->rear = news;
}
//����
int DeQueue(LinkQueue* Q, QueueType* x) {
	if (Q->front == Q->rear) return 0;
	QueueNode* del = Q->front->next;
	*x = del->data;
	Q->front->next = del->next;
	if (Q->rear == del)
		Q->rear = Q->front; // ��ԭ����ֻ��һ���ڵ㣬ɾ������ 
	free(del);
	return 1;
}


/*------------- ջ�������� ---------------*/
//��ʼ��ջ
void InitStack(LinkStack* S) {
	S->top = (StackNode*)malloc(sizeof(StackNode)); // ����ͷ�ڵ�
	S->top = NULL; //��ʼ��Ϊ��
}
//�ж�ջ�Ƿ�Ϊ��
int IsStackEmpty(LinkStack S) {
	if (S.top == NULL) return 1;
	else return 0;
}
//��ջ
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
//��ջ
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
//ȡջ��Ԫ��
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
//����ջ
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


/*------------- ���Ĳ��� ---------------*/
//���򷽷�����������
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
//�������н����
int Count_TreeSize(BiTree root) {
	if (root == NULL) return 0;
	return Count_TreeSize(root->lchild) + Count_TreeSize(root->rchild) + 1;
}
//����Ҷ�����
int Count_LeafNode(BiTree root) {
	if (root == NULL)	return 0;
	else if (root->lchild == NULL && root->rchild == NULL)	return 1;
	else return Count_LeafNode(root->lchild) + Count_LeafNode(root->rchild);
}
//�����������
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
//�����i��ڵ����
int Count_TreeLevelSize(BiTNode* root, int level) {
	if (root == NULL)  return 0;
	if (level == 1) return 1;
	return Count_TreeLevelSize(root->lchild, level - 1) + Count_TreeLevelSize(root->rchild, level - 1);
}
//������������������
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
//����������
void DestoryTree(BiTree* root) {
	if (*root != NULL) {
		if ((*root)->lchild) //������
			DestoryTree(&(*root)->lchild);
		if ((*root)->rchild) //���Һ���
			DestoryTree(&(*root)->rchild);
		free(*root); 		//�ͷŸ����
		*root = NULL; 		//��ָ��NULL
	}
}

//�Խ��T�Ĳ���
void Visit(BiTNode* node) {
	printf(" %c", node->data);
}
//����������ݹ飩 
void PreOrder_recursion(BiTree root) {
	if (root != NULL) {
		Visit(root);
		PreOrder_recursion(root->lchild);
		PreOrder_recursion(root->rchild);
	}
}
//����������ݹ飩 
void InOrder_recursion(BiTree root) {
	if (root != NULL) {
		InOrder_recursion(root->lchild);
		Visit(root);
		InOrder_recursion(root->rchild);
	}
}
//����������ݹ飩 
void PostOrder_recursion(BiTree root) {
	if (root != NULL) {
		PostOrder_recursion(root->lchild);
		PostOrder_recursion(root->rchild);
		Visit(root);
	}
}
//����������ǵݹ飩
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
//����������ǵݹ飩
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
//�����������ǵݹ飩
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
//��α���
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
	// ������������ ABD##E#H##CF##G## ����������
	printf("�����������д���������:");
	BiTree root = CreateTree();

	printf("\n�������(��  ��):");
	PreOrder_recursion(root);
	printf("\n�������(�ǵݹ�):");
	PreOrder_non_recursion(root);

	printf("\n�������(��  ��):");
	InOrder_recursion(root);
	printf("\n�������(�ǵݹ�):");
	InOrder_non_recursion(root);

	printf("\n�������(��  ��):");
	PostOrder_recursion(root);
	printf("\n�������(�ǵݹ�):");
	postOrder_non_recursion(root);

	printf("\n��α���:");
	LevelOrder(root);

	ChangeRightLeft(root);
	printf("\n������������������������");
	PostOrder_recursion(root);

	printf("\n������� = %d", Count_TreeDepth(root));
	printf("\n���н���� = %d", Count_TreeSize(root));
	printf("\nҶ����� = %d", Count_LeafNode(root));

	int level;
	printf("\n���������");
	scanf("%d", &level);
	printf("��%d������ = %d", level, Count_TreeLevelSize(root, level));

	return 0;
}