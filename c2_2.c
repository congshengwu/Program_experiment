//链表实现方式
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
	printf("输入猴子个数m：\n");
	scanf("%d", &m);
	printf("输入数猴子数n(小于猴子个数)\n");
	scanf("%d", &n);
	
	//创建猴子线性表
	Monkey *p = (Monkey *)malloc(sizeof(Monkey));
	p->id = 1;
	p->next = NULL;
	Monkey *head = p;
	Monkey *q = p;
	
	for(i = 0; i < m - 1; i++)
	{
		p = (Monkey *)malloc(sizeof(Monkey));
		p->id = i + 2;//因为for循环上面已经创建了id为1的猴子
		p->next = NULL;
		q->next = p;
		q = p;
	}
	p->next = head;
	
	printf("\n猴王是%d号猴子", find_king(head, m ,n));
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
		for(i = 0; i < n - 2; i++)//第一个猴子也要数,不执行p = p->next,找到淘汰猴子的上一个猴子
		{
			p = p->next;
		}
		
		Monkey *temp = p->next;
		printf("淘汰%d号猴子\n", temp->id);
		p->next = p->next->next;//淘汰猴子
		free(temp);
		
		p = p->next;//将p移动到淘汰猴子的下一个猴子,如果剩俩猴子,就不用再移动了
		
		monkey_count--;
	}
	return p->id;
}

