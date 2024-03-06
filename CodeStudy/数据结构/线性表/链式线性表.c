#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/* ������ */
typedef int ListType;
typedef struct node {
	ListType data;
	struct node* next;
} *Node, * LinkList;


LinkList CreateLinkList(); // ����ֻ��ͷ���Ŀ�����
void InsertHead(LinkList L, ListType data); // ��ͷ����
void InsertTail(LinkList L, ListType data); // ��β����
int InsertAssign(LinkList list, int serial, ListType data); // ָ��λ��serialǰ����

int DeleteAssignData(LinkList list, ListType data);	// ɾ����һ����ֵΪdata�Ľ��
int DeleteAssignSerial(LinkList list, int serial);	// ɾ�����Ϊserial�Ľ��

int FindFirstData(LinkList list, ListType data);	// ���ҵ�һ����ֵΪdata�Ľ��
int FindAllData(LinkList list, ListType data);		// ����������ֵΪdata�Ľ�㼰���

void PrintLinkList(LinkList L);		// ��ӡ������
void ReverseLinkList(LinkList L);	// ��������
int DestroyLinkList(LinkList L);	// ���ٵ�����


// ����ֻ��ͷ���Ŀ�����
LinkList CreateLinkList() {
	Node head = (Node)malloc(sizeof(struct node));
	if (head != NULL) {
		head->next = NULL;
		head->data = 0;
	}
	return head;
}
// �ж������Ƿ�Ϊ��
int IsLinkListEmpty(LinkList list) {
	return(list->next == NULL);
}
// ��ͷ����
void InsertHead(LinkList L, ListType data){
	Node Head = (Node)malloc(sizeof(struct node));
	Head->data = data;
	Head->next = L->next;
	L->next = Head;
}
// ��β����
void InsertTail(LinkList L, ListType data){
	Node p = L;
	while (p->next != NULL) p = p->next;
	Node Tail = (Node)malloc(sizeof(struct node));
	p->next = Tail;
	Tail->data = data;
	Tail->next = NULL;
}
// ָ��λ��serialǰ����
int InsertAssign(LinkList L, int serial, ListType data) {
	int tra = 1;
	Node pre = L, p = L->next;
	Node add = (Node)malloc(sizeof(struct node));
	// Ѱ��ָ��λ�õĽ��
	while (p != NULL && tra < serial) {
		pre = p;
		p = p->next;
		tra++;
	}
	if (p == NULL || serial <= 0) {
		printf("�±�Ƿ�!\n");
		return 0;
	}
	else {
		add->data = data;
		add->next = pre->next;
		pre->next = add;
		return 1;
	}
}
// ɾ����һ����ֵΪdata�Ľ��
int DeleteAssignData(LinkList L, ListType data) {
	Node del, pre = L;
	if (L == NULL) {
		printf("����Ϊ��!\n");
		return 0;
	}
	// ����ֵΪdata��ǰ�ý��
	while (pre->next != NULL && pre->next->data != data)
		pre = pre->next;

	if (pre->next == NULL) {
		printf("ָ�����ݲ�����!\n");
		return 0;
	}
	else {
		del = pre->next;
		pre->next = del->next;
		free(del);
		return 1;
	}
}
// ɾ�����Ϊserial�Ľ��
int DeleteAssignSerial(LinkList L, int serial) {
	int tra = 1;
	Node del,p = L;
	// Ѱ��ָ��λ�õĽ��
	while (p != NULL && tra < serial) {
		p = p->next;
		tra++;
	}

	if (p == NULL || serial <= 0) {
		printf("�±�Ƿ�!\n");
		return 0;
	}
	else {
		del = p->next;
		p->next = del->next;
		free(del);
		return 1;
	}
}
// ���ҵ�һ����ֵΪdata�Ľ��
int FindFirstData(LinkList L, ListType data) {
	int local = 1;
	Node find = L->next;
	if (L == NULL) {
		printf("����Ϊ��!\n");
		return -1;
	}
	// Ѱ����ֵΪdata�Ľ��
	while (find != NULL && find->data != data) {
		find = find->next;
		local++;
	}
	if (find == NULL) {
		printf("ָ�����ݲ�����!\n");
		return -1;
	}
	else return local;
}
// ����������ֵΪdata�Ľ�㼰���
int FindAllData(LinkList L, ListType data){
	int local = 1;
	Node find = L->next;

	if (L == NULL) {
		printf("����Ϊ��!\n");
		return -1;
	}
	while (find != NULL)	{
		// Ѱ����ֵΪdata�Ľ������
		if (find->data == data)	 
			printf("<%d> : %d\n", local, data);		
		// δ�ҵ�����data�Ľ��
		if (find == NULL) {													
			printf("ָ�����ݲ�����!\n");
			return -1;
		}
		find = find->next;
		local++;
	}
	return 1;
}
// ��ӡ������
void PrintLinkList(LinkList L) {
	Node p = L->next;
	while (p->next != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("%d\n", p->data);
}
// ��������
void ReverseLinkList(LinkList L) {
	Node q, p = L->next;
	L->next = NULL;
	while (p) {
		q = p;
		p = p->next;
		q->next = L->next;
		L->next = q;
	}
}
// ���ٵ�����
int DestroyLinkList(LinkList L) {
	Node p;
	int num = 0;
	while (L) {
		p = L;
		L = L->next;
		free(p);
		num += 1;
	}
	return num;	// ���ػ��ս��ĸ�������ͷ���
}

int main() {
	LinkList L = CreateLinkList();
	printf("��������: ");
	for (int i = 10; i >= 1; i--) 
		InsertTail(L, i);
	PrintLinkList(L);

	printf("��������: ");
	ReverseLinkList(L);
	PrintLinkList(L);
	
	printf("ָ��λ��ǰ����: ");
	InsertAssign(L, 2, 66);
	PrintLinkList(L);

	printf("ɾ��ָ������(66): ");
	DeleteAssignData(L,66);
	PrintLinkList(L);

	printf("ɾ��ָ��λ��(1): ");
	DeleteAssignSerial(L, 1);
	PrintLinkList(L);

	int local = FindFirstData(L, 4);
	if(local != -1) printf("����ָ������(4)�±�:%d\n", local);

	printf("����ָ������(66)�������±�: \n");
	InsertAssign(L, 2, 66);
	InsertAssign(L, 3, 66);
	FindAllData(L,66);

	DestroyLinkList(L);
}