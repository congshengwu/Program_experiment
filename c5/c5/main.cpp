#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int create_key(string one_name, string *names, int hash_len, int p)
{
	//region ���ɵ�ַ
	int adress, d = 0, d_len = 0;//d_len��α��������鳤��
	adress = (26 - ('z' - one_name[0])) + (26 - ('z' - one_name[one_name.length() - 1]));
	adress = adress % p;
	while (adress >= hash_len)//�����ַ������ϣ��
	{
		adress = adress - hash_len;
	}
	//endregion
	if (names[adress] == "")
	{
		names[adress] = one_name;
	} 
	else//�����ͻ
	{
		while (names[adress] != "")
		{
			d = (d + p) % hash_len;//α�����������
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
		else//������ͻ
		{
			d = (d + p) % hash_len;//α�����������
			d_len--;
			if (d_len < 0)
			{
				return "��";
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
	int p;//������hash_len���������
	int d_len;
	cout << "����������" << endl;
	cin >> man_len;
	int hash_len = man_len * 2;
	float R = man_len * 1.0 / hash_len;//װ������
	float S = -1 / R * log(1 - R);//���ҳɹ�ƽ�����ҳ���
	cout << "ƽ�����ҳ���:" << S << endl;

	string *names = new string[hash_len];
	p = (hash_len / 2 == hash_len / 2.0) ? (hash_len - 1) : (hash_len - 2);
	
	cout << "��������������:" << endl;
	for (int i = 0; i < man_len; i++)
	{
		string one_name;
		cin >> one_name;
		d_len = create_key(one_name, names, hash_len, p);
	}
	
	while (true)
	{
		cout << "��ϣ�����ɹ�,����ƴ���������в�ѯ,��q�˳�" << endl;
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
