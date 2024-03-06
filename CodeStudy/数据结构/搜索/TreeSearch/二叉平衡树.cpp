#include "stdio.h"
#include "malloc.h"
#include <iostream>
#include <stack>
#include <queue>
using namespace std;


typedef struct AVLNode{
    int data = 0;//结点值
    int depth = 0;//深度
    struct AVLNode* father = NULL;//父结点
    struct AVLNode* lchild = NULL, * rchild = NULL;//左右结点
} AVLNode, * AVLTree; //结点结构体


//计算各结点的深度
int count_depth(AVLTree& T) {
    if (T == NULL) {
        return 0;
    }
    else {
        int l = count_depth(T->lchild);//左子树深度
        int r = count_depth(T->rchild);//右子树深度
        return T->depth = max(l, r) + 1;//更新深度
    }
}

//读取深度
int get_balance(AVLTree T) {
    if (T) {
        return T->depth;
    }
    else {
        return 0;
    }
}
//计算平衡因子
int count_balance(AVLTree T) {
    if (!T) {
        return 0;
    }
    else {
        return get_balance(T->lchild) - get_balance(T->rchild);//平衡因子等于左右子树的深度之差
    }
}

AVLTree LL_rotate(AVLTree T){
    AVLTree parent = NULL, son;//son结点即为旋转中心
    parent = T->father;//获取失衡结点的父节点
    son = T->lchild;//获取失衡结点的左孩子
    if (son->rchild != NULL)//设置son结点右孩子的父指针
        son->rchild->father = T;
    T->lchild = son->rchild;//失衡结点的左孩子变更为son的右孩子
    //T的子结点更新完毕
    count_depth(T);//更新失衡结点的深度信息
    son->rchild = T;//失衡结点变成son的右孩子
    son->father = parent;//设置son的父结点为原失衡结点的父结点，连接整颗树
    //如果失衡结点不是根结点，则更新父节点
    if (parent != NULL)
    {
        //如果父节点的左孩子是失衡结点，指向现在更新后的新孩子son
        if (parent->lchild == T)
            parent->lchild = son;
        else //父节点的右孩子是失衡结点
            parent->rchild = son;
    }
    T->father = son;//设置失衡结点的父亲
    count_depth(son);//更新son结点的高度信息
    return son;
}

AVLTree RR_rotate(AVLTree T){
    AVLTree parent = NULL, son;//son结点即为旋转中心
    parent = T->father;//获取失衡结点的父节点
    son = T->rchild;//获取失衡结点的右孩子
    if (son->lchild != NULL)//设置son结点左孩子的父指针
        son->lchild->father = T;
    T->rchild = son->lchild;//失衡结点的右孩子变更为son的左孩子
    //T的子结点更新完毕
    count_depth(T);//更新失衡结点的高度信息
    son->lchild = T;//失衡结点变成son的右孩子
    son->father = parent;//设置son的父结点为原失衡结点的父结点，连接整颗树
    //如果失衡结点不是根结点，则更新父节点
    if (parent != NULL)
    {
        //如果父节点的左孩子是失衡结点，指向现在更新后的新孩子son
        if (parent->lchild == T)
            parent->lchild = son;
        else //父节点的右孩子是失衡结点
            parent->rchild = son;
    }
    T->father = son;//设置失衡结点的父亲
    count_depth(son);//更新son结点的高度信息
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

//调整为平衡二叉树
AVLTree AVLchange(AVLTree& T, AVLTree S) {
    int balance = 0;//平衡因子
    while (S) {
        count_depth(T);//计算深度
        balance = count_balance(S);//计算平衡因子
        if (balance > 1 || balance < -1) {
            //L型
            if (balance > 1) {
                //LL型
                if (count_balance(S->lchild) > 0) {
                    S = LL_rotate(S);
                }
                //LR型
                else {
                    S = LR_rotate(S);
                }
            }
            //R型
            if (balance < 1) {
                //RR型
                if (count_balance(S->rchild) < 0)
                    S = RR_rotate(S);
                //RL型
                else S = RL_rotate(S);
            }
            //到达根节点，退出循环
            if (S->father == NULL) {
                T = S;//更新为新的根节点
                break;
            }
        }
        S = S->father;//一层一层往上调整
    }
    return T;
}

AVLTree InsertAVL(AVLTree& T, int e, AVLTree parent) {
    //找到结点插入位置
    if (!T) {
        AVLNode* S;
        S = new AVLNode;
        S->data = e;
        S->father = parent;
        S->lchild = S->rchild = NULL;
        T = S;
        return S;
    }
    //向左搜索
    else if (e < T->data) {
        return InsertAVL(T->lchild, e, T);
    }
    //向右搜索
    else if (e > T->data) {
        return InsertAVL(T->rchild, e, T);
    }
    return NULL;//该结点已存在
}

AVLTree Insert(AVLTree& T, int e){
    AVLNode* S;
    S = new AVLNode;
    S = InsertAVL(T, e, NULL);//插入结点
    count_depth(T);//更新深度信息
    T = AVLchange(T, S);//调整为平衡二叉树
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
    creativetree(T);//建树
    return 0;
}
