#include "stdio.h"
#include "malloc.h"
#include <iostream>
#include <stack>
#include <queue>
using namespace std;


typedef struct AVLNode{
    int data = 0;//���ֵ
    int depth = 0;//���
    struct AVLNode* father = NULL;//�����
    struct AVLNode* lchild = NULL, * rchild = NULL;//���ҽ��
} AVLNode, * AVLTree; //���ṹ��


//������������
int count_depth(AVLTree& T) {
    if (T == NULL) {
        return 0;
    }
    else {
        int l = count_depth(T->lchild);//���������
        int r = count_depth(T->rchild);//���������
        return T->depth = max(l, r) + 1;//�������
    }
}

//��ȡ���
int get_balance(AVLTree T) {
    if (T) {
        return T->depth;
    }
    else {
        return 0;
    }
}
//����ƽ������
int count_balance(AVLTree T) {
    if (!T) {
        return 0;
    }
    else {
        return get_balance(T->lchild) - get_balance(T->rchild);//ƽ�����ӵ����������������֮��
    }
}

AVLTree LL_rotate(AVLTree T){
    AVLTree parent = NULL, son;//son��㼴Ϊ��ת����
    parent = T->father;//��ȡʧ����ĸ��ڵ�
    son = T->lchild;//��ȡʧ���������
    if (son->rchild != NULL)//����son����Һ��ӵĸ�ָ��
        son->rchild->father = T;
    T->lchild = son->rchild;//ʧ��������ӱ��Ϊson���Һ���
    //T���ӽ��������
    count_depth(T);//����ʧ����������Ϣ
    son->rchild = T;//ʧ������son���Һ���
    son->father = parent;//����son�ĸ����Ϊԭʧ����ĸ���㣬����������
    //���ʧ���㲻�Ǹ���㣬����¸��ڵ�
    if (parent != NULL)
    {
        //������ڵ��������ʧ���㣬ָ�����ڸ��º���º���son
        if (parent->lchild == T)
            parent->lchild = son;
        else //���ڵ���Һ�����ʧ����
            parent->rchild = son;
    }
    T->father = son;//����ʧ����ĸ���
    count_depth(son);//����son���ĸ߶���Ϣ
    return son;
}

AVLTree RR_rotate(AVLTree T){
    AVLTree parent = NULL, son;//son��㼴Ϊ��ת����
    parent = T->father;//��ȡʧ����ĸ��ڵ�
    son = T->rchild;//��ȡʧ������Һ���
    if (son->lchild != NULL)//����son������ӵĸ�ָ��
        son->lchild->father = T;
    T->rchild = son->lchild;//ʧ������Һ��ӱ��Ϊson������
    //T���ӽ��������
    count_depth(T);//����ʧ����ĸ߶���Ϣ
    son->lchild = T;//ʧ������son���Һ���
    son->father = parent;//����son�ĸ����Ϊԭʧ����ĸ���㣬����������
    //���ʧ���㲻�Ǹ���㣬����¸��ڵ�
    if (parent != NULL)
    {
        //������ڵ��������ʧ���㣬ָ�����ڸ��º���º���son
        if (parent->lchild == T)
            parent->lchild = son;
        else //���ڵ���Һ�����ʧ����
            parent->rchild = son;
    }
    T->father = son;//����ʧ����ĸ���
    count_depth(son);//����son���ĸ߶���Ϣ
    return son;
}

AVLTree LR_rotate(AVLTree T){
    RR_rotate(T->lchild);
    return LL_rotate(T);
}

AVLTree RL_rotate(AVLTree T){
    LL_rotate(T->rchild);
    return RR_rotate(T);
}

//����Ϊƽ�������
AVLTree AVLchange(AVLTree& T, AVLTree S) {
    int balance = 0;//ƽ������
    while (S) {
        count_depth(T);//�������
        balance = count_balance(S);//����ƽ������
        if (balance > 1 || balance < -1) {
            //L��
            if (balance > 1) {
                //LL��
                if (count_balance(S->lchild) > 0) {
                    S = LL_rotate(S);
                }
                //LR��
                else {
                    S = LR_rotate(S);
                }
            }
            //R��
            if (balance < 1) {
                //RR��
                if (count_balance(S->rchild) < 0)
                    S = RR_rotate(S);
                //RL��
                else S = RL_rotate(S);
            }
            //������ڵ㣬�˳�ѭ��
            if (S->father == NULL) {
                T = S;//����Ϊ�µĸ��ڵ�
                break;
            }
        }
        S = S->father;//һ��һ�����ϵ���
    }
    return T;
}

AVLTree InsertAVL(AVLTree& T, int e, AVLTree parent) {
    //�ҵ�������λ��
    if (!T) {
        AVLNode* S;
        S = new AVLNode;
        S->data = e;
        S->father = parent;
        S->lchild = S->rchild = NULL;
        T = S;
        return S;
    }
    //��������
    else if (e < T->data) {
        return InsertAVL(T->lchild, e, T);
    }
    //��������
    else if (e > T->data) {
        return InsertAVL(T->rchild, e, T);
    }
    return NULL;//�ý���Ѵ���
}

AVLTree Insert(AVLTree& T, int e){
    AVLNode* S;
    S = new AVLNode;
    S = InsertAVL(T, e, NULL);//������
    count_depth(T);//���������Ϣ
    T = AVLchange(T, S);//����Ϊƽ�������
    return T;
}

void creativetree(AVLTree& T) {
    T = NULL;
    int e, n, i;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &e);
        T = Insert(T, e);
    }
}


int main(){
    AVLTree T;
    creativetree(T);//����
    return 0;
}
