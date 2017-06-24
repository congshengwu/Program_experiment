#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;
int main()
{
	string str;
	string new_str;
	bool isEqual = false;
	//cout << "请输入任意字符串:" << endl;
	cin >> str;
	int length = 1;//默认长度
	for (int i = 0; i < str.length() ; i++)
	{
		if ((i != str.length() - 1) && str[i] == str[i + 1])
		{
			length++;
			continue;
		}
		else
		{
			new_str.append(str.substr(i, 1));//添加数字
			new_str.append(to_string(length));//添加长度
			length = 1;//长度归位
		}
	}
	cout << new_str << endl;
	system("pause");
	return 0;
}
