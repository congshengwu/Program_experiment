#include "stdio.h"

void switch_figure(int *a, int *b);

int main()
{
	int a = 100, b = 50;
	printf("交换前：a=%d,b=%d\n", a, b);
	
	switch_figure(&a, &b);
	
	printf("交换后：a=%d,b=%d", a, b);
	return 0;
}

void switch_figure(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}



