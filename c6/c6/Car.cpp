#include "Car.h"
#include <iostream>
using namespace std;
Car::Car(int wheels, int weight, int passenger_count):Vehicle(wheels, weight)
{
	cout << "小汽车构造方法" << endl;
	this->wheels = wheels;
	this->weight = weight;
	this->passenger_load = new Passenger_load(passenger_count);
	cout << "轮子个数:" << this->wheels << endl;
	cout << "汽车重量:" << this->weight << endl;
}
Car::~Car()
{
	delete	this->passenger_load;
	this->passenger_load = NULL;
}