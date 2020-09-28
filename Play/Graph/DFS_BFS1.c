#include "stdio.h"
#include "stdlib.h"

#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE
#define MAXSIZE 100     //最大定点数，应由用户定义

typedef int Status;
typedef char VertexType;
typedef int EdgeType;    

typedef struct EdgeNode   //边表节点
{
	int adjvex;            //邻接点域，存储该顶点对应的下标
	EdgeType info;        //用于存储权值，对于非网图可以不需要
	struct EdgeNode *next;   //链域，指向下一个邻接点
}EdgeNode;


typedef struct VertexNode       //顶点表结构
{
	VertexType data;
	EdgeNode *firstedges;   //边表头指针
}VertexNode,AdjList[MAXVEX];


typedef struct
{
	AdjList AdjList;
	int numNodes,numEdges;
}GraphAdjList;




