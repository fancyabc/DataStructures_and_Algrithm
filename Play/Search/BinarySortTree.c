#include "stdio.h"    
#include "stdlib.h"   

#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100 /* 存储空间初始分配量 */

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */

/*二叉查找树*/

/*二叉树的二叉链表节点结构定义*/
typedef struct BiTNode
{
	int data;
	struct BiTNode *lchild,*rchild;
} BiTNode, *BiTree;

/*递归查找二叉排序树T中是否存在key*/
/*指针f指向T的双亲，其初始调用值为NULL*/
/*若查找成功，则指针p指向该数据元素节点，并返回TRUE*/
/*否则指针p指向查找路径上访问的最后一个节点并返回FALSE*/
Status SearchBST(BiTree T,int key,BiTree f,BiTree *p)
{
	if(!T){      /*  查找不成功 */
		*p=f;
		return FALSE;
	}
	else if(key==T->data){   /*  查找成功 */
		*p=T;
		return TRUE;
	}
	else if(key<T->data)
		return SearchBST(T->lchild, key, T, p);
	else
		return SearchBST(T->rchild, key, T, p);
}



/*二叉排序树插入操作*/
Status InsertBST(BiTree *T,int key)
{
	BiTree p,s;
	if(!SearchBST(*T, key, NULL, &p)){
		s=(BiTree)malloc(sizeof(BiTNode));
		s->data=key;
		s->lchild=s->rchild=NULL;
		if(!p)
			*T=s;         //插入s为新的根节点
		else if(key<p->data)
			p->lchild=s;    //插入s为左孩子
		else
			p->rchild=s;   //插入s为右孩子
		return TRUE;
	}
	else
		return FALSE;
}


Status Delete(BiTree *p)
{
	BiTree q,s;
	if((*p)->rchild==NULL){
		q=*p;
		*p=(*p)->lchild;
		free(q);
	}
	else if((*p)->lchild==NULL){
		q=*p;
		*p=(*p)->rchild;
		free(q);
	}
	else{
		q=*p;
		s=(*p)->lchild;
		while(s->rchild){
			q=s;             //q 指向删除点左子树最右一个元素的父节点
			s=s->rchild;     //s指向左子树的最后一个元素（删除点的前节点） 
		}                             
		(*p)->data=s->data;    //所删除节点值用前一节点的值替换
		if(q!=*p)
			q->rchild=s->lchild;
		else
			q->lchild=s->lchild;
		free(s);
	}
	return TRUE;
}


/*二叉排序树删除操作*/
Status DeleteBST(BiTree *T,int key)
{
	if(!*T)    //不存在关键字等于key的数据元素
		return FALSE;
	else{
		if(key==(*T)->data)
			return Delete(T);
		else if(key<(*T)->data)
			return DeleteBST(&(*T)->lchild,key);
		else
			return DeleteBST(&(*T)->rchild,key);
	}
		
}





int main(void)
{    
	int i;
	int a[10]={62,88,58,47,35,73,51,99,37,93};
	BiTree T=NULL;   //
	
	for(i=0;i<10;i++)
	{
		InsertBST(&T, a[i]);
	}
	DeleteBST(&T,93);
	DeleteBST(&T,47);
    printf("本样例建议断点跟踪查看二叉排序树结构");
	return 0;
}