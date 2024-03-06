#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MaxNum 999			// 无穷大值
#define MaxVertexNum 100	// 最大可存储的节点数目

/*图*/
typedef char VertexType;
typedef int EdgeType;

typedef struct GraphMatrix{
	VertexType Vexs[MaxVertexNum];				//结点 
	EdgeType Edges[MaxVertexNum][MaxVertexNum];	//边
	int vexnum, arcnum;							//当前点数和边数
}*MGraph;

int visited[MaxVertexNum]; // 记录是否访问该节点，访问过为1，否则为0

/*队列*/
typedef int QueueType;
typedef struct QueueNode {
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


void PrintGraph(MGraph G);//打印图的邻接矩阵
MGraph InitGraph();//初始化图并输入数据
int Adjacent(MGraph G, int x, int y);//判断是否存在某条边(x,y)
int FirstNeighbor(MGraph G, int v);//求点v的第一个邻接点
int NextNeighbor(MGraph G, int v, int w);//求点v的邻接点w的下一个邻接点

void Visit(MGraph G, int v);//访问该节点的信息
void BFS(MGraph G, LinkQueue Q, int v);// 广度优先遍历
void BFSTraverse(MGraph G);//广度优先遍历 主函数
void DFS(MGraph G, int v);//深度优先遍历
void DFSTraverse(MGraph G);//深度优先遍历 主函数
void BFS_MinDistance(MGraph G, int u);// BFS求解 非带权图 单源最短路径问题
void PrintDistence(int* d, int size);// 打印图的单源最短路径矩阵



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

// 打印图的邻接矩阵
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
// 初始化图并输入数据
MGraph InitGraph() {
	int i, j;
	MGraph G = (MGraph)malloc(sizeof(struct GraphMatrix));
	G->vexnum = 6;
	G->arcnum = 14;

	/* 初始化图的邻接矩阵 Edges[MaxVertexNum][MaxVertexNum] */
	for (i = 0; i < G->vexnum; i++) {
		for (j = 0; j < G->vexnum; j++) {
			G->Edges[i][j] = 0;
		}
	}

	/* 输入图的结点矩阵 Vexs[MaxVertexNum] */
	VertexType v[6] = { 'A','B','C','D','E','F' };
	for (i = 0; i < G->vexnum; i++)
		G->Vexs[i] = v[i];

	/* 输入图的边权 */
	int  start_vex[14] = { 0,0,0,1,1,1,2,2,3,3,4,4,5,5 };
	int    end_vex[14] = { 1,2,3,0,4,5,0,1,0,5,1,2,1,3 };
	for (i = 0; i < G->arcnum; i++)
		G->Edges[start_vex[i]][end_vex[i]] = 1;
	return G;
}
// 判断是否存在某条边(x,y)
int Adjacent(MGraph G, int x, int y) {
	if (G->Edges[x][y] == 1)
		return 1;
	else
		return -1;
}
// 求点v的第一个邻接点
// 若有返回顶点号，否则返回-1
int FirstNeighbor(MGraph G, int v) {
	for (int i = 0; i < G->vexnum; i++) {
		if (G->Edges[v][i] == 1)
			return i;
	}
	return -1;
}
// 求点v的邻接点w的下一个邻接点
// 若有返回顶点号，否则返回-1
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

// 访问该节点的信息
void Visit(MGraph G,int v) {
	printf("%c ",G->Vexs[v]);
}
// 广度优先遍历
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
// 广度优先遍历 主函数
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
// 打印图的单源最短路径矩阵
void PrintDistence(int *d,int size) {
	printf("\n单源最短路径矩阵 : ");
	for (int i = 0; i < size; ++i)
		printf("%d ", d[i]);
}
// BFS求解 非带权图 单源最短路径问题
void BFS_MinDistance(MGraph G, int u) {
	int distance[6]; // distance[i]表示从u到i节点的最短路径
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
// 深度优先遍历
void DFS(MGraph G, int v) {
	Visit(G, v);
	visited[v] = 1;
	for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {
		if (visited[w] == 0) 
			DFS(G, w);
	}
}
// 深度优先遍历 主函数
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

	printf("\n广度优先遍历 : ");
	BFSTraverse(G);

	printf("\n深度优先遍历 : ");
	DFSTraverse(G);

	BFS_MinDistance(G, 0);
	return 0;
}