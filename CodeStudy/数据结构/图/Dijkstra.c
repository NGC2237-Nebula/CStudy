#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define SIZE 6				//邻接矩阵大小（v0 - v5） 
#define MaxNum 999			//不可到达点的权值（即无穷大）

typedef char VertexType;
typedef int EdgeType;

/*图*/
typedef struct {
	VertexType Vexs[SIZE];		//结点 
	EdgeType Edges[SIZE][SIZE];	//权值 
	int vexnum, arcnum;
}MGraph;

/*路径*/
typedef struct {
	EdgeType length;			// 从源点v0到其他各点当前的最短路径长度
	int prevex;			// 从源点v0到点vi之间最短路径的前驱节点下标
}Path;



/*打印图的邻接矩阵和路径矩阵*/
void PrintResult(MGraph* G, Path path[]) {
	int i, j;
	printf("Edges[][] = \n\t");
	for (i = 0; i < G->vexnum; ++i)
		printf(" %c \t", G->Vexs[i]);
	printf("\n");

	for (i = 0; i < G->vexnum; ++i) {
		printf(" %c \t", G->Vexs[i]);
		for (j = 0; j < G->vexnum; j++)
			printf(" %d \t", G->Edges[i][j]);
		printf("\n");
	}

	printf("path[] = \n");
	for (int i = 0; i < G->vexnum; i++)
		printf(" %c: prevex = %c  lenght = %d\n", G->Vexs[i], G->Vexs[path[i].prevex], path[i].length);
	printf("\n");
}


/*打印指定点到源点的最短路径*/
void PrintPath(int v, Path path[], MGraph* G) {
	if (v > G->vexnum - 1 || v == -1) {
		printf("输入错误!");
		return; 
	}

	printf("%c -> ", G->Vexs[v]);
	int i = v;
	while (path[i].prevex != 0) {
		printf("%c -> ", G->Vexs[path[i].prevex]);
		i = path[i].prevex;
	}
	printf("%c = %d", G->Vexs[0], path[v].length);
	return;
}

/*寻找结点G->Vexs[start]对应的储存位置i*/
int Find(VertexType find_point, MGraph* G) {
	for (int i = 0; i < G->vexnum; i++)
		if (G->Vexs[i] == find_point) return i;
	return -1;
}

/*初始化图并输入权值*/
MGraph* InitGraph() {
	MGraph*  G = (MGraph*)malloc(sizeof(MGraph));
	G->vexnum = 6;
	G->arcnum = 9;

	//初始化图的邻接矩阵 Edges[SIZE][SIZE]
	for (int i = 0; i < G->vexnum; i++) {
		for (int j = 0; j < G->vexnum; j++) {
			if (i == j)	G->Edges[i][j] = 0;		//对角线权值为0 
			else		G->Edges[i][j] = MaxNum;	//除对角线外所有权值为无穷大 
		}
	}

	//初始化图的结点矩阵 Vexs[SIZE]
	VertexType v[6] = { 'A','B','C','D','E','F' };
	for (int i = 0; i < G->vexnum; i++)
		G->Vexs[i] = v[i];

	//初始化图的边权
	int  start_vex[9] = { 0,0,1,1,3,3,2,3,4 };
	int    end_vex[9] = { 1,2,2,3,2,4,4,5,5 };
	int vex_weight[9] = { 1,12,9,3,4,13,5,15,4 };
	for (int i = 0; i < G->arcnum; i++)
		G->Edges[start_vex[i]][end_vex[i]] = vex_weight[i];
	return G;
}

/*初始化路径矩阵*/
void InitPath(MGraph* G, Path path[]) {
	path[0].length = 0;
	path[0].prevex = 0;
	G->Edges[0][0] = 1;
	for (int i = 1; i < G->vexnum; ++i) {
		path[i].length = G->Edges[0][i];
		if (path[i].length != MaxNum) path[i].prevex = 0;
		else path[i].prevex = -1;
	}
}

/*Dijkstra算法寻找最短路径*/
void Dijkstra(MGraph* G, Path path[]) {
	int i, j, min_vex, min_length;

	for (i = 1; i < G->vexnum; ++i) {
		min_length = MaxNum;	//当前到Vi的最短路径长度 
		min_vex = 0;		//当前到Vi的最短路径对应的上一个结点

		for (j = 1; j < G->vexnum; ++j) {
			if (G->Edges[j][j] == 0 && path[j].length < min_length) {
				min_vex = j;
				min_length = path[j].length;
			}
		}
		if (min_vex == 0) break;
		G->Edges[min_vex][min_vex] = 1;

		for (j = 1; j < G->vexnum; ++j) {
			if (G->Edges[j][j] == 0 && path[j].length > path[min_vex].length + G->Edges[min_vex][j]) {
				path[j].prevex = min_vex;
				path[j].length = path[min_vex].length + G->Edges[min_vex][j];
			}
		}
	}
}


int main() {
	MGraph* G = InitGraph();
	Path path[6];
	InitPath(G, path);

	Dijkstra(G, path);
	PrintResult(G, path);

	VertexType end;
	printf("输入终点：");
	scanf("%c", &end);
	PrintPath(Find(end, G), path, G);

	return 0;
}


/*输出：
G->Edges[][] =
		 V1      V2      V3      V4      V5      V6
 V1      0       1       12      999     999     999
 V2      999     0       9       3       999     999
 V3      999     999     0       999     5       999
 V4      999     999     4       0       13      15
 V5      999     999     999     999     0       4
 V6      999     999     999     999     999     0

path[] =
 V0: prevex = 0   lenght = 0
 V1: prevex = 1   lenght = 1
 V2: prevex = 2   lenght = 8
 V3: prevex = 3   lenght = 4
 V4: prevex = 4   lenght = 13
 V5: prevex = 5   lenght = 17 
 */