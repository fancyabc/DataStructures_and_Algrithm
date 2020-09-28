#include <stdio.h>
#include <stdbool.h>


void bubble_sort(int arr[],int size)
{
	int i,j;
	for ( i = 0; i < size; i++)
	{
		for ( j = size - 1; j >= i; j--)
		{
			if (arr[j] > arr[j+1])
			{
				int tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;
			}
		}
	}
}

void bubble_sort2(int arr[],int size)
{
	int i,j;
	bool flag = true;
	for ( i = 0; i < size && flag; i++)
	{
		flag = false;
		for ( j = size -1; j >= i; j--)
		{
			if (arr[j] > arr[j+1])
			{
				int tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;
				flag = true;  //如果有数据交换，则flag为true
			}	
		}
	}
}

int main(void)
{
	int arr[]={3,6,1,9,4,2,0,5,8,7,17,12};
	int len=sizeof(arr)/sizeof(arr[0]);   //计算数组元素个数
	bubble_sort2(arr,len);
	int i=0;
	for(i=0;i<len;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
	return 0;
}