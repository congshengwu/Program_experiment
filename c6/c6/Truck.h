#pragma once
#include "Vehicle.h"
#include "Passenger_load.h"
#include "Payload.h"
class Truck:private Vehicle
{
public:
	Truck(int wheels, int weight, int passenger_count, int payload_count);
	~Truck();
private:
	Passenger_load *passenger_load;
	Payload *payload;
};