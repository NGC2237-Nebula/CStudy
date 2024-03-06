#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/* ���������� */
typedef char ThreadType;
typedef struct ThreadNode {
	ThreadType data;
	struct ThreadNode* lchild, * rchild;
	int ltag, rtag; //����������־
}ThreadNode, *ThreadTree;


ThreadTree createTree(); //���򷽷�����������
void threaded(ThreadNode* q); //�Ե�ǰ����������������
void createInThreadTree(ThreadTree T); //����������������T
void inThread(ThreadTree T); //����������������߱�����������
void preThread(ThreadTree T); //����������������߱�����������
void postThread(ThreadTree T); //����������������߱�����������

void visit(ThreadNode* node); //�Խ��T�Ĳ���
ThreadNode* firstNode(ThreadNode* p); // �ҵ���PΪ���ڵ�������У�����������ȱ������Ľڵ�
ThreadNode* lastNode(ThreadNode* p); // �ҵ���PΪ���ڵ�������У����������󱻱����Ľڵ�
ThreadNode* nextNode(ThreadNode* p); // �������������������ҵ�P�ĺ�̽ڵ�
ThreadNode* preNode(ThreadNode* p); // �������������������ҵ�P��ǰ���ڵ�
void inOrder_thread(ThreadNode* T); // �����������������������ʵ�ֵķǵݹ��㷨���ռ临�Ӷ�O��1����
void revInOrder_thread(ThreadNode* T); // �����������������

//ָ��ǰ���ʽڵ��ǰ��
ThreadNode* pre = NULL;

/*-------- ������������ --------*/
//���򷽷�����������
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
//�Ե�ǰ����������������
void threaded(ThreadNode* p) {
	// ��ָ��Ϊ�գ�����ǰ������
	if (p->lchild == NULL) {
		p->lchild = pre;
		p->ltag = 1;
	}
	// ����ǰ���ڵ�ĺ������
	if (pre != NULL && pre->rchild == NULL) {
		pre->rchild = p;
		pre->rtag = 1;
	}
	// ָ�����
	pre = p;
}
//����������������T
void createInThreadTree(ThreadTree T) {
	pre = NULL;
	if (T != NULL) {
		inThread(T);
		if (pre->rchild == NULL)
			pre->rtag = 1;
	}
}
//����������������߱�����������
void inThread(ThreadTree T) {
	if (T != NULL) {
		inThread(T->lchild);
		threaded(T);
		inThread(T->rchild);
	}
}
//����������������߱�����������
void preThread(ThreadTree T) {
	if (T != NULL) {
		threaded(T);
		// lchild����ǰ������ʱ�ŷ���������
		// ���Ӹ����������ܻ��������ָ������ѭ����ת
		if(T->ltag==0) 
			preThread(T->lchild);
		preThread(T->rchild);
	}
}
//����������������߱�����������
void postThread(ThreadTree T) {
	if (T != NULL) {
		// �������������������
		// ��Ϊ���� visit(T) ��ʱ�������ӡ��Һ����Ѿ������꣬�����ٷ�����
		postThread(T->lchild);
		postThread(T->rchild);
		threaded(T);
	}
}

/*-------- �������������� --------*/
//�Խ��T�Ĳ���
void visit(ThreadNode* node) {
	printf("%c ", node->data);
}
// �ҵ���PΪ���ڵ�������У�����������ȱ������Ľڵ�
ThreadNode* firstNode(ThreadNode* p) {
	//ѭ���ҵ���������������½ǵĽڵ㣨��һ����Ҷ�ӽڵ㣩
	while (p->ltag == 0) p = p->lchild;
	return p;
}
// �ҵ���PΪ���ڵ�������У����������󱻱����Ľڵ�
ThreadNode* lastNode(ThreadNode* p) {
	//ѭ���ҵ���������������½ǵĽڵ㣨��һ����Ҷ�ӽڵ㣩
	while (p->rtag == 0) p = p->rchild;
	return p;
}
// �������������������ҵ�P�ĺ�̽ڵ�
ThreadNode* nextNode(ThreadNode* p) {
	// p->rtag = 0(ָʾP�ڵ������),���������������½ڵ�
	if (p->rtag == 0) return firstNode(p->rchild);
	// p->rtag = 1(ָʾ����),ֱ�ӷ��غ������
	else return p->rchild;
}
// �������������������ҵ�P��ǰ���ڵ�
ThreadNode* preNode(ThreadNode* p) {
	// p->rtag = 0(ָʾP�ڵ���Һ���),���������������½ڵ�
	if (p->ltag == 0) return lastNode(p->lchild);
	// p->rtag = 1(ָʾ����),ֱ�ӷ���ǰ������
	else return p->lchild;
}
// �����������������������ʵ�ֵķǵݹ��㷨���ռ临�Ӷ�O��1����
void inOrder_thread(ThreadNode* T) {
	for (ThreadNode* p = firstNode(T); p != NULL; p = nextNode(p)) {
		visit(p);
	}
}
// �����������������
void revInOrder_thread(ThreadNode* T) {
	for (ThreadNode* p = lastNode(T); p != NULL; p = preNode(p)) {
		visit(p);
	}
}


int main() {
	// ������������ ABD##E#H##CF##G## ����������
	printf("�����������д���������:");
	ThreadTree root = createTree();
	createInThreadTree(root);

	printf("\n�������:");
	inOrder_thread(root);
	printf("\n�����������:");
	revInOrder_thread(root);
}