#include <stdio.h>
#define LeftChild(i) (2 * (i) + 1)
void swap(int *a,int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}


/* 调整大顶堆（建立在大顶堆已经构建的基础上） */
void HeapAdjust(int A[],int i,int N)
{
	int temp,Child;
	for(temp=A[i];LeftChild(i) < N;i=Child)  //i是 parent的序号数（数组下标）
	{	
		Child = LeftChild(i);      // 左孩子序数 2 * i + 1
		if(Child != N-1 && A[Child+1]>A[Child]) //如果左孩子结点小于右孩子结点，调整为指向右孩子
			Child++;
		if(temp<A[Child])  //如果子结点大于父节点，将子结点值赋给父节点
			A[i]=A[Child];
		else
			break;
	}
	A[i]=temp;  //将temp值放在最终位置
}

void HeapSort(int A[],int size)
{
	int i;
	for(i=size/2-1;i>=0;i--)  //构建一个最大堆
		HeapAdjust(A,i,size);
	for(i=size-1;i>0;i--)   //循环将堆首位与末位值交换，然后重新调整最大堆
	{
		swap(&A[0],&A[i]);    //“删除”最大值
		HeapAdjust(A,0,i);
	}
}

int main(void)
{
//	int arr[]={3,6,1,9,4,2,0,5,8,7,17,12};
	int arr[]={6};
	int len=sizeof(arr)/sizeof(arr[0]);   //计算数组元素个数
	HeapSort(arr,len);
	int i=0;
	for(i=0;i<len;i++){
		printf("%d ",arr[i]);
	}
	printf("\n");
	return 0;
}
