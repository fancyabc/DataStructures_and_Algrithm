#include "stdio.h"    
#include "stdlib.h"  
#include <stdbool.h> 

#include "math.h"  
#include "time.h"

#define MAXSIZE 100 /* 存储空间初始分配量 */


/* 二叉树的二叉链表节点结构定义 */
typedef struct BiTNode
{
	int data;
	int bf;
	struct BiNode *lchild, *rchild;
} BiTNode, *BiTree;

/* 对以p为根的二叉树做  右旋处理   */
/* 处理之后p指向新的树根结点，即旋转处理之前的左子树的根节点 */
void R_Rotate(BiTree *P)
{
	BiTree L;
	L = (*P)->lchild;         // L指向P的左子树的节点
	(*P)->lchild = L->rchild;    // L的 右子树挂接为P的左子树
	L->rchild = *P;
	*P = L;		// P指向新的根节点
}


/* 对以p为根的二叉树做  左旋处理   */
/* 处理之后p指向新的树根结点，即旋转处理之前的右子树的根节点 */
void L_Rotate(BiTree *P)
{
	BiTree R;
	R = (*P)->rchild;	//R指向左子树节点
	(*P)->rchild = R->lchild;	//R的左子树挂接为P的右子树
	R->lchild = *P;
	*P = R;	// P指向新的节点
}


#define LH +1   //左子树高
#define EH 0	//等高
#define RH -1	// 右子树高

/*  对以指针T所指结点为根的二叉树作左平衡旋转处理 */
/*  本算法结束时，指针T指向新的根结点 */
void LeftBalance(BiTree *T)
{
	
	BiTree L,Lr;
	L = (*T)->lchild;   //L指向T的左子树根节点
	switch (L->bf)	
	{			// 检查T的左子树的平衡度，并作相应平衡处理
	case LH:	//新节点插入在T的左孩子的左子树上，要做单右旋处理
		(*T)->bf = L->bf = EH;
		R_Rotate(T);
		break;
	case RH:	// (此时，他的值和T符号相反)新节点插入在T的左孩子的右子树上，要作双旋处理
		Lr = L->rchild;		//Lr指向T的左孩子的右子树根
		switch (Lr->bf)
		{		// 修改T及其左孩子的平衡因子
			case LH:
				(*T)->bf = RH;
				L->bf = EH;
				break;
			case EH:
				(*T)->bf = L->bf = EH;
				break;
			case RH:
				(*T)->bf = EH;
				L->bf = LH;
				break;
		}
		Lr->bf = EH;
		L_Rotate(&(*T)->lchild);	//对T的左子树作为左旋平衡处理
		R_Rotate(T);		// 对T做平衡处理
	}
}


/*  对以指针T所指结点为根的二叉树作右平衡旋转处理， */ 
/*  本算法结束时，指针T指向新的根结点 */ 
void RightBalance(BiTree *T)
{	
	BiTree R,Rl;
	R = (*T)->rchild;
	switch (R->bf)
	{//检查T的右子树的平衡度，并作相应平衡处理
	case RH:	//新节点插入在T的右孩子的右子树上，要做单左旋处理
		(*T)->bf = R->bf = EH;
		L_Rotate(T);
		break;
	
	case LH:	//新节点插入在T的右孩子的左子树上，要做双旋处理
		Rl = R->lchild;
		switch(Rl->bf)
		{	// 修改T及右孩子的平衡因子
			case RH:
				(*T)->bf = LH;
				R->bf = EH;
				break;
			case EH:
				(*T)->bf = R->bf = EH;
				break;
			case LH:
				(*T)->bf = EH;
				R->bf = RH;
				break;
		}
		Rl->bf = EH;
		R_Rotate(&(*T)->rchild);
		L_Rotate(T);
	}
}




/*  若在平衡的二叉排序树T中不存在和e有相同关键字的结点，则插入一个 */ 
/*  数据元素为e的新结点，并返回1，否则返回0。若因插入而使二叉排序树 */ 
/*  失去平衡，则作平衡旋转处理，布尔变量taller反映T长高与否。 */
bool InsertAVL(BiTree *T,int e, bool *taller)
{
	if (!*T)
	{
		// 插入新节点，树长高，置 taller为true
		*T = malloc(sizeof( BiTNode ));
		(*T)->data = e;
		(*T)->lchild = (*T)->rchild = NULL;
		(*T)->bf = EH;
	}
	else
	{
		if (e == (*T)->data)
		{
			// 树中已存在和e相同的关键字的节点则不再插入
			*taller = false;
			return false;
		}
		if (e < (*T)->data)
		{
			//应继续在T的左子树中进行搜索
			if(!InsertAVL(&(*T)->lchild, e, taller))	//未插入
				return false;
			if (*taller)	// 已插入到T的左子树中且左子树“长高”
			{
				switch((*T)->bf)	//检查T的平衡度
				{
					case LH:	// 原本左子树比右子树高，需要做左平衡处理
						LeftBalance(T);
						*taller = false;
						break;
					case EH:	// 原本左右子树等高，因左子树增高而使树增高
						(*T)->bf = LH;
						*taller = true;
						break;
					case RH:	// 原本右子树比左子树高，现在，左右树等高
						(*T)->bf = EH;
						*taller = false;
						break;
				}
			}
			
		}
		else
		{
			if(!InsertAVL(&(*T)->rchild, e, taller))
				return false;
			if (*taller)
			{
				switch((*T)->bf)
				{
					case LH:
						(*T)->bf = EH;
						*taller = false;
						break;
					case EH:
						(*T)->bf = RH;
						*taller = true;
						break;
					case RH:
						
						RightBalance(T);
						*taller = false;
						break;
				}
			}	
		}	
	}
	return true;
}


int main(void)
{
	int i;
	int a[10]={3,2,1,4,5,6,7,10,9,8};
	BiTree T=NULL;
	bool taller;
	for(i=0;i<10;i++)
		InsertAVL(&T,a[i],&taller);
	return 0;
}

