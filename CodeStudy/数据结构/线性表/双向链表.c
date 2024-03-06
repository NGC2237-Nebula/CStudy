#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/* ������ */
typedef int ListType;
typedef struct node {
    ListType data; // �����������
    struct node* llink, * rlink; // ָ��ǰ���ͺ�̽���ָ��
} *Node;

/* ˫������ͷ��� */
typedef struct headNode {
    struct node* head, * tail; // ָ��˫������ĵ�һ���������һ������ָ��
} *DoublyLinkedList;

DoublyLinkedList CreateDoublyLinkedList();  // ��������ͷ����˫������
void InsertHead(DoublyLinkedList L, ListType insData);  // ��ͷ�������� 
void InsertTail(DoublyLinkedList L, ListType insData);  // ��β�������� 
int DeleteData(DoublyLinkedList L, ListType delData);   // ɾ������
void PrintDoublyLinkedList(DoublyLinkedList L);     // ���˫������
int DestroyDoublyLinkedList(DoublyLinkedList L);    // �ͷ�˫������

// ��������ͷ����˫������
DoublyLinkedList CreateDoublyLinkedList() {
    DoublyLinkedList L = (DoublyLinkedList)malloc(sizeof(struct headNode));
    L->head = L->tail = NULL;
    return L;
}
// ��ͷ�������� 
void InsertHead(DoublyLinkedList L, ListType insData) {
    Node add = (Node)malloc(sizeof(struct headNode));
    add->data = insData;
    // ��һ�β���
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
// ��β�������� 
void InsertTail(DoublyLinkedList L, ListType insData) {
    Node add = (Node)malloc(sizeof(struct headNode));
    add->data = insData;
    // ��һ�β��룬���ͷ���봦����ͬ
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
// ɾ��ֵΪdelData�ĵ�һ�����
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
            return 1; // ɾ���ɹ�����1�����򷵻�0
        }
    }
    return 0;
}
// ���˫������
void PrintDoublyLinkedList(DoublyLinkedList L) {
    for (Node p = L->head; p != NULL; p = p->rlink)
        printf("%d ", p->data);
    printf("\n");
}
// �ͷ�˫������
int DestroyDoublyLinkedList(DoublyLinkedList L) {
    int num = 0;
    Node p, temp;
    temp = p = (Node)malloc(sizeof(struct node));
    for (p = L->head; p->rlink != NULL; p = p->rlink) {
        temp = p;
        //free(temp);
        num++;
    }
    return num; // �����ͷŵĽ����
}

int main() {
    DoublyLinkedList L = CreateDoublyLinkedList();

    for (int i = 1; i <= 5; i++)
        InsertHead(L, i);
    printf("��ͷ�����: ");
    PrintDoublyLinkedList(L);

    for (int i = 1; i <= 5; i++)
        InsertTail(L, i);
    printf("��β�����: ");
    PrintDoublyLinkedList(L);

    DeleteData(L, 5);
    printf("ɾ��Ԫ��5��: ");
    PrintDoublyLinkedList(L);

    DestroyDoublyLinkedList(L);
    return 1;
}