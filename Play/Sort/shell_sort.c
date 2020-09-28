#include <stdio.h>


/* 对数组arr做shell排序 */
void Shell_sort(int arr[],int size)
{
	int i,j,Increment;
	int temp;

	for(Increment=size/2;Increment >0;Increment /=2)  //选择增量序列
		for(i=Increment;i<size;i++)  //进行插入排序
		{
			temp=arr[i];
			for(j=i;j>=Increment;j-=Increment)
				if(temp<arr[j-Increment])
					arr[j]=arr[j - Increment];
				else
					break;
			arr[j]=temp;
		}
}



int main(void)
{
	int arr[]={3,6,1,9,4,2,0,5,8,7,16,12,11};
	int len=sizeof(arr)/sizeof(arr[0]);
	Shell_sort(arr,len);
	int i;
	for(i=0;i<len;i++){
		printf("%d ",arr[i]);
	}
	printf("\n");
	return 0;
}


