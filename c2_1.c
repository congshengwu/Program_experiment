//����ʵ�ַ�ʽ
#include "stdio.h"
int find_king(int arr[], int arr_len, int n);

int main()
{
	int m, n;
	int i;
	printf("������Ӹ���m��\n");
	scanf("%d", &m);
	//��������
	int arr[m];
	printf("������������n(С�ں��Ӹ���)\n");
	scanf("%d", &n);
	for(i = 0; i < m; i++)
	{
		arr[i] = i+1;
	}
	
	printf("\n�����ǣ�%d�ź���", find_king(arr, m, n));
	return 0;
}
//�ݹ�
int find_king(int arr[], int arr_len, int n)
{
	int i = 0, j = 0, out;//out�±��0��ʼ

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
	
	for(i = out + 1; i < arr_len + 1; i++)//������̭���Ӻ��沿��,���������
	{
		new_arr[j] = arr[i];
		j++;
	}
	
	for(i = 0; i < out; i++)//������̭����ǰ�沿��,��ӵ����������
	{
		new_arr[j] = arr[i];
		j++;
	}
	
	return arr_len == 1 ? new_arr[0] : find_king(new_arr, arr_len, n);
}