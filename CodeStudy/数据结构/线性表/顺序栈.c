#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/* 顺序栈 */
typedef int StackType;
typedef struct seqStack{
    int MAXNUM;     // 最大元素个数    
    int top;        // 栈顶位置，初始化为0或-1
    StackType element[100]; // 元素的连续空间的起始地址  
} *SeqStack;

SeqStack CreateSqlStack(int m); //创建空顺序栈
int IsStackEmpty(SeqStack L);   //判断栈是否为空
int IsStackFull(SeqStack L);    //判断栈是否已满
int PushStack(SeqStack L, StackType x); //入栈
StackType PopStack(SeqStack L);         //出栈
StackType GetStackTop(SeqStack L);      //取栈顶元素
int DestroyStack(SeqStack L);   //销毁栈

// 创建空顺序栈
SeqStack CreateSqlStack(int m) {
    if (m == 0) return NULL;
    else {
        struct seqStack* stack = (struct seqStack*)malloc(sizeof(struct seqStack));
        stack->MAXNUM = m;
        stack->top = 0;
        return stack;
    }
}
// 判断栈是否为空
int IsStackEmpty(SeqStack L) {
    // 若栈不存在，则返回-1
    if (L == NULL) return -1;
    // 若为空，返回值为1，否则返回值为0
    else if (L->top == 0) return 1;
    else return 0;
}
// 判断栈是否已满
int IsStackFull(SeqStack L){
    //若已满，返回值为1，否则返回值为0
    if (L->top == L->MAXNUM) return 1;
    else return 0;
}
// 入栈
int PushStack(SeqStack L, StackType x) {
    // 若插入不成功，返回0；插入成功返回值为1
    if (IsStackFull(L))  return 0;
    else {
        L->element[L->top] = x;
        L->top = L->top + 1;
        return 1;
    }
}
//出栈
StackType PopStack(SeqStack L) {
    // 若栈为空，则返回-1
    if (IsStackEmpty(L))  return -1;
    else {
        int del = L->element[L->top - 1];
        L->top--;
        return del;
    }
}
//取栈顶元素
StackType GetStackTop(SeqStack L) {
    // 若栈为空，则返回-1
    if (IsStackEmpty(L))  return -1;
    else return L->element[L->top - 1];
}
//销毁栈
int DestroyStack(SeqStack L){
    // 返回销毁栈中元素个数，若待销毁栈不存在返回-1
    if (L == NULL) return -1;
    else {
        int num = L->top;
        L->top = 0;
        return num;
    }
}


// 利用栈将data转换为k进制，k可能是2，8，16
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
