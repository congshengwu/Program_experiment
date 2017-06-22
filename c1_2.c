#include "stdio.h"
int main()
{
	int a = 25, b = 99, c = 10;
	int meduim;
	
	if(a > b && a > c)
	{
		meduim = b > c ? b : c;
	}
	else if(a < b && a < c)
	{
		meduim = b < c ? b : c;
	}
	else
	{
		meduim = a;
	}
	
	printf("中间数为：%d", meduim);
	
	return 0;
}