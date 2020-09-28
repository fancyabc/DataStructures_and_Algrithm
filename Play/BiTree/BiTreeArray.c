#include "stdio.h"
#include "stdlib.h"
#include <stdbool.h>
#include <math.h>


#define MAXSIZE 100
#define MAX_TREE_SIZE 100


typedef char TElemType;
typedef TElemType SqBiTree[MAX_TREE_SIZE];

typedef struct{
	int level;    // 层数
	int order;    // 节点所在本层序号
}Position;   //节点所在位置

void visit(TElemType c)
{
	printf(" %c ",c);
}


/*构造空二叉树*/
void InitBiTree(SqBiTree T)
{
	int i;

	for(i = 0; i < MAX_TREE_SIZE;i++)
	{
		T[i] = '\0';     // 空树无节点，以字符‘\0’填充
	}
}


bool CreateBiTree(SqBiTree T)
{ 
	int i=0;
 	printf("请按层序输入结点的值(整型)，0表示空结点，输999结束。结点数≤%d:\n",MAX_TREE_SIZE);
	while(i<10)
	{
		T[i]='A'+i;
		
		if(i!=0&&T[(i+1)/2-1]=='\0'&&T[i]!='\0') /* 此结点(不空)无双亲且不是根 */
		{
			printf("出现无双亲的非根结点%d\n",T[i]);
			exit(1);
		}
		i++;
	}
	while(i<MAX_TREE_SIZE)
	{
		T[i]='\0'; /* 将空赋值给T的后面的结点 */
		i++;
	}

	return true;
}

void ClearBiTree(SqBiTree T) /* 在顺序存储结构中，两函数完全一样 */
{
	InitBiTree(T);
}

/* 初始条件: 二叉树T存在 */
/* 操作结果: 若T为空二叉树,则返回TRUE,否则FALSE */
bool BiTreeEmpty(SqBiTree T)
{ 
	return T[0] == '\0'; 
}


/* 初始条件: 二叉树T存在。操作结果: 返回T的深度 */
int BiTreeDepth(SqBiTree T)
{
	int level = 0;
	int i;
	for(i = MAX_TREE_SIZE -1; i>=0;i--)    // 找到最后一个节点
	{
		if( T[i] != '\0')
			break;
	}
	while((int)pow(2,level) -1 < i)   // level层的二叉树最多有 pow(2,level)个节点
	{
		level++;
	}
	return level;
}


/* 初始条件: 二叉树T存在 */
/* 操作结果:  当T不空,用e返回T的根,返回OK;否则返回ERROR,e无定义 */
bool Root(SqBiTree T,TElemType *e)
{ 
	if(BiTreeEmpty(T))
		return false;
	*e = T[0];
	return true;
}


/* 初始条件: 二叉树T存在,e是T中某个结点(的位置) */
/* 操作结果: 返回处于位置e(层,本层序号)的结点的值 */
TElemType Value(SqBiTree T,Position e)
{ 
	int res = (int)pow(2,e.level -1) + e.order - 2;	// level的树最多有pow(2,e.level) -1个节点
	return res;
}


/* 初始条件: 二叉树T存在,e是T中某个结点(的位置) */
/* 操作结果: 给处于位置e(层,本层序号)的结点赋新值value */
bool Assign(SqBiTree T,Position e,TElemType value)
{ 
	int i = pow(2,e.level -1)+ e.order -2;
	if(value == '\0' && (T[2*i+1] != '\0' || T[2*i+2]!= '\0'))  // 赋值位置的值 和 左右孩子均为 '\0'
		return false;
	else if(value != '\0' && T[(i+1)/2 -1] == '\0')    // 赋值的节点为空且父节点也为空
		return false;
	else
		T[i] = value;
	return true;
}


/* 初始条件: 二叉树T存在,e是T中某个结点 */
/* 操作结果: 若e是T的非根结点,则返回它的双亲,否则返回＂空＂ */
TElemType Parent(SqBiTree T,TElemType e)
{ 
	int i;
	if(T[0] != '\0')
	{
		for ( i = 0; i < MAX_TREE_SIZE; i++)
		{
			if (T[i] == e)
			{
				return T[(i+1)/2-1];   
			}
			
		}
		
	}
	return '\0';
}


/* 初始条件: 二叉树T存在,e是T中某个结点 */
/* 操作结果: 返回e的左孩子。若e无左孩子,则返回＂空＂ */
TElemType LeftChild(SqBiTree T,TElemType e)
{ 
	int i;
	if(T[0] != '\0')
	{
		for ( i = 0; i < MAX_TREE_SIZE; i++)
		{
			if (T[i] == e)
			{
				return T[2*i+1];   
			}
		}
	}
	return '\0';	
}


/* 初始条件: 二叉树T存在,e是T中某个结点 */
/* 操作结果: 返回e的右孩子。若e无右孩子,则返回＂空＂ */
TElemType RightChild(SqBiTree T,TElemType e)
{ 
	int i;
	if(T[0] != '\0')
	{
		for ( i = 0; i < MAX_TREE_SIZE; i++)
		{
			if (T[i] == e)
			{
				return T[2*i +2];   
			}
		}
	}
	return '\0';	
}


/* 初始条件: 二叉树T存在,e是T中某个结点 */
/* 操作结果: 返回e的左兄弟。若e是T的左孩子或无左兄弟,则返回＂空＂ */
TElemType LeftSibling(SqBiTree T,TElemType e)
{ 
	int i;
	if(T[0] == '\0')   // 空树的话，不用继续了
		return '\0';
	for(i = 0; i < MAX_TREE_SIZE;i++)
	{
		if(i%2 == 0 && T[i] == e)   // i偶序数，此时自己是右侧节点
		{
			return T[i-1];
		}
	}
	return '\0';   // 未找到e
}


/* 初始条件: 二叉树T存在,e是T中某个结点 */
/* 操作结果: 返回e的右兄弟。若e是T的右孩子或无右兄弟,则返回＂空＂ */
TElemType RightSibling(SqBiTree T,TElemType e)
{ 
	int i;
	if(T[0] == '\0')   // 空树的话，不用继续了
		return '\0';
	for(i = 0; i < MAX_TREE_SIZE;i++)
	{
		if(i%2 == 1 && T[i] == e)   // i奇序数，此时自己是左侧节点
		{
			return T[i+1];
		}
	}
	return '\0';	// 未找到e
}





/* 初始条件: 二叉树存在 */
/* 操作结果: 先序遍历T。 */
void PreOrderTraverse(SqBiTree T, void(visit)(TElemType), int i)
{ 
	if (T[i] != '\0')
	{
		visit(T[i]);
		PreOrderTraverse(T,visit, 2*i+1);
		PreOrderTraverse(T,visit, 2*i+2);
	}
}


/* 初始条件: 二叉树存在 */
/* 操作结果: 中序遍历T。 */
void InOrderTraverse(SqBiTree T, void(visit)(TElemType), int i)
{ 
	if (T[i] != '\0')
	{
		InOrderTraverse(T,visit, 2*i+1);
		visit(T[i]);
		InOrderTraverse(T,visit, 2*i+2);
	}	
}

/* 初始条件: 二叉树T存在 */
/* 操作结果: 后序遍历T。 */
void PostOrderTraverse(SqBiTree T, void(visit)(TElemType), int i)
{ 
	if (T[i] != '\0')
	{
		PostOrderTraverse(T,visit, 2*i+1);
		PostOrderTraverse(T,visit, 2*i+2);
		visit(T[i]);
	}	
}


void LevelOrderTraverse(SqBiTree T)
{
	int i;
	int len;
	for ( len = MAX_TREE_SIZE; len >=0; len--)
	{
		if(T[len] != '\0')
			break;
	}
//	len = i;

	for(i=0;i < len+1;i++)
		visit(T[i]);
	printf("\n");
}


int main()
{
	bool i;
	Position p;
	TElemType e;
	SqBiTree T;
	InitBiTree(T);
	CreateBiTree(T);
	
	printf("建立二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
	i=Root(T,&e);
	if(i)
		printf("二叉树的根为：%c\n",e);
	else
		printf("树空，无根\n");
	printf("层序遍历二叉树:\n");
	LevelOrderTraverse(T);
	printf("前序遍历二叉树:\n");
	PreOrderTraverse(T,visit,0);
	printf("中序遍历二叉树:\n");
	InOrderTraverse(T,visit,0);
	printf("后序遍历二叉树:\n");
	PostOrderTraverse(T,visit,0);
	printf("修改结点的层号3本层序号2。");
	p.level=3;
	p.order=2;
	e=Value(T,p);
	printf("待修改结点的原值为%d请输入新值:50 ",e);
	e=50;
	Assign(T,p,e);
	printf("前序遍历二叉树:\n");
	PreOrderTraverse(T,visit,0);
	printf("结点%d的双亲为%d,左右孩子分别为",e,Parent(T,e));
	printf("%d,%d,左右兄弟分别为",LeftChild(T,e),RightChild(T,e));
	printf("%d,%d\n",LeftSibling(T,e),RightSibling(T,e));
	ClearBiTree(T);
	printf("清除二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
	i=Root(T,&e);
	if(i)
		printf("二叉树的根为：%d\n",e);
	else
		printf("树空，无根\n");
	
	return 0;
}

















































































