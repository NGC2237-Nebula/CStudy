#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


/* ˳������� */
typedef char TreeType;
typedef struct seqTree{
	int MAXNUM;		// ���Ԫ�ظ���
	int curNum;		// Ԫ�صĸ���
	TreeType nodelist[];	// ˳��������ڵ�洢
} *SeqTree;

/* ��ʽջ */
typedef char StackType;
typedef struct StackNode {
	StackType data;
	struct StackNode* next;
}StackNode;

typedef struct {
	StackNode* top;
}LinkStack;

void InitStack(LinkStack* S);//��ʼ��ջ
int IsStackEmpty(LinkStack S);//�ж�ջ�Ƿ�Ϊ��
int PushStack(LinkStack* L, StackType data);//��ջ
int PopStack(LinkStack* L, StackType* data);//��ջ
int GetStackTop(LinkStack* L, StackType* x);//ȡջ��Ԫ��
int DestroyStack(LinkStack* L);//����ջ

SeqTree CreateSeqTree(TreeType node[]); // ����������
int FindTreeNode(SeqTree T, char ch); // ����ָ�������±�
char GetRoot(SeqTree T); // �������ֵ
int GetParentIndex(SeqTree T, char ch);		// ��ָ������˫�׽����±�
int GetLeftChildIndex(SeqTree T, char ch);	// ��ָ���������ӵ��±�
int GetRightChildIndex(SeqTree T, char ch); // ��ָ�������Һ��ӵ��±�
void LevelOrder(SeqTree T); // �������������
void PreOrder(SeqTree T); // �������������

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

/*------------- ���������� ---------------*/
// ����������
SeqTree CreateSeqTree(TreeType node[]) {
	SeqTree T = (SeqTree)malloc(sizeof(struct seqTree));
	for (T->curNum = 0; T->curNum < strlen(node); T->curNum++)
		T->nodelist[T->curNum] = node[T->curNum];
	return T;
}
// ����ָ�������±�
int FindTreeNode(SeqTree T, char ch) {
	for (int i = 0; i < T->curNum; i++)
		if (T->nodelist[i] == ch)
			return i;
	return -1;
}
// �������ֵ
char GetRoot(SeqTree T){
	// ��������Ϊ�գ��򷵻�#
	if (T->curNum == 0) return '#';
	return(T->nodelist[0]);
}
// ��ָ������˫�׽����±�
int GetParentIndex(SeqTree T, char ch){
	int i, p;
	// ����˫�׽����±�
	for (i = 0; i < T->curNum; i++) {
		if (T->nodelist[i] == ch) p = i;
	}
	// ��˫�ײ����ڣ��򷵻�-1
	if (p <= 0 || p >= T->curNum || T->nodelist[(p - 1) / 2] == 32) return -1;
	return (p - 1) / 2;
}
// ��ָ���������ӵ��±�
int GetLeftChildIndex(SeqTree T, char ch){
	int i, p;
	for (i = 0; i < T->curNum; i++) {
		if (T->nodelist[i] == ch) p = i;
	}
	// �����Ӳ����ڣ��򷵻�-1
	if (p < 0 || p >= T->curNum || T->nodelist[2 * p + 1] == 32)
		return -1;
	return 2 * p + 1;
}
// ��ָ�������Һ��ӵ��±�
int GetRightChildIndex(SeqTree T, char ch){
	int i, p;
	for (i = 0; i < T->curNum; i++) {
		if (T->nodelist[i] == ch) p = i;
	}
	// �����Ӳ����ڣ��򷵻�-1
	if (p < 0 || p >= T->curNum || T->nodelist[2 * (p + 1)] == 32) 
		return -1;
	return 2 * (p + 1);
}

// �������������
void LevelOrder(SeqTree T){
	for (int i = 0; i < T->curNum; i++) {
		if (T->nodelist[i] == '#');
		else printf("%c ", T->nodelist[i]);
	}
}
// �������������
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

	printf("������ֵ: %c", GetRoot(T));
	printf("\n���B˫�׵��±�: %d", GetParentIndex(T, 'B'));
	printf("\n���B���ӵ��±�: %d", GetLeftChildIndex(T, 'B'));
	printf("\n���B�Һ��ӵ��±�: %d", GetRightChildIndex(T, 'B'));

	printf("\n����������:");
	LevelOrder(T);
	printf("\n����������:");
	PreOrder(T);
}