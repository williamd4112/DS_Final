#ifndef _BIKE_H_
#define _BIKE_H_

#include "standard.h"

class Bike;
typedef BikePtr Bike*;

class Bike {
public:
	Bike(LicenseType license, Mileage Mile, BikeType bikeType, StationType station);
	~Bike();

	void trans(StationType station);
	void rent(StationType station);
	void returns(StationType station);
private:
	LicenseType license;
	StatusType status;
	Mileage mileage; 
	CursorType cursor;
	StationType station;
	BikeType type;
};

#endif