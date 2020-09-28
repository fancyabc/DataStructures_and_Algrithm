#include <stdio.h>

void swap(int *a,int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void select_sort(int arr[],int size)
{
	int i,j,min;
	for(i=0;i<size;i++)
	{
		min=i;     //将当前下标设为最小值下标
		for(j=i+1;j<=size;j++)  //循环之后的数据
		{
			if(arr[min]>arr[j]) //如果有小于当前最小值的关键字
				min=j;    //将此关键字的下标值赋给min
		}
		if(i!=min)                //若min不等于i，说明找到最小值，交换
			swap(&arr[i],&arr[min]);		
	}	
}


int main(void)
{
	int arr[]={3,6,1,9,4,2,0,5,8,7,16,12,11};
	int len=sizeof(arr)/sizeof(arr[0]);
	select_sort(arr,len);
	int i=0;
	for(i=0;i<len;i++){
		printf("%d ",arr[i]);
	}
	printf("\n");
	return 0;
}

