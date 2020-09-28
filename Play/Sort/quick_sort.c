#include <stdio.h>

int Partition(int A[],int low, int high);

void swap(int *a,int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}




void QSort(int A[],int low, int high)
{
	int pivot;
	if(low<high)
	{
		pivot=Partition(A,low,high);  //将A[]分为两份，算出枢轴值
		QSort(A, low, pivot-1);
		QSort(A, pivot+1, high);
	}
}

int Partition(int A[],int low, int high)
{
	int pivotkey;
	pivotkey=A[low];   //用子表的第一个记录作枢轴记录
	while(low<high)    //从表两侧交替向中间扫描
	{
		while(low<high && A[high]>=pivotkey)
			high--;
		swap(&A[low],&A[high]);  //将比枢轴记录小的记录交换到低端
		while(low<high && A[low]<=pivotkey)
			low++;
		swap(&A[low],&A[high]);  //将比枢轴记录大的记录交换到高端
	}
	return low;     //返回枢轴所在位置
}

void QuicK_sort(int A[],int size)
{
	QSort(A,0,size-1);
}


int main(void)
{
	int arr[]={3,6,1,9,4,2,0,5,8,7,17,12};
	int len=sizeof(arr)/sizeof(arr[0]);   //计算数组元素个数
	QuicK_sort(arr,len);
	int i=0;
	for(i=0;i<len;i++){
		printf("%d ",arr[i]);
	}
	printf("\n");
	return 0;
}


