#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

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
int PushStack(LinkStack *L, StackType data) {
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
int DestroyStack(LinkStack* L){
    int cnt = 0;
    if (L == NULL)	return 0;
    struct StackNode* p = L->top, * q;
    free(L);
    while (p->next != NULL){
        q = p->next;
        cnt++;
        free(p);
        p = q;
    }
    return cnt;
}


int main(void) {
    LinkStack S;
    InitStack(&S);
    
    PushStack(&S, 'a');

    if (IsStackEmpty(S) == 1) {
        printf("stack is null\n");
    }
    else {
        printf("stack is not null\n");
    }

    char a;
    if (PopStack(&S, &a) == -1) {
        printf("the stack is null,pop fails"); 
    }
    else {
        printf("%c", a);
    }
}