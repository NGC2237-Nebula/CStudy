#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/* ˳����� */
typedef int QueueType;
typedef struct seqQueue {
    int MAXNUM;             // �������ܴ�ŵ����Ԫ�ظ���
    int front, rear;        // ���еĶ��ף���β
    QueueType element[100]; // ��������ռ����ʼ��ַ
} *SeqQueue;

SeqQueue CreateSqlQueue(int maxNum); //�����յ�˳�����
int IsQueueEmpty(SeqQueue Q);   //�ж�˳�򣨻��Σ������Ƿ�Ϊ��
int IsQueueFull(SeqQueue Q);    //�ж�˳�򣨻��Σ������Ƿ�����
int EnQueue(SeqQueue Q, QueueType x);   //���
QueueType DeQueue(SeqQueue Q);          //����
QueueType GetQueueFront(SeqQueue Q);    //ȡ����Ԫ�ط���
int DestroyQueue(SeqQueue Q);   //���ٶ���

// �����յ�˳�����
SeqQueue CreateSqlQueue(int maxNum) {
    SeqQueue queue = (SeqQueue)malloc(sizeof(struct seqQueue));
    if (!maxNum)  return NULL;
    else {
        queue->MAXNUM = maxNum;
        queue->front = queue->rear = NULL;
        return queue;
    }
}
// �ж�˳�򣨻��Σ������Ƿ�Ϊ��
int IsQueueEmpty(SeqQueue Q) {
    // ��Ϊ�գ�����ֵΪ1�����򷵻�ֵΪ0
    // �����в����ڣ��򷵻�-1
    if (Q == NULL) return -1;
    else  return(Q->front == Q->rear);
}
// �ж�˳�򣨻��Σ������Ƿ�����
int IsQueueFull(SeqQueue Q) {
    // ������������ֵΪ1�����򷵻�ֵΪ0
    return((Q->rear + 1) % Q->MAXNUM == Q->front);
}
// ���
int EnQueue(SeqQueue Q, QueueType x) {
    // �����벻�ɹ�������0������ɹ�����ֵΪ1
    if ((Q->rear + 1) % Q->MAXNUM == Q->front) return 0;
    else {
        Q->element[Q->rear] = x;
        Q->rear = (Q->rear + 1) % Q->MAXNUM;
        return 1;
    }
}
// ���Ӳ�����ɾ��Ԫ��
QueueType DeQueue(SeqQueue Q) {
    // ������Ϊ�գ��򷵻�-1
    if (Q->front == Q->rear) return -1;
    else {
        int del = Q->element[Q->front];
        Q->front = (Q->front + 1) % Q->MAXNUM;
        return del;
    }
}
// ȡ����Ԫ�ط���
QueueType GetQueueFront(SeqQueue Q){
    // ������Ϊ�գ��򷵻�-1
    if (Q->front == Q->rear) return -1;
    else  return(Q->element[Q->front]);
}
// ���ٶ��У��ͷŶ�����ռ�洢�ռ�
int DestroyQueue(SeqQueue Q){
    // ��������ջ����������Ԫ�صĸ���
    // �������ٵ����Ա����ڣ��򷵻�0
    if (Q->front == Q->rear) return 0;
}

/*  ��ĳ������A��B����ҵ�񴰿ڣ�A���ڴ���ҵ����ٶ���B���ڵ�2������A������2��ҵ��B�Ŵ�����һ����
�������еĹ˿����У��밴ҵ�����˳������˿����С��ٶ������ǹ˿͵����ʱ���������ҵ�A��B��������ͬ
ʱ������˿�ʱ��A���ڵĹ˿����뿪��
    ����һ����������һ�������ǹ˿͵�����N��N<1000��,�����N����������˿͵ı�ţ��ٶ����Ϊ�����Ĺ�
��ȥA���ڴ���ҵ�񣬶����Ϊż���Ĺ˿�ȥB���ڴ���ҵ�� */

/*
�������룺8  2  1  3  9   4  11  13  15
Ԥ�������1  3  2  9  11  4  13  15
*/

void QueueDemo(int a[], int n) {
    SeqQueue A = CreateSqlQueue(n * 2);	//���Ϊ�����Ĺ˿�ȥA���� 
    SeqQueue B = CreateSqlQueue(n * 2);	//���Ϊż���Ĺ˿�ȥB����

    for (int i = 0; i < n; i++) {
        if (a[i] % 2)	EnQueue(A, a[i]);
        else EnQueue(B, a[i]);
    }
    printf("�������:");
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
    if (IsQueueEmpty(Q)) printf("��ǰ����Ϊ��");
    for (int i = 0; i < 10; i++) {
        EnQueue(Q, i);
    }
    printf("\nDeQueue����: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", DeQueue(Q));
    }
    printf("\nGetQueueFront����: %d ", GetQueueFront(Q));
    DestroyQueue(Q);

    printf("\n\n���а�����\n");
    int a[] = {2,1,3,9,4,11,13,15};
    QueueDemo(a, 8);
}

