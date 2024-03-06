#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/* 链式队列 */
typedef char QueueType;
typedef struct QueueNode{
	QueueType data;
	struct QueueNode* next;
}QueueNode;

typedef struct {
	QueueNode* front, * rear;
}LinkQueue;

void InitQueue(LinkQueue* Q);//初始化队列
int IsQueueEmpty(LinkQueue* Q);//判断队列是否为空
void EnQueue(LinkQueue* Q, QueueType data);//入队
int DeQueue(LinkQueue* Q, QueueType* data);//出队

//初始化队列
void InitQueue(LinkQueue* Q) {
	Q->front = Q->rear = (QueueNode*)malloc(sizeof(QueueNode)); // 分配头节点
	Q->front->next = NULL; //初始化为空
}
//判断队列是否为空
int IsQueueEmpty(LinkQueue* Q) {
	if (Q->front == Q->rear) return 1;
	else return 0;
}
//入队
void EnQueue(LinkQueue* Q, QueueType data) {
	QueueNode* news = (QueueNode*)malloc(sizeof(QueueNode));
	news->data = data; // 创建新节点，插入队列尾部 
	news->next = NULL;
	Q->rear->next = news;
	Q->rear = news;
}
//出队
int DeQueue(LinkQueue* Q, QueueType* data) {
	if (Q->front == Q->rear) return 0;
	QueueNode* del = Q->front->next;
	*data = del->data;
	Q->front->next = del->next;
	if (Q->rear == del)
		Q->rear = Q->front; // 若原队列只有一个节点，删除后变空 
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