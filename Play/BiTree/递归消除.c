#include <stdio.h>
#include "stdlib.h"


typedef BiTree StackElementType;
#define Stack_Size 50//设栈中元素个数为50

/*顺序栈的存储结构*/
typedef struct{
    StackElementType elem[Stack_Size];//用来存放栈中元素的一维数组
    int top;//用来存放栈顶元素的下标，top为-1表示空栈
}SeqStack;
/*初始化顺序栈*/
void InitStack(SeqStack * S){//构造一个空栈S
    S->top = -1;
}
/*顺序栈进栈运算*/
int Push(SeqStack * S,StackElementType x){//将x置入S栈新栈顶
    if(S->top==Stack_Size-1) return 0;//栈已满
    S->top++;//修改栈顶指针
    S->elem[S->top] = x;//x进栈
    return 1;
}
/*顺序栈出栈运算*/
int Pop(SeqStack * S,StackElementType * x){//将S栈顶元素弹出，放到x所指的存储空间中带出
    if(S->top==-1) return 0;//栈为空
    *x = S->elem[S->top];//栈顶元素赋给x
    S->top--;//修改栈顶指针
    return 1;
}
/*顺序栈读栈顶元素运算*/
int GetTop(SeqStack * S,StackElementType * x){//将S栈顶元素读出，放到x所指的存储空间中，栈顶指针保持不变
    if(S->top==-1) return 0;//栈为空
    *x = S->elem[S->top];//栈顶元素赋给x
    return 1;
}
/*顺序栈判空函数*/
int IsEmpty(SeqStack * S){//若S为空栈，则函数返回1，否则返回0
    return (S->top==-1 ? 1 : 0);
}

/*****************************************************/

typedef char DataType;
/*二叉树的二叉链表结点结构定义*/
typedef struct Node{//结点结构
    DataType data;//结点数据
    struct Node * LChild;//左孩子指针
    struct Node * RChild;//右孩子指针
}BiTNode, * BiTree;
/*用扩展先序遍历序列创建二叉链表*/
void CreateBiTree(BiTree * bt){//这边的bt是指针的指针
    char ch;
    ch = getchar();
    if(ch=='#') *bt = NULL;
    else{
        *bt = (BiTree)malloc(sizeof(BiTNode));//用(*bt)指针开辟结点空间
        (*bt)->data = ch;
        CreateBiTree( &( (*bt)->LChild  ) );
        CreateBiTree( &( (*bt)->RChild  ) );
    }
}


/*先序遍历二叉树的非递归算法（调用栈操作的函数）*/
void PreOrder(BiTree root){//先序遍历二叉树的非递归算法
    SeqStack S;//建栈
    InitStack(&S);//初始化栈
    BiTree p = root;//建立一个p指针拷贝root指针
    while(p!=NULL || !IsEmpty(&S)){//当p不为空，或者栈S不为空时进入循环
        if(p!=NULL){//如果p不为空指针，根指针进栈，访问根结点，遍历左子树
            Push(&S,p);
            printf("%c",p->data);
            p = p->LChild;
        }
        else{//如果p为空指针，根指针退栈，遍历右子树
            Pop(&S,&p);
            p = p->RChild;
        }
    }
}

/*中序遍历二叉树的非递归算法（调用栈操作的函数）*/
void InOrder(BiTree root){//中序遍历二叉树的非递归算法
    SeqStack S;//建栈
    InitStack(&S);//初始化栈
    BiTree p = root;//建立一个p指针拷贝root指针
    while(p!=NULL || !IsEmpty(&S)){//当p不为空，或者栈S不为空时进入循环
        if(p!=NULL){//如果p不为空指针，根指针进栈，遍历左子树
            Push(&S,p);
            p = p->LChild;
        }
        else{//如果p为空指针，根指针退栈，访问根结点，遍历右子树
            Pop(&S,&p);
            printf("%c",p->data);
            p = p->RChild;
        }
    }
}

/*后序遍历二叉树的非递归算法（调用栈操作的函数）*/
void PostOrder(BiTree root){//后序遍历二叉树的非递归算法
    BiTree p,q;//建立两个指针
    SeqStack S;//建栈
    q = NULL;//q指针置为空，用来记录刚访问过的结点
    p = root;//p指针拷贝root指针，用来记录当前正在访问的结点
    InitStack(&S);//初始化栈
    while(p!=NULL || !IsEmpty(&S)){//只要当前结点存在，或者栈不空，则重复下面操作
        if(p!=NULL){//从当前结点开始，进栈并遍历左子树，直到左子树为空
            Push(&S,p);
            p = p->LChild;
        }
        else{//当左子树为空时
            GetTop(&S,&p);//用p来存储栈顶结点
            if((p->RChild==NULL) || (p->RChild==q)){//栈顶结点的右子树为空，或者栈顶结点的右孩子为刚访问过的结点
                printf("%c",p->data);//输出当前栈顶结点
                q = p;//准备进行下一步，所以把q置为p
                Pop(&S,&p);//退栈
                p = NULL;//然后将当前结点指针置为空
            }
            else p = p->RChild;//否则，遍历右子树
        }
    }
}


int main()
{
    BiTree T;//开辟一个指向树的T指针
    CreateBiTree(&T);//传址建树
    PreOrder(T);//先序遍历二叉树的非递归算法（调用栈操作的函数）
    printf("\n");
    InOrder(T);//中序遍历二叉树的非递归算法（调用栈操作的函数）
    printf("\n");
    PostOrder(T);//后序遍历二叉树的非递归算法（调用栈操作的函数）
    return 0;
}

