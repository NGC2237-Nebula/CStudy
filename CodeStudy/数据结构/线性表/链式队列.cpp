#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/* ��ʽ���� */
typedef char QueueType;
typedef struct QueueNode{
	QueueType data;
	struct QueueNode* next;
}QueueNode;

typedef struct {
	QueueNode* front, * rear;
}LinkQueue;

void InitQueue(LinkQueue* Q);//��ʼ������
int IsQueueEmpty(LinkQueue* Q);//�ж϶����Ƿ�Ϊ��
void EnQueue(LinkQueue* Q, QueueType data);//���
int DeQueue(LinkQueue* Q, QueueType* data);//����

//��ʼ������
void InitQueue(LinkQueue* Q) {
	Q->front = Q->rear = (QueueNode*)malloc(sizeof(QueueNode)); // ����ͷ�ڵ�
	Q->front->next = NULL; //��ʼ��Ϊ��
}
//�ж϶����Ƿ�Ϊ��
int IsQueueEmpty(LinkQueue* Q) {
	if (Q->front == Q->rear) return 1;
	else return 0;
}
//���
void EnQueue(LinkQueue* Q, QueueType data) {
	QueueNode* news = (QueueNode*)malloc(sizeof(QueueNode));
	news->data = data; // �����½ڵ㣬�������β�� 
	news->next = NULL;
	Q->rear->next = news;
	Q->rear = news;
}
//����
int DeQueue(LinkQueue* Q, QueueType* data) {
	if (Q->front == Q->rear) return 0;
	QueueNode* del = Q->front->next;
	*data = del->data;
	Q->front->next = del->next;
	if (Q->rear == del)
		Q->rear = Q->front; // ��ԭ����ֻ��һ���ڵ㣬ɾ������ 
	free(del);
	return 1;
}

int main() {
	LinkQueue Q;
	InitQueue(&Q);
	EnQueue(&Q, 'a');
	EnQueue(&Q, 'b');
	EnQueue(&Q, 'c');

	char x;
	DeQueue(&Q, &x);
	printf("%c", x);
	DeQueue(&Q, &x);
	printf("%c", x);
	DeQueue(&Q, &x);
	printf("%c", x);
}