#include "Vehicle.h"
#include "Car.h"
#include "Truck.h"
#include <iostream>
using namespace std;

int main()
{
	Car *car = new Car(4, 250, 5);
	Truck truck(6, 500, 3, 500);
	system("pause");
	delete car;
	car = NULL;
	return 0;
}