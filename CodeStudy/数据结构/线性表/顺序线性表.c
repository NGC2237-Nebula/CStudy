#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int SqlTableType;

typedef struct seqTable{
    int MAXNUM;     // ���Ԫ�ظ���   
    int curNum;     // Ԫ�صĸ���
    SqlTableType* element;  // �����ռ����ʼ��ַ  
} *SqlTable;

SqlTable CreateSqlTable(int max);   // ������˳���
int IsSqlListFull(SqlTable L);      // �ж�˳����Ƿ�����
int InsertSqlTable_P(SqlTable L, int p, SqlTableType x);     // ���±�p����Ԫ��x
int InsertSqlTable_Pre(SqlTable L, int p, SqlTableType x);   // ���±�p��ǰ�����Ԫ��x
int InsertSqlTable_Post(SqlTable L, int p, SqlTableType x);  // ���±�p�ĺ������Ԫ��x
int FindElement(SqlTable L, SqlTableType x);        // ����Ԫ��x�״γ��ֵ�λ��
SqlTableType FindPostion(SqlTable L, int pos);      // ����λ��pos����Ԫ��
int DeletePostion(SqlTable L, int pos);             // ɾ���±�pos����Ԫ��
int DeleteElement(SqlTable L, SqlTableType x);      // ɾ��xֵ��ͬ������Ԫ��
int DestroySqlTable(SqlTable L);                    // �������Ա�
void PrintSqlTable(SqlTable L);     // ��ӡ���Ա�


// ������˳����ܴ�ŵ����Ԫ�ظ���Ϊmax
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

// �ж�˳�����Ա��Ƿ�����
// ������������ֵΪ1�����򷵻�ֵΪ0
int IsSqlListFull(SqlTable L){
    return (L->curNum == L->MAXNUM);
}

// ���±�p����Ԫ��x
// ���±�p�Ƿ������Ա������޷��������ݣ�����0������ɹ�����ֵΪ1
int InsertSqlTable_P(SqlTable L, int p, SqlTableType x){
    if (L->curNum >= L->MAXNUM) {
        printf("���Ա�����");
        return 0;
    }
    if (p < 0) {
        printf("����λ�÷Ƿ�");
        return 0;
    }
    L->element[p] = x;
    L->curNum = L->curNum + 1;
    return 1;
}

// ���±�p��ǰ�����Ԫ��x
// ���±�p�Ƿ������Ա������޷��������ݣ�����0������ɹ�����ֵΪ1
int InsertSqlTable_Pre(SqlTable L, int p, SqlTableType x){
    if (L->curNum >= L->MAXNUM) {
        printf("���Ա�����");
        return 0;
    }
    if (p <= 0 || p > L->curNum) {
        printf("����λ�÷Ƿ�");
        return 0;
    }
    for (int i = L->curNum - 1; i >= p - 1; i--)
        L->element[i + 1] = L->element[i];
    L->element[p - 1] = x;
    L->curNum = L->curNum + 1;
    return 1;
}

// ���±�p�ĺ������Ԫ��x
// ���±�p�Ƿ������Ա������޷��������ݣ�����0������ɹ�����ֵΪ1
int InsertSqlTable_Post(SqlTable L, int p, SqlTableType x) {
    if (L->curNum >= L->MAXNUM) {
        printf("���Ա�����");
        return 0;
    }
    if (p < 0 || p >= L->curNum) {
        printf("����λ�÷Ƿ�");
        return 0;
    }
    for (int i = L->curNum - 1; i >= p + 1; i--)
        L->element[i + 1] = L->element[i];
    L->element[p + 1] = x;
    L->curNum = L->curNum + 1;
    return 1;
}

// ��ӡ���Ա�
void PrintSqlTable(SqlTable L) {
    for (int i = 0; i < L->curNum; i++)
        printf("%d ", L->element[i]);
    printf("\n");
}

// ����Ԫ��x�״γ��ֵ�λ��
// �������ٵ����Ա����ڣ��򷵻�0
int FindElement(SqlTable L, SqlTableType x){
    for (int i = 0; i < L->curNum; i++) {
        if (L->element[i] == x) return i;
    }
    return -1;
}

// ����λ��pos����Ԫ��
// �������ڸ���ֵ���򷵻�-1
SqlTableType FindPostion(SqlTable L, int pos){
    if (pos<0 || pos>L->curNum) return L->element[0];
    else return L->element[pos];
}

// ɾ���±�pos����Ԫ��
// ��pos�Ƿ����򷵻�-1�����򷵻�1
int DeletePostion(SqlTable L, int pos) {
    if (pos<0 || pos > L->curNum - 1) return -1;
    for (int i = pos; i < L->curNum - 1; i++)
        L->element[i] = L->element[i + 1];
    L->curNum = L->curNum - 1;
    return 1;
}

// ɾ��xֵ��ͬ������Ԫ��
// ����ɾ������Ԫ�صĸ���
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

// �������Ա�
// �����������Ա�Ԫ�صĸ���
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