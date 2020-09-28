#include <stdio.h>

/* 对数组L做插入排序 */
void Insert_sort(int arr[],int size)
{
	int i,j,key;
	for ( i = 1; i < size; i++)
	{
		key = arr[i];   // 要插入的数
		j = i - 1;
		while (j >= 0 && arr[j] > key)   // j下标不超过数组左边界
		{
			arr[j+1] = arr[j];
			j = j -1;
		}
		arr[j+1] = key;
	}
	
}


void InsertionSort(int arr[],int size)
{
	int i,p;
	int tmp;
	for(p=1;p < size;p++)
	{
		tmp = arr[p];
		for ( i = p; i > 0 && arr[i-1] > tmp; i--)
		{
			arr[i] = arr[i-1];
		}
		arr[i] = tmp;
	}
}


int main(void)
{
	int arr[]={3,6,1,9,4,2,0,5,8,7,16,12,11,19,17};
//	int arr[] = {3,6,2};
	int len=sizeof(arr)/sizeof(arr[0]);
	Insert_sort(arr,len);
//	InsertionSort(arr,len);
	int i;
	for(i=0;i<len;i++){
		printf("%d ",arr[i]);
	}
	printf("\n");
	return 0;
}

