#include "stdio.h"

int main()
{
	int a = 20, b = 6;
	printf("交换前：a=%d,b=%d", a, b);
	a = a^b;
	b = a^b;
	a = a^b;
	printf("\n");
	printf("交换后：a=%d,b=%d", a, b);
	
	return 0;
}

