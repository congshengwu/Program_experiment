//数组实现方式
#include "stdio.h"
int find_king(int arr[], int arr_len, int n);

int main()
{
	int m, n;
	int i;
	printf("输入猴子个数m：\n");
	scanf("%d", &m);
	//猴子数组
	int arr[m];
	printf("输入数猴子数n(小于猴子个数)\n");
	scanf("%d", &n);
	for(i = 0; i < m; i++)
	{
		arr[i] = i+1;
	}
	
	printf("\n猴王是：%d号猴子", find_king(arr, m, n));
	return 0;
}
//递归
int find_king(int arr[], int arr_len, int n)
{
	int i = 0, j = 0, out;//out下标从0开始

	if(arr_len - n >= 0)
	{
		out = n - 1;
	}
	else
	{
		out = n - arr_len - 1;
		while(out > arr_len - 1)
		{
			out = out - arr_len - 1;
		}
	}
	
	arr_len--;
	int new_arr[arr_len];
	
	for(i = out + 1; i < arr_len + 1; i++)//遍历淘汰猴子后面部分,组成新数组
	{
		new_arr[j] = arr[i];
		j++;
	}
	
	for(i = 0; i < out; i++)//遍历淘汰猴子前面部分,添加到新数组后面
	{
		new_arr[j] = arr[i];
		j++;
	}
	
	return arr_len == 1 ? new_arr[0] : find_king(new_arr, arr_len, n);
}