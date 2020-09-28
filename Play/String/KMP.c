#include "string.h"
#include "stdio.h"    
#include "stdlib.h"  



/*计算next数组值*/
void getNext(char * t, int * next)   
{
	next[0] = -1;
	int i = 0, j = -1;

	while (i < strlen(t))
	{
		if (j == -1 || t[i] == t[j])
		{
			++i;
			++j;
			next[i] = j;
		}	
		else
			j = next[j];
	}
}


/**/
int KMP(char * s, char * t) 
{
	int i = 0; 
	int j = 0;
	int next[255];
	getNext(s,next);
	while (i < strlen(s) && j < strlen(t))
	{
		if (j == -1 || s[i] == t[j]) 
		{
			i++;
           	j++;
		}
	 	else 
           	j = next[j];
    	}

    if (j == strlen(t))
       return i - j;
    else 
       return -1;
}


void main()
{	int pos;
	char * s = "abababababababca";
	char * t = "abababca";
	pos = KMP(s, t);
	printf("%d",pos);
}