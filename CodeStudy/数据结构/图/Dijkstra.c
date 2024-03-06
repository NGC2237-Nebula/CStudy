#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define SIZE 6				//�ڽӾ����С��v0 - v5�� 
#define MaxNum 999			//���ɵ�����Ȩֵ���������

typedef char VertexType;
typedef int EdgeType;

/*ͼ*/
typedef struct {
	VertexType Vexs[SIZE];		//��� 
	EdgeType Edges[SIZE][SIZE];	//Ȩֵ 
	int vexnum, arcnum;
}MGraph;

/*·��*/
typedef struct {
	EdgeType length;			// ��Դ��v0���������㵱ǰ�����·������
	int prevex;			// ��Դ��v0����vi֮�����·����ǰ���ڵ��±�
}Path;



/*��ӡͼ���ڽӾ����·������*/
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


/*��ӡָ���㵽Դ������·��*/
void PrintPath(int v, Path path[], MGraph* G) {
	if (v > G->vexnum - 1 || v == -1) {
		printf("�������!");
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

/*Ѱ�ҽ��G->Vexs[start]��Ӧ�Ĵ���λ��i*/
int Find(VertexType find_point, MGraph* G) {
	for (int i = 0; i < G->vexnum; i++)
		if (G->Vexs[i] == find_point) return i;
	return -1;
}

/*��ʼ��ͼ������Ȩֵ*/
MGraph* InitGraph() {
	MGraph*  G = (MGraph*)malloc(sizeof(MGraph));
	G->vexnum = 6;
	G->arcnum = 9;

	//��ʼ��ͼ���ڽӾ��� Edges[SIZE][SIZE]
	for (int i = 0; i < G->vexnum; i++) {
		for (int j = 0; j < G->vexnum; j++) {
			if (i == j)	G->Edges[i][j] = 0;		//�Խ���ȨֵΪ0 
			else		G->Edges[i][j] = MaxNum;	//���Խ���������ȨֵΪ����� 
		}
	}

	//��ʼ��ͼ�Ľ����� Vexs[SIZE]
	VertexType v[6] = { 'A','B','C','D','E','F' };
	for (int i = 0; i < G->vexnum; i++)
		G->Vexs[i] = v[i];

	//��ʼ��ͼ�ı�Ȩ
	int  start_vex[9] = { 0,0,1,1,3,3,2,3,4 };
	int    end_vex[9] = { 1,2,2,3,2,4,4,5,5 };
	int vex_weight[9] = { 1,12,9,3,4,13,5,15,4 };
	for (int i = 0; i < G->arcnum; i++)
		G->Edges[start_vex[i]][end_vex[i]] = vex_weight[i];
	return G;
}

/*��ʼ��·������*/
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

/*Dijkstra�㷨Ѱ�����·��*/
void Dijkstra(MGraph* G, Path path[]) {
	int i, j, min_vex, min_length;

	for (i = 1; i < G->vexnum; ++i) {
		min_length = MaxNum;	//��ǰ��Vi�����·������ 
		min_vex = 0;		//��ǰ��Vi�����·����Ӧ����һ�����

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
	printf("�����յ㣺");
	scanf("%c", &end);
	PrintPath(Find(end, G), path, G);

	return 0;
}


/*�����
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