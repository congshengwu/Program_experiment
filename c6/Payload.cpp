#include "Payload.h"
#include <iostream>
using namespace std;
Payload::Payload(int payload_count)
{
	this->payload_count = payload_count;
	cout << "������Ϊ��" << payload_count << endl;
}