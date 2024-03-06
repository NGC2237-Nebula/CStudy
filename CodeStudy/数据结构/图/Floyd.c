#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define SIZE 4          //�ڽӾ����С��v0 - v3��
#define MaxNum 999      //���ɵ�����Ȩֵ���������

typedef int VertexType;
typedef int EdgeType;

/*ͼ*/
typedef struct {
    VertexType Vexs[SIZE];		//��� 
    EdgeType Edges[SIZE][SIZE];	//Ȩֵ 
    int vexnum, arcnum;
}MGraph;

/*·��*/
typedef struct {
    int path[SIZE][SIZE];
    EdgeType length;
}Path;


/* ��ʼ��ͼ������Ȩֵ */
MGraph* InitGraph() {
    MGraph* G = (MGraph*)malloc(sizeof(MGraph));
    G->vexnum = 4;
    G->arcnum = 8;
    //��ʼ��ͼ���ڽӾ��� Edges[SIZE][SIZE]
    for (int i = 0; i < G->vexnum; i++) {
        for (int j = 0; j < G->vexnum; j++) {
            if (i == j)	G->Edges[i][j] = 0;		//�Խ���ȨֵΪ0 
            else		G->Edges[i][j] = MaxNum;	//���Խ���������ȨֵΪ����� 
        }
    }
    //��ʼ��ͼ�Ľ����� Vexs[SIZE]
    VertexType v[4] = { 0,1,2,3 };
    for (int i = 0; i < G->vexnum; i++)
        G->Vexs[i] = v[i];
    //��ʼ��ͼ�ı�Ȩ
    int  start_vex[8] = { 0,0,1,1,2,2,2,3 };
    int    end_vex[8] = { 1,3,2,3,0,1,3,2 };
    int vex_weight[8] = { 5,7,4,2,3,3,2,1 };
    for (int i = 0; i < G->arcnum; i++)
        G->Edges[start_vex[i]][end_vex[i]] = vex_weight[i];
    return G;
}

/* ��ʼ��·������ */
Path InitPath() {
    Path path;
    path.length = 0;
    return path;
}

/* Floyd�㷨Ѱ�����·�� */
void Floyd(MGraph* Graph, Path *path) {
    int i, j, k, nun = Graph->vexnum;
    int temp[SIZE][SIZE];
    // ��ʼ��
    for (i = 0; i < nun; i++) {
        for (j = 0; j < nun; j++) {
            temp[i][j] = Graph->Edges[i][j];
            path->path[i][j] = -1;
        }
    }
    // �㷨����
    for (k = 0; k < nun; k++) {
        for (i = 0; i < nun; i++) {
            for (j = 0; j < nun; j++) {
                if (temp[i][j] > temp[i][k] + temp[k][j]) {
                    temp[i][j] = temp[i][k] + temp[k][j];
                    path->path[i][j] = k;
                }
            }
        }
    }
}

/* �ݹ�Ѱ�����·�� */
void FindPath(int start, int end, Path* path, MGraph* Graph) {
    if (path->path[start][end] == -1) {
        printf("-> %d ", end);
        path->length = path->length + Graph->Edges[start][end];
    }
    else {
        int mid = path->path[start][end];
        FindPath(start, mid, path, Graph);
        FindPath(mid, end, path, Graph);
    }
}

/* ��ӡ���·�� */
void PrintPath(MGraph* Graph, Path* path) {
    VertexType start, end;
    printf("������㣺");
    scanf("%d", &start);
    printf("�����յ㣺");
    scanf("%d", &end);

    printf("%d ", start);
    FindPath(start, end, path, Graph);
    printf("= %d", path->length);
}

int main() {
    MGraph* Graph = InitGraph();
    Path path = InitPath();

    Floyd(Graph, &path);
    PrintPath(Graph, &path);
    return 0;
}