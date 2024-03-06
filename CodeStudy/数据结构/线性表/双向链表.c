#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/* 链表结点 */
typedef int ListType;
typedef struct node {
    ListType data; // 存放整型数据
    struct node* llink, * rlink; // 指向前驱和后继结点的指针
} *Node;

/* 双向链表头结点 */
typedef struct headNode {
    struct node* head, * tail; // 指向双向链表的第一个结点和最后一个结点的指针
} *DoublyLinkedList;

DoublyLinkedList CreateDoublyLinkedList();  // 创建不带头结点的双向链表
void InsertHead(DoublyLinkedList L, ListType insData);  // 表头插入数据 
void InsertTail(DoublyLinkedList L, ListType insData);  // 表尾插入数据 
int DeleteData(DoublyLinkedList L, ListType delData);   // 删除数据
void PrintDoublyLinkedList(DoublyLinkedList L);     // 输出双向链表
int DestroyDoublyLinkedList(DoublyLinkedList L);    // 释放双向链表

// 创建不带头结点的双向链表
DoublyLinkedList CreateDoublyLinkedList() {
    DoublyLinkedList L = (DoublyLinkedList)malloc(sizeof(struct headNode));
    L->head = L->tail = NULL;
    return L;
}
// 表头插入数据 
void InsertHead(DoublyLinkedList L, ListType insData) {
    Node add = (Node)malloc(sizeof(struct headNode));
    add->data = insData;
    // 第一次插入
    if (L->head == NULL && L->tail == NULL) {
        add->llink = add->rlink = NULL;
        L->head = L->tail = add;
    }
    else {
        add->llink = NULL;
        add->rlink = L->head;
        L->head->llink = add;
        L->head = add;
    }
}
// 表尾插入数据 
void InsertTail(DoublyLinkedList L, ListType insData) {
    Node add = (Node)malloc(sizeof(struct headNode));
    add->data = insData;
    // 第一次插入，与表头插入处理相同
    if (L->head == NULL && L->tail == NULL) {
        add->llink = add->rlink = NULL;
        L->head = L->tail = add;
    }
    else {
        add->llink = L->tail;
        add->rlink = NULL;
        L->tail->rlink = add;
        L->tail = add;
    }
}
// 删除值为delData的第一个结点
int DeleteData(DoublyLinkedList L, ListType delData) {
    Node del;
    for (del = L->head; del != NULL; del = del->rlink) {
        if (del->data == delData) {
            if (del == L->head) {
                L->head = del->rlink;
                L->head->llink = NULL;
            }
            else if (del == L->tail) {
                L->tail = del->llink;
                L->tail->rlink = NULL;
            }
            else {
                del->llink->rlink = del->rlink;
                del->rlink->llink = del->llink;
            }
            //free(del);
            return 1; // 删除成功返回1，否则返回0
        }
    }
    return 0;
}
// 输出双向链表
void PrintDoublyLinkedList(DoublyLinkedList L) {
    for (Node p = L->head; p != NULL; p = p->rlink)
        printf("%d ", p->data);
    printf("\n");
}
// 释放双向链表
int DestroyDoublyLinkedList(DoublyLinkedList L) {
    int num = 0;
    Node p, temp;
    temp = p = (Node)malloc(sizeof(struct node));
    for (p = L->head; p->rlink != NULL; p = p->rlink) {
        temp = p;
        //free(temp);
        num++;
    }
    return num; // 返回释放的结点数
}

int main() {
    DoublyLinkedList L = CreateDoublyLinkedList();

    for (int i = 1; i <= 5; i++)
        InsertHead(L, i);
    printf("表头插入后: ");
    PrintDoublyLinkedList(L);

    for (int i = 1; i <= 5; i++)
        InsertTail(L, i);
    printf("表尾插入后: ");
    PrintDoublyLinkedList(L);

    DeleteData(L, 5);
    printf("删除元素5后: ");
    PrintDoublyLinkedList(L);

    DestroyDoublyLinkedList(L);
    return 1;
}