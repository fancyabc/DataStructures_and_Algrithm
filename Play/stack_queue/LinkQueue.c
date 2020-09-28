#include "stdio.h"    
#include "stdlib.h"   

#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status; 

typedef int QElemType; /* QElemType类型根据实际情况而定，这里假设为int */

typedef struct QNode	/* 结点结构 */
{
   QElemType data;
   struct QNode *next;
}QNode,*QueuePtr;

typedef struct			/* 队列的链表结构 */
{
   QueuePtr front,rear; /* 队头、队尾指针 */
}LinkQueue;

Status visit(QElemType c)
{
	printf("%d ",c);
	return OK;
}


/* 构造一个空队列Q */
Status InitQueue(LinkQueue *Q)
{ 
	Q->front=Q->rear=(QueuePtr)malloc(sizeof(QNode));
	if(!Q->front)
		exit(1);;
	Q->front->next=NULL;
	return OK;
}

/* 销毁队列Q */
/*链队列，释放的时候一个个得释放，因此需要通过循环来实现，
具体为while和内部的语句，本质就是用front和rear指针交替往后移动进行释放。*/
Status DestroyQueue(LinkQueue *Q)
{
	while(Q->front)      //队列的队首节点，不为NULL时执行循环
	{
		 Q->rear=Q->front->next;   //rear指向离队首最近的节点。
		 free(Q->front);    //释放队首的节点所在内存单元
		 Q->front=Q->rear;   //现在front和rear都指向离原来队首最近的节点
	}
	return OK;
}

/* 将Q清为空队列 */
Status ClearQueue(LinkQueue *Q)
{
	QueuePtr p,q;
	Q->rear=Q->front;   //Q为空队列
	p=Q->front->next;   //p指向队头的节点
	Q->front->next=NULL;   //头节点
	while(p)     //释放节点
	{
		 q=p;
		 p=p->next;
		 free(q);
	}
	return OK;
}

/* 若Q为空队列,则返回TRUE,否则返回FALSE */
Status QueueEmpty(LinkQueue Q)
{ 
	if(Q.front==Q.rear)
		return TRUE;
	else
		return FALSE;
}

/* 求队列的长度 */
int QueueLength(LinkQueue Q)
{ 
	int i=0;
	QueuePtr p;
	p=Q.front;
	while(Q.rear!=p)
	{
		 i++;
		 p=p->next;
	}
	return i;
}

/* 若队列不空,则用e返回Q的队头元素,并返回OK,否则返回ERROR */
Status GetHead(LinkQueue Q,QElemType *e)
{ 
	QueuePtr p;
	if(Q.front==Q.rear)
		return ERROR;
	p=Q.front->next;
	*e=p->data;
	return OK;
}

/*插入元素e为Q的队尾元素*/
Status EnQueue(LinkQueue *Q,QElemType e)
{
	QueuePtr s=(QueuePtr)malloc(sizeof(QNode));
	if(!s)
		return ERROR;
	s->data = e;
	s->next = NULL;
	Q->rear->next = s;
	Q->rear = s;
	return OK;
}


Status DeQueue(LinkQueue *Q,QElemType *e)
{
	QueuePtr p;
	if(Q->front==Q->rear)   //队列空
		return ERROR;
	p = Q->front->next;    //将欲删除的节点暂存给p
	*e = p->data;
	Q->front->next = p->next;  //将原队头节点后继赋值给头节点后继
	
	if(Q->rear==p)   //若队头是队尾，则删除后将rear指向头节点
		Q->rear=Q->front;
	free(p);
	return OK;
}


/* 从队头到队尾依次对队列Q中每个元素输出 */
Status QueueTraverse(LinkQueue Q)
{
	QueuePtr p;
	p=Q.front->next;
	while(p)
	{
		 visit(p->data);
		 p=p->next;
	}
	printf("\n");
	return OK;
}

int main()
{
	int i;
	QElemType d;
	LinkQueue q;
	i=InitQueue(&q);
	if(i)
		printf("成功地构造了一个空队列!\n");
	printf("是否空队列？%d(1:空 0:否)  ",QueueEmpty(q));
	printf("队列的长度为%d\n",QueueLength(q));
	EnQueue(&q,-5);
	EnQueue(&q,5);
	EnQueue(&q,10);
	printf("插入3个元素(-5,5,10)后,队列的长度为%d\n",QueueLength(q));
	printf("是否空队列？%d(1:空 0:否)  ",QueueEmpty(q));
	printf("队列的元素依次为：");
	QueueTraverse(q);
	i=GetHead(q,&d);
	if(i==OK)
	 printf("队头元素是：%d\n",d);
	DeQueue(&q,&d);
	printf("删除了队头元素%d\n",d);
	i=GetHead(q,&d);
	if(i==OK)
		printf("新的队头元素是：%d\n",d);
	ClearQueue(&q);
	printf("清空队列后,q.front=%u q.rear=%u q.front->next=%u\n",q.front,q.rear,q.front->next);
	DestroyQueue(&q);
	printf("销毁队列后,q.front=%u q.rear=%u\n",q.front, q.rear);
	
	return 0;
}

