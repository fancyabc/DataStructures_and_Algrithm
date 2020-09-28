#include <stdio.h>
#include <stdlib.h>

/*	算法描述：
	1.把长度为n的输入序列分成长度为n/2的两个序列
	2.对这两个子序列分别采取归并排序
	3.将两个排序好的子序列合并成一个最终的排序序列
*/



/* Lpos = start of left half, Rpos = start of right half */
void Merge( int A[ ], int TmpArray[ ],int Lpos, int Rpos, int RightEnd )
{
	int i, LeftEnd, NumElements, TmpPos;

	LeftEnd = Rpos - 1;   
	TmpPos = Lpos;        
	NumElements = RightEnd - Lpos + 1;

	/* main loop */
	while( Lpos<=LeftEnd && Rpos<=RightEnd )
		if( A[Lpos]<=A[Rpos] )
			TmpArray[TmpPos++]=A[Lpos++];
		else
			TmpArray[TmpPos++]=A[Rpos++];

	while( Lpos<=LeftEnd )  			/* Copy rest of first half */
		TmpArray[TmpPos++]=A[Lpos++];
	while( Rpos <= RightEnd ) 			/* Copy rest of second half */
		TmpArray[TmpPos++]=A[Rpos++];

	/* Copy TmpArray back */
	for( i = 0; i < NumElements; i++, RightEnd-- )
		A[ RightEnd ] = TmpArray[ RightEnd ];
}


/*   */
void MSort(int A[],int TmpArray[],int L,int R)
{
	int mid;
	if(L<R)
	{
		mid = (L + R)/2;
		MSort(A, TmpArray, L, mid);
		MSort(A, TmpArray, mid+1, R);  // 
		Merge(A, TmpArray,L, mid+1, R);  // 
	}
}

void merge_sort(int A[],int size)
{
	int *temp_arr;
	temp_arr=malloc(size * sizeof(int));
	if(temp_arr != NULL)
	{
		MSort(A,temp_arr,0,size-1);
		free(temp_arr);
	}
	else
	{
		printf( "No space for tmp array!!!" );
		exit(0);
	}
		
}







int main(void)
{
	int arr[]={3,6,1,9,4,2,0,5,8,7,16,12,11,17,21,13};
	int len=sizeof(arr)/sizeof(arr[0]);
	merge_sort(arr,len);
	int i;
	for(i=0;i<len;i++){
		printf("%d ",arr[i]);
	}
	printf("\n");
	return 0;
}


