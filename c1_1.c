#include "stdio.h"

int max(int a, int b);

int main()
{
	int a, b;
	printf("������������:\n");
	scanf("%d%d",&a, &b);
		
	printf("�����Ϊ��%d", max(a, b));
	
	return 0;
}

//int�洢��С��4���ֽ�,һ���ֽڴ�СΪ8bit,����int��32λ��������(���λΪ����λ),����31λ���ɵõ�����λ
//ת��unsigned����Ϊ���������߼�����
int max(int a, int b)
{
	int arr[]={a, b};
	int temp = a - b;
	return arr[(unsigned)temp >> sizeof(int) * 8 - 1];
}