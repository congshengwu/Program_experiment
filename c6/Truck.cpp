#include "Truck.h"
#include <iostream>
using namespace std;

Truck::Truck(int wheels, int weight, int passenger_count, int payload_count):Vehicle(wheels, weight)
{
	cout << "�������췽��" << endl;
	this->wheels = wheels;
	this->weight = weight;
	this->passenger_load = new Passenger_load(passenger_count);
	this->payload = new Payload(payload_count);
	cout << "���Ӹ�����" << this->wheels << endl;
	cout << "����������" << this->weight << endl;
}

Truck::~Truck()
{
	delete this->passenger_load;
	delete this->payload;
	this->passenger_load = NULL;
	this->payload = NULL;
}