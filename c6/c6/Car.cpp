#include "Car.h"
#include <iostream>
using namespace std;
Car::Car(int wheels, int weight, int passenger_count):Vehicle(wheels, weight)
{
	cout << "С�������췽��" << endl;
	this->wheels = wheels;
	this->weight = weight;
	this->passenger_load = new Passenger_load(passenger_count);
	cout << "���Ӹ���:" << this->wheels << endl;
	cout << "��������:" << this->weight << endl;
}
Car::~Car()
{
	delete	this->passenger_load;
	this->passenger_load = NULL;
}