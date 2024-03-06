#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/* 顺序队列 */
typedef int QueueType;
typedef struct seqQueue {
    int MAXNUM;             // 队列中能存放的最大元素个数
    int front, rear;        // 队列的队首，队尾
    QueueType element[100]; // 存放连续空间的起始地址
} *SeqQueue;

SeqQueue CreateSqlQueue(int maxNum); //创建空的顺序队列
int IsQueueEmpty(SeqQueue Q);   //判断顺序（环形）队列是否为空
int IsQueueFull(SeqQueue Q);    //判断顺序（环形）队列是否已满
int EnQueue(SeqQueue Q, QueueType x);   //入队
QueueType DeQueue(SeqQueue Q);          //出队
QueueType GetQueueFront(SeqQueue Q);    //取队首元素返回
int DestroyQueue(SeqQueue Q);   //销毁队列

// 创建空的顺序队列
SeqQueue CreateSqlQueue(int maxNum) {
    SeqQueue queue = (SeqQueue)malloc(sizeof(struct seqQueue));
    if (!maxNum)  return NULL;
    else {
        queue->MAXNUM = maxNum;
        queue->front = queue->rear = NULL;
        return queue;
    }
}
// 判断顺序（环形）队列是否为空
int IsQueueEmpty(SeqQueue Q) {
    // 若为空，返回值为1，否则返回值为0
    // 若队列不存在，则返回-1
    if (Q == NULL) return -1;
    else  return(Q->front == Q->rear);
}
// 判断顺序（环形）队列是否已满
int IsQueueFull(SeqQueue Q) {
    // 若已满，返回值为1，否则返回值为0
    return((Q->rear + 1) % Q->MAXNUM == Q->front);
}
// 入队
int EnQueue(SeqQueue Q, QueueType x) {
    // 若插入不成功，返回0；插入成功返回值为1
    if ((Q->rear + 1) % Q->MAXNUM == Q->front) return 0;
    else {
        Q->element[Q->rear] = x;
        Q->rear = (Q->rear + 1) % Q->MAXNUM;
        return 1;
    }
}
// 出队并返回删除元素
QueueType DeQueue(SeqQueue Q) {
    // 若队列为空，则返回-1
    if (Q->front == Q->rear) return -1;
    else {
        int del = Q->element[Q->front];
        Q->front = (Q->front + 1) % Q->MAXNUM;
        return del;
    }
}
// 取队首元素返回
QueueType GetQueueFront(SeqQueue Q){
    // 若队列为空，则返回-1
    if (Q->front == Q->rear) return -1;
    else  return(Q->element[Q->front]);
}
// 销毁队列，释放队列所占存储空间
int DestroyQueue(SeqQueue Q){
    // 返回销毁栈中现有数据元素的个数
    // 若待销毁的线性表不存在，则返回0
    if (Q->front == Q->rear) return 0;
}

/*  设某银行有A、B两个业务窗口，A窗口处理业务的速度是B窗口的2倍，即A处理完2个业务，B才处理完一个。
给定银行的顾客序列，请按业务完成顺序输出顾客序列。假定不考虑顾客到达的时间间隔，并且当A、B两个窗口同
时处理完顾客时，A窗口的顾客先离开。
    输入一行整数，第一个数字是顾客的总数N（N<1000）,后面跟N个整数代表顾客的编号，假定编号为奇数的顾
客去A窗口处理业务，而编号为偶数的顾客去B窗口处理业务。 */

/*
测试输入：8  2  1  3  9   4  11  13  15
预期输出：1  3  2  9  11  4  13  15
*/

void QueueDemo(int a[], int n) {
    SeqQueue A = CreateSqlQueue(n * 2);	//编号为奇数的顾客去A窗口 
    SeqQueue B = CreateSqlQueue(n * 2);	//编号为偶数的顾客去B窗口

    for (int i = 0; i < n; i++) {
        if (a[i] % 2)	EnQueue(A, a[i]);
        else EnQueue(B, a[i]);
    }
    printf("结果如下:");
    while (1) {
        for (int i = 0; i < 2; i++) {
            if (!IsQueueEmpty(A)) {
                printf("%d ", GetQueueFront(A));
                DeQueue(A);
            }
            else break;
        }
        if (!IsQueueEmpty(B)) {
            printf("%d ", GetQueueFront(B));
            DeQueue(B);
        }
        else break;
    }
}

int main() {
    SeqQueue Q = CreateSqlQueue(10);
    if (IsQueueEmpty(Q)) printf("当前队列为空");
    for (int i = 0; i < 10; i++) {
        EnQueue(Q, i);
    }
    printf("\nDeQueue方法: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", DeQueue(Q));
    }
    printf("\nGetQueueFront方法: %d ", GetQueueFront(Q));
    DestroyQueue(Q);

    printf("\n\n队列案例：\n");
    int a[] = {2,1,3,9,4,11,13,15};
    QueueDemo(a, 8);
}

