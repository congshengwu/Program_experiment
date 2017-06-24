#pragma once
#include "Vehicle.h"
#include "Passenger_load.h"
class Car :private Vehicle
{
public:
	Car(int wheels, int weight, int passenger_load);
	~Car();
private:
	Passenger_load *passenger_load;
};