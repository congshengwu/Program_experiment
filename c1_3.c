#include "stdio.h"

int main()
{
	int a = 20, b = 6;
	printf("����ǰ��a=%d,b=%d", a, b);
	a = a^b;
	b = a^b;
	a = a^b;
	printf("\n");
	printf("������a=%d,b=%d", a, b);
	
	return 0;
}

