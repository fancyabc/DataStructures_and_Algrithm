#include<stdio.h>

int Fib(int n)
{
	if(n<2)
		return n == 0 ? 0 : 1;
	return Fib(n-1)+Fib(n-2);
}


int main()
{
	int i;
	for(i=0;i<40;i++)
		printf("%d ",Fib(i));
	return 0;
}