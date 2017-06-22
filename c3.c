#include "stdio.h"

int main()
{
	int arr[10];
	int i, j;
	printf("输入10个数排序\n");
	for(i = 0; i < 10; i++)
	{
		scanf("%d", &arr[i]);
	}
	
	for(j = 0; j < 9; j++)//外层控制循环次数
	{
		for(i = 0; i < 9 - j; i++)
		{
			if(arr[i] >= arr[i+1])
			{
				int temp = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = temp;
			}
		}
	}
	
	for(i = 0; i < 10; i++)
	{
		printf("%d  ", arr[i]);
	}
	
	return 0;
}