#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;
int main()
{
	string str;
	string new_str;
	bool isEqual = false;
	//cout << "�����������ַ���:" << endl;
	cin >> str;
	int length = 1;//Ĭ�ϳ���
	for (int i = 0; i < str.length() ; i++)
	{
		if ((i != str.length() - 1) && str[i] == str[i + 1])
		{
			length++;
			continue;
		}
		else
		{
			new_str.append(str.substr(i, 1));
			new_str.append(to_string(length));
			length = 1;
		}
	}
	cout << new_str << endl;
	system("pause");
	return 0;
}
