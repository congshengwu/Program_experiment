#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int create_key(string one_name, string *names, int hash_len, int p)
{
	//region 生成地址
	int adress, d = 0, d_len = 0;//d_len是伪随机数数组长度
	adress = (26 - ('z' - one_name[0])) + (26 - ('z' - one_name[one_name.length() - 1]));
	adress = adress % p;
	while (adress >= hash_len)//如果地址超出哈希表长
	{
		adress = adress - hash_len;
	}
	//endregion
	if (names[adress] == "")
	{
		names[adress] = one_name;
	} 
	else//处理冲突
	{
		while (names[adress] != "")
		{
			d = (d + p) % hash_len;//伪随机数发生器
			d_len++;
			if (adress + d > hash_len)
			{
				adress = adress + d - hash_len;
			}
			else
			{
				adress = adress + d;
			}
		}
		names[adress] = one_name;
	}
	return d_len;
}

string find_name(string one_name, string *name, int hash_len, int p, int d_len)
{
	int adress, d = 0;
	adress = (26 - ('z' - one_name[0])) + (26 - ('z' - one_name[one_name.length() - 1]));
	adress = adress % p;
	while (adress >= hash_len)
	{
		adress = adress - hash_len;
	}
	while (true)
	{
		if (name[adress] == one_name)
		{
			return name[adress];
		}
		else//产生冲突
		{
			d = (d + p) % hash_len;//伪随机数发生器
			d_len--;
			if (d_len < 0)
			{
				return "无";
			}
			if (adress + d > hash_len)
			{
				adress = adress + d - hash_len;
			}
			else
			{
				adress = adress + d;
			}
		}
	}
}

int main()
{
	int man_len;
	int p;//不大于hash_len的最大质数
	int d_len;
	cout << "请输入人数" << endl;
	cin >> man_len;
	int hash_len = man_len * 2;
	float R = man_len * 1.0 / hash_len;//装填因子
	float S = -1 / R * log(1 - R);//查找成功平均查找长度
	cout << "平均查找长度:" << S << endl;

	string *names = new string[hash_len];
	p = (hash_len / 2 == hash_len / 2.0) ? (hash_len - 1) : (hash_len - 2);
	
	cout << "请依次输入姓名:" << endl;
	for (int i = 0; i < man_len; i++)
	{
		string one_name;
		cin >> one_name;
		d_len = create_key(one_name, names, hash_len, p);
	}
	
	while (true)
	{
		cout << "哈希表创建成功,输入拼音姓名进行查询,按q退出" << endl;
		string input;
		cin >> input;
		if (input == "q" || input == "Q")
		{
			break;
		}//////********************************************************************************************************************
		cout << find_name(input, names, hash_len, p, d_len) << endl;
	}
	
	system("pause");
	return 0;
}
