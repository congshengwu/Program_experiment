#include "Vehicle.h"
#include <iostream>
using namespace std;
Vehicle::Vehicle(int wheels, int weight)
{
	this->wheels = wheels;
	this->weight = weight;
	cout << "Vehicle���캯��" << endl;
}