//����ʵ�ַ�ʽ
#include "stdio.h"
#include "malloc.h"
typedef struct monkey
{
	int id;
	struct monkey *next;
	
} Monkey;

int find_king(Monkey *head, int m, int n);

int main()
{
	int m, n;
	int i;
	printf("������Ӹ���m��\n");
	scanf("%d", &m);
	printf("������������n(С�ں��Ӹ���)\n");
	scanf("%d", &n);
	
	//�����������Ա�
	Monkey *p = (Monkey *)malloc(sizeof(Monkey));
	p->id = 1;
	p->next = NULL;
	Monkey *head = p;
	Monkey *q = p;
	
	for(i = 0; i < m - 1; i++)
	{
		p = (Monkey *)malloc(sizeof(Monkey));
		p->id = i + 2;//��Ϊforѭ�������Ѿ�������idΪ1�ĺ���
		p->next = NULL;
		q->next = p;
		q = p;
	}
	p->next = head;
	
	printf("\n������%d�ź���", find_king(head, m ,n));
	return 0;
}

int find_king(Monkey *head, int m, int n)
{
	Monkey *p = head;
	int monkey_count = m;
	int i;
	if(n == 1)
	{
		for(i = 0; i < m - 1; i++)
		{
			p = p->next;
		}
		return p->id;
	}
	while(monkey_count != 1)
	{
		for(i = 0; i < n - 2; i++)//��һ������ҲҪ��,��ִ��p = p->next,�ҵ���̭���ӵ���һ������
		{
			p = p->next;
		}
		
		Monkey *temp = p->next;
		printf("��̭%d�ź���\n", temp->id);
		p->next = p->next->next;//��̭����
		free(temp);
		
		p = p->next;//��p�ƶ�����̭���ӵ���һ������,���ʣ������,�Ͳ������ƶ���
		
		monkey_count--;
	}
	return p->id;
}

