#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/* ˳��ջ */
typedef int StackType;
typedef struct seqStack{
    int MAXNUM;     // ���Ԫ�ظ���    
    int top;        // ջ��λ�ã���ʼ��Ϊ0��-1
    StackType element[100]; // Ԫ�ص������ռ����ʼ��ַ  
} *SeqStack;

SeqStack CreateSqlStack(int m); //������˳��ջ
int IsStackEmpty(SeqStack L);   //�ж�ջ�Ƿ�Ϊ��
int IsStackFull(SeqStack L);    //�ж�ջ�Ƿ�����
int PushStack(SeqStack L, StackType x); //��ջ
StackType PopStack(SeqStack L);         //��ջ
StackType GetStackTop(SeqStack L);      //ȡջ��Ԫ��
int DestroyStack(SeqStack L);   //����ջ

// ������˳��ջ
SeqStack CreateSqlStack(int m) {
    if (m == 0) return NULL;
    else {
        struct seqStack* stack = (struct seqStack*)malloc(sizeof(struct seqStack));
        stack->MAXNUM = m;
        stack->top = 0;
        return stack;
    }
}
// �ж�ջ�Ƿ�Ϊ��
int IsStackEmpty(SeqStack L) {
    // ��ջ�����ڣ��򷵻�-1
    if (L == NULL) return -1;
    // ��Ϊ�գ�����ֵΪ1�����򷵻�ֵΪ0
    else if (L->top == 0) return 1;
    else return 0;
}
// �ж�ջ�Ƿ�����
int IsStackFull(SeqStack L){
    //������������ֵΪ1�����򷵻�ֵΪ0
    if (L->top == L->MAXNUM) return 1;
    else return 0;
}
// ��ջ
int PushStack(SeqStack L, StackType x) {
    // �����벻�ɹ�������0������ɹ�����ֵΪ1
    if (IsStackFull(L))  return 0;
    else {
        L->element[L->top] = x;
        L->top = L->top + 1;
        return 1;
    }
}
//��ջ
StackType PopStack(SeqStack L) {
    // ��ջΪ�գ��򷵻�-1
    if (IsStackEmpty(L))  return -1;
    else {
        int del = L->element[L->top - 1];
        L->top--;
        return del;
    }
}
//ȡջ��Ԫ��
StackType GetStackTop(SeqStack L) {
    // ��ջΪ�գ��򷵻�-1
    if (IsStackEmpty(L))  return -1;
    else return L->element[L->top - 1];
}
//����ջ
int DestroyStack(SeqStack L){
    // ��������ջ��Ԫ�ظ�������������ջ�����ڷ���-1
    if (L == NULL) return -1;
    else {
        int num = L->top;
        L->top = 0;
        return num;
    }
}


// ����ջ��dataת��Ϊk���ƣ�k������2��8��16
void ConvertData(int data, int k){
    SeqStack L = CreateSqlStack(50);
    int temp = 0;
    while (data != 0) {
        temp = data % k;
        data = data / k;
        PushStack(L, temp);
    }
    while (!IsStackEmpty(L)) {
        temp = GetStackTop(L);
        PopStack(L);
        if (temp == 10) printf("A");
        else if (temp == 11) printf("B");
        else if (temp == 12) printf("C");
        else if (temp == 13) printf("D");
        else if (temp == 14) printf("E");
        else if (temp == 15) printf("F");
        else printf("%d", temp);
    }
}

int main() {
    ConvertData(33324, 16);
}
