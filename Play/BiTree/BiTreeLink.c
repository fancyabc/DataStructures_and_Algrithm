#include "string.h"
#include "stdio.h"    
#include "stdlib.h"  
#include <stdbool.h> 



#define MAXSIZE 100 /* 存储空间初始分配量 */


typedef char TElemType;
typedef char String[24];
String str = "ABDH#K###E##CFI###G#J##";

void StrAssign(String T, char * chars)
{

}

typedef struct BiNode
{
	TElemType data;
	struct BiNode *lchild,*rchild;
}BiTNode,*BiTree;


TElemType Nil='\0';

void visit(TElemType e)
{
	printf(" %c ",e);
}




void InitBiTree(BiTree *T)
{
	*T = NULL; 
}

/* 初始条件: 二叉树T存在。操作结果: 销毁二叉树T */
void DestroyBiTree(BiTree *T)
{ 
	if (*T)
	{
		if((*T)->lchild)
			DestroyBiTree(&(*T)->lchild);
		if((*T)->rchild)
			DestroyBiTree(&(*T)->rchild);
		
		free(*T);
		*T = NULL;
	}
}

int index1 = 0;
/* 按前序输入二叉树中结点的值（一个字符） */
/* #表示空树，构造二叉链表表示二叉树T。 */
void CreateBiTree(BiTree *T)
{
	
	TElemType ch;
	ch = str[index1++];

	if(ch == '#')
	{
		*T = NULL;
	}
	else
	{
		*T = (BiTree)malloc(sizeof(BiTNode));
		if(*T == NULL)
			exit(1);
		(*T)->data = ch;
		CreateBiTree(&(*T)->lchild);
		CreateBiTree(&(*T)->rchild);
	}
}


/* 初始条件: 二叉树T存在 */
/* 操作结果: 若T为空二叉树,则返回TRUE,否则FALSE */
bool BiTreeEmpty(BiTree T)
{
	return T == NULL;
}

#define ClearBiTree DestroyBiTree

/* 初始条件: 二叉树T存在。操作结果: 返回T的深度 */
int BiTreeDepth(BiTree T)
{
	if (!T)
		return 0;
	int LD,RD;
	LD = BiTreeDepth(T->lchild);
	RD = BiTreeDepth(T->rchild);
	return (LD >= RD ? LD : RD) + 1;
}


/* 初始条件: 二叉树T存在。操作结果: 返回T的根 */
TElemType Root(BiTree T)
{
	if (!T)
		return '\0';
	else
		return T->data;	
}


/* 初始条件: 二叉树T存在，p指向T中某个结点 */
/* 操作结果: 返回p所指结点的值 */
TElemType Value(BiTree p)
{
	return p->data;
}


/* 给p所指结点赋值为value */
void Assign(BiTree p,TElemType value)
{
	p->data = value;
}


/* 初始条件: 二叉树T存在 */
/* 操作结果: 前序递归遍历T */
void PreOrderTraverse(BiTree T)
{
	if(T)
	{
		visit(T->data);
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
}


/* 初始条件: 二叉树T存在 */
/* 操作结果: 中序递归遍历T */
void InOrderTraverse(BiTree T)
{
	if(T)
	{
		PreOrderTraverse(T->lchild);
		visit(T->data);
		PreOrderTraverse(T->rchild);
	}
}


/* 初始条件: 二叉树T存在 */
/* 操作结果: 后序递归遍历T */
void PostOrderTraverse(BiTree T)
{
	if(T)
	{
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
		visit(T->data);
	}
}


int main()
{
	int i;
	BiTree T;
	TElemType e1;
	InitBiTree(&T);

	StrAssign(str, "ABDH#K###E##CFI###G#J##");

	CreateBiTree(&T);
	printf("构造空二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
	e1=Root(T);
	printf("二叉树的根为： %c\n",e1);
		printf("\n前序遍历二叉树:");
	PreOrderTraverse(T);
	printf("\n中序遍历二叉树:");
	InOrderTraverse(T);
	printf("\n后序遍历二叉树:");
	PostOrderTraverse(T);

	ClearBiTree(&T);
	printf("\n清除二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));

	i=Root(T);
	if(!i)
		printf("树空，无根\n");

	return 0;
}




































