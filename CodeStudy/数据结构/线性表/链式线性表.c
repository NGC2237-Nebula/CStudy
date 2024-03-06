#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/* 单链表 */
typedef int ListType;
typedef struct node {
	ListType data;
	struct node* next;
} *Node, * LinkList;


LinkList CreateLinkList(); // 创建只有头结点的空链表
void InsertHead(LinkList L, ListType data); // 表头插入
void InsertTail(LinkList L, ListType data); // 表尾插入
int InsertAssign(LinkList list, int serial, ListType data); // 指定位置serial前插入

int DeleteAssignData(LinkList list, ListType data);	// 删除第一个数值为data的结点
int DeleteAssignSerial(LinkList list, int serial);	// 删除序号为serial的结点

int FindFirstData(LinkList list, ListType data);	// 查找第一个数值为data的结点
int FindAllData(LinkList list, ListType data);		// 查找所有数值为data的结点及序号

void PrintLinkList(LinkList L);		// 打印单链表
void ReverseLinkList(LinkList L);	// 链表逆置
int DestroyLinkList(LinkList L);	// 销毁单链表


// 创建只有头结点的空链表
LinkList CreateLinkList() {
	Node head = (Node)malloc(sizeof(struct node));
	if (head != NULL) {
		head->next = NULL;
		head->data = 0;
	}
	return head;
}
// 判断链表是否为空
int IsLinkListEmpty(LinkList list) {
	return(list->next == NULL);
}
// 表头插入
void InsertHead(LinkList L, ListType data){
	Node Head = (Node)malloc(sizeof(struct node));
	Head->data = data;
	Head->next = L->next;
	L->next = Head;
}
// 表尾插入
void InsertTail(LinkList L, ListType data){
	Node p = L;
	while (p->next != NULL) p = p->next;
	Node Tail = (Node)malloc(sizeof(struct node));
	p->next = Tail;
	Tail->data = data;
	Tail->next = NULL;
}
// 指定位置serial前插入
int InsertAssign(LinkList L, int serial, ListType data) {
	int tra = 1;
	Node pre = L, p = L->next;
	Node add = (Node)malloc(sizeof(struct node));
	// 寻找指定位置的结点
	while (p != NULL && tra < serial) {
		pre = p;
		p = p->next;
		tra++;
	}
	if (p == NULL || serial <= 0) {
		printf("下标非法!\n");
		return 0;
	}
	else {
		add->data = data;
		add->next = pre->next;
		pre->next = add;
		return 1;
	}
}
// 删除第一个数值为data的结点
int DeleteAssignData(LinkList L, ListType data) {
	Node del, pre = L;
	if (L == NULL) {
		printf("链表为空!\n");
		return 0;
	}
	// 找数值为data的前置结点
	while (pre->next != NULL && pre->next->data != data)
		pre = pre->next;

	if (pre->next == NULL) {
		printf("指定数据不存在!\n");
		return 0;
	}
	else {
		del = pre->next;
		pre->next = del->next;
		free(del);
		return 1;
	}
}
// 删除序号为serial的结点
int DeleteAssignSerial(LinkList L, int serial) {
	int tra = 1;
	Node del,p = L;
	// 寻找指定位置的结点
	while (p != NULL && tra < serial) {
		p = p->next;
		tra++;
	}

	if (p == NULL || serial <= 0) {
		printf("下标非法!\n");
		return 0;
	}
	else {
		del = p->next;
		p->next = del->next;
		free(del);
		return 1;
	}
}
// 查找第一个数值为data的结点
int FindFirstData(LinkList L, ListType data) {
	int local = 1;
	Node find = L->next;
	if (L == NULL) {
		printf("链表为空!\n");
		return -1;
	}
	// 寻找数值为data的结点
	while (find != NULL && find->data != data) {
		find = find->next;
		local++;
	}
	if (find == NULL) {
		printf("指定数据不存在!\n");
		return -1;
	}
	else return local;
}
// 查找所有数值为data的结点及序号
int FindAllData(LinkList L, ListType data){
	int local = 1;
	Node find = L->next;

	if (L == NULL) {
		printf("链表为空!\n");
		return -1;
	}
	while (find != NULL)	{
		// 寻找数值为data的结点和序号
		if (find->data == data)	 
			printf("<%d> : %d\n", local, data);		
		// 未找到数据data的结点
		if (find == NULL) {													
			printf("指定数据不存在!\n");
			return -1;
		}
		find = find->next;
		local++;
	}
	return 1;
}
// 打印单链表
void PrintLinkList(LinkList L) {
	Node p = L->next;
	while (p->next != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("%d\n", p->data);
}
// 链表逆置
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
// 销毁单链表
int DestroyLinkList(LinkList L) {
	Node p;
	int num = 0;
	while (L) {
		p = L;
		L = L->next;
		free(p);
		num += 1;
	}
	return num;	// 返回回收结点的个数，含头结点
}

int main() {
	LinkList L = CreateLinkList();
	printf("插入数据: ");
	for (int i = 10; i >= 1; i--) 
		InsertTail(L, i);
	PrintLinkList(L);

	printf("链表逆置: ");
	ReverseLinkList(L);
	PrintLinkList(L);
	
	printf("指定位置前插入: ");
	InsertAssign(L, 2, 66);
	PrintLinkList(L);

	printf("删除指定数据(66): ");
	DeleteAssignData(L,66);
	PrintLinkList(L);

	printf("删除指定位置(1): ");
	DeleteAssignSerial(L, 1);
	PrintLinkList(L);

	int local = FindFirstData(L, 4);
	if(local != -1) printf("查找指定数据(4)下标:%d\n", local);

	printf("查找指定数据(66)的所有下标: \n");
	InsertAssign(L, 2, 66);
	InsertAssign(L, 3, 66);
	FindAllData(L,66);

	DestroyLinkList(L);
}