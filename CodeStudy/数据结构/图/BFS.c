#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MaxNum 999			// �����ֵ
#define MaxVertexNum 100	// ���ɴ洢�Ľڵ���Ŀ

/*ͼ*/
typedef char VertexType;
typedef int EdgeType;

typedef struct GraphMatrix{
	VertexType Vexs[MaxVertexNum];				//��� 
	EdgeType Edges[MaxVertexNum][MaxVertexNum];	//��
	int vexnum, arcnum;							//��ǰ�����ͱ���
}*MGraph;

int visited[MaxVertexNum]; // ��¼�Ƿ���ʸýڵ㣬���ʹ�Ϊ1������Ϊ0

/*����*/
typedef int QueueType;
typedef struct QueueNode {
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


void PrintGraph(MGraph G);//��ӡͼ���ڽӾ���
MGraph InitGraph();//��ʼ��ͼ����������
int Adjacent(MGraph G, int x, int y);//�ж��Ƿ����ĳ����(x,y)
int FirstNeighbor(MGraph G, int v);//���v�ĵ�һ���ڽӵ�
int NextNeighbor(MGraph G, int v, int w);//���v���ڽӵ�w����һ���ڽӵ�

void Visit(MGraph G, int v);//���ʸýڵ����Ϣ
void BFS(MGraph G, LinkQueue Q, int v);// ������ȱ���
void BFSTraverse(MGraph G);//������ȱ��� ������
void DFS(MGraph G, int v);//������ȱ���
void DFSTraverse(MGraph G);//������ȱ��� ������
void BFS_MinDistance(MGraph G, int u);// BFS��� �Ǵ�Ȩͼ ��Դ���·������
void PrintDistence(int* d, int size);// ��ӡͼ�ĵ�Դ���·������



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

// ��ӡͼ���ڽӾ���
void PrintGraph(MGraph G) {
	int i, j;
	printf("G->Edges[][] = \n\t");

	for (i = 0; i < G->vexnum; ++i)
		printf(" %c \t", G->Vexs[i]);
	printf("\n");

	for (i = 0; i < G->vexnum; ++i) {
		printf(" %c \t", G->Vexs[i]);
		for (j = 0; j < G->vexnum; j++)
			printf(" %d \t", G->Edges[i][j]);
		printf("\n");
	}
}
// ��ʼ��ͼ����������
MGraph InitGraph() {
	int i, j;
	MGraph G = (MGraph)malloc(sizeof(struct GraphMatrix));
	G->vexnum = 6;
	G->arcnum = 14;

	/* ��ʼ��ͼ���ڽӾ��� Edges[MaxVertexNum][MaxVertexNum] */
	for (i = 0; i < G->vexnum; i++) {
		for (j = 0; j < G->vexnum; j++) {
			G->Edges[i][j] = 0;
		}
	}

	/* ����ͼ�Ľ����� Vexs[MaxVertexNum] */
	VertexType v[6] = { 'A','B','C','D','E','F' };
	for (i = 0; i < G->vexnum; i++)
		G->Vexs[i] = v[i];

	/* ����ͼ�ı�Ȩ */
	int  start_vex[14] = { 0,0,0,1,1,1,2,2,3,3,4,4,5,5 };
	int    end_vex[14] = { 1,2,3,0,4,5,0,1,0,5,1,2,1,3 };
	for (i = 0; i < G->arcnum; i++)
		G->Edges[start_vex[i]][end_vex[i]] = 1;
	return G;
}
// �ж��Ƿ����ĳ����(x,y)
int Adjacent(MGraph G, int x, int y) {
	if (G->Edges[x][y] == 1)
		return 1;
	else
		return -1;
}
// ���v�ĵ�һ���ڽӵ�
// ���з��ض���ţ����򷵻�-1
int FirstNeighbor(MGraph G, int v) {
	for (int i = 0; i < G->vexnum; i++) {
		if (G->Edges[v][i] == 1)
			return i;
	}
	return -1;
}
// ���v���ڽӵ�w����һ���ڽӵ�
// ���з��ض���ţ����򷵻�-1
int NextNeighbor(MGraph G, int v, int w) {
	if (w < G->vexnum) {
		for (int i = w + 1; i < G->vexnum; i++) {
			if (G->Edges[v][i] == 1)
				return i;
		}
		return -1;
	}
	return -1;
}

// ���ʸýڵ����Ϣ
void Visit(MGraph G,int v) {
	printf("%c ",G->Vexs[v]);
}
// ������ȱ���
void BFS(MGraph G, LinkQueue Q, int v) {
	Visit(G, v);
	visited[v] = 1;
	EnQueue(&Q, v);
	while (!IsQueueEmpty(&Q)) {
		DeQueue(&Q, &v);
		for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {
			if (visited[w] == 0) {
				Visit(G, w);
				visited[w] = 1;
				EnQueue(&Q, w);
			}
		}
	}
}
// ������ȱ��� ������
void BFSTraverse(MGraph G) {
	for (int i = 0; i < G->vexnum; ++i) {
		visited[i] = 0;
	}
	LinkQueue Q;
	InitQueue(&Q);
	for (int i = 0; i < G->vexnum; ++i) {
		if (visited[i] == 0)
			BFS(G, Q, i);
	}
}
// ��ӡͼ�ĵ�Դ���·������
void PrintDistence(int *d,int size) {
	printf("\n��Դ���·������ : ");
	for (int i = 0; i < size; ++i)
		printf("%d ", d[i]);
}
// BFS��� �Ǵ�Ȩͼ ��Դ���·������
void BFS_MinDistance(MGraph G, int u) {
	int distance[6]; // distance[i]��ʾ��u��i�ڵ�����·��
	for (int i = 0; i < G->vexnum; ++i) {
		visited[i] = 0;
		distance[i] = MaxNum;
	}
	visited[u] = 1; 
	distance[u] = 0;

	LinkQueue Q;
	InitQueue(&Q);
	EnQueue(&Q, u);
	while (!IsQueueEmpty(&Q)) {
		DeQueue(&Q, &u);
		for (int w = FirstNeighbor(G, u); w >= 0; w = NextNeighbor(G, u, w)) {
			if (!visited[w]) {
				visited[w] = 1;
				distance[w] = distance[u] + 1;
				EnQueue(&Q, w);
			}
		}
	}
	PrintDistence(distance,6);	
}
// ������ȱ���
void DFS(MGraph G, int v) {
	Visit(G, v);
	visited[v] = 1;
	for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {
		if (visited[w] == 0) 
			DFS(G, w);
	}
}
// ������ȱ��� ������
void DFSTraverse(MGraph G) {
	for (int i = 0; i < G->vexnum; ++i) {
		visited[i] = 0;
	}
	for (int i = 0; i < G->vexnum; ++i) {
		if (visited[i] == 0)
			DFS(G, i);
	}
}


int main() {
	MGraph G = InitGraph();
	PrintGraph(G);

	printf("\n������ȱ��� : ");
	BFSTraverse(G);

	printf("\n������ȱ��� : ");
	DFSTraverse(G);

	BFS_MinDistance(G, 0);
	return 0;
}