#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int SqlTableType;

typedef struct seqTable{
    int MAXNUM;     // 最大元素个数   
    int curNum;     // 元素的个数
    SqlTableType* element;  // 连续空间的起始地址  
} *SqlTable;

SqlTable CreateSqlTable(int max);   // 创建空顺序表
int IsSqlListFull(SqlTable L);      // 判断顺序表是否已满
int InsertSqlTable_P(SqlTable L, int p, SqlTableType x);     // 在下标p插入元素x
int InsertSqlTable_Pre(SqlTable L, int p, SqlTableType x);   // 在下标p的前面插入元素x
int InsertSqlTable_Post(SqlTable L, int p, SqlTableType x);  // 在下标p的后面插入元素x
int FindElement(SqlTable L, SqlTableType x);        // 查找元素x首次出现的位置
SqlTableType FindPostion(SqlTable L, int pos);      // 查找位置pos处的元素
int DeletePostion(SqlTable L, int pos);             // 删除下标pos处的元素
int DeleteElement(SqlTable L, SqlTableType x);      // 删除x值相同的数据元素
int DestroySqlTable(SqlTable L);                    // 销毁线性表
void PrintSqlTable(SqlTable L);     // 打印线性表


// 创建空顺序表，能存放的最大元素个数为max
SqlTable CreateSqlTable(int max){
    SqlTable L = (SqlTable)malloc(sizeof(struct seqTable));
    if (L != NULL) {
        L->element = (SqlTableType*)malloc(sizeof(SqlTableType) * max);
        if (L->element) {
            L->MAXNUM = max;
            L->curNum = 0;
            return L;
        }
        else free(L);
    }
    return NULL;
}

// 判断顺序线性表是否已满
// 若已满，返回值为1，否则返回值为0
int IsSqlListFull(SqlTable L){
    return (L->curNum == L->MAXNUM);
}

// 在下标p插入元素x
// 若下标p非法或线性表已满无法插入数据，返回0；插入成功返回值为1
int InsertSqlTable_P(SqlTable L, int p, SqlTableType x){
    if (L->curNum >= L->MAXNUM) {
        printf("线性表已满");
        return 0;
    }
    if (p < 0) {
        printf("插入位置非法");
        return 0;
    }
    L->element[p] = x;
    L->curNum = L->curNum + 1;
    return 1;
}

// 在下标p的前面插入元素x
// 若下标p非法或线性表已满无法插入数据，返回0；插入成功返回值为1
int InsertSqlTable_Pre(SqlTable L, int p, SqlTableType x){
    if (L->curNum >= L->MAXNUM) {
        printf("线性表已满");
        return 0;
    }
    if (p <= 0 || p > L->curNum) {
        printf("插入位置非法");
        return 0;
    }
    for (int i = L->curNum - 1; i >= p - 1; i--)
        L->element[i + 1] = L->element[i];
    L->element[p - 1] = x;
    L->curNum = L->curNum + 1;
    return 1;
}

// 在下标p的后面插入元素x
// 若下标p非法或线性表已满无法插入数据，返回0；插入成功返回值为1
int InsertSqlTable_Post(SqlTable L, int p, SqlTableType x) {
    if (L->curNum >= L->MAXNUM) {
        printf("线性表已满");
        return 0;
    }
    if (p < 0 || p >= L->curNum) {
        printf("插入位置非法");
        return 0;
    }
    for (int i = L->curNum - 1; i >= p + 1; i--)
        L->element[i + 1] = L->element[i];
    L->element[p + 1] = x;
    L->curNum = L->curNum + 1;
    return 1;
}

// 打印线性表
void PrintSqlTable(SqlTable L) {
    for (int i = 0; i < L->curNum; i++)
        printf("%d ", L->element[i]);
    printf("\n");
}

// 查找元素x首次出现的位置
// 若待销毁的线性表不存在，则返回0
int FindElement(SqlTable L, SqlTableType x){
    for (int i = 0; i < L->curNum; i++) {
        if (L->element[i] == x) return i;
    }
    return -1;
}

// 查找位置pos处的元素
// 若不存在给定值，则返回-1
SqlTableType FindPostion(SqlTable L, int pos){
    if (pos<0 || pos>L->curNum) return L->element[0];
    else return L->element[pos];
}

// 删除下标pos处的元素
// 若pos非法，则返回-1；否则返回1
int DeletePostion(SqlTable L, int pos) {
    if (pos<0 || pos > L->curNum - 1) return -1;
    for (int i = pos; i < L->curNum - 1; i++)
        L->element[i] = L->element[i + 1];
    L->curNum = L->curNum - 1;
    return 1;
}

// 删除x值相同的数据元素
// 返回删除数据元素的个数
int DeleteElement(SqlTable L, SqlTableType x){
    int num = 0;
    for (int i = 0; i < L->curNum; i++){
        if (L->element[i] == x){
            DeletePostion(L, i);
            num++;
        }
    }
    return num;
}

// 销毁线性表
// 返回销毁线性表元素的个数
int DestroySqlTable(SqlTable L) {
    int num = L->curNum;
    free(L->element);
    free(L);
    return num;
}


int main() {
    int max = 10;
    SqlTable table = CreateSqlTable(max);
    for (int i = 0; i < max; i++) {
        InsertSqlTable_P(table, i, i + 1);
    }
    PrintSqlTable(table);

    DeleteElement(table, 3);
    PrintSqlTable(table);

    DeletePostion(table, 3);
    PrintSqlTable(table);

    DestroySqlTable(table);
}