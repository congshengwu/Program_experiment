#include "stdio.h"

int max(int a, int b);

int main()
{
	int a, b;
	printf("输入两个整数:\n");
	scanf("%d%d",&a, &b);
		
	printf("大的数为：%d", max(a, b));
	
	return 0;
}

//int存储大小是4个字节,一个字节大小为8bit,所以int是32位二进制数(最高位为符号位),右移31位即可得到符号位
//转成unsigned是因为其右移是逻辑右移
int max(int a, int b)
{
	int arr[]={a, b};
	int temp = a - b;
	return arr[(unsigned)temp >> sizeof(int) * 8 - 1];
}