#ifndef _BIKE_H_
#define _BIKE_H_

#include "standard.h"

// Forward declartion
class Station;
class Bikebase;
class BikeHeap;
class Bike;
typedef Bike* BikePtr;
typedef std::vector<BikePtr>::iterator BikeHeapCursor;

class Bike {
friend class Bikebase;
friend class Station;
friend class BikeHeap;
public:
	// Complete bike constructor
	Bike(LicenseType license, Mileage mile, BikeType bikeType, StationType stationType);
	
	// Dummy bike constructor
	Bike(LicenseType license);
	
	~Bike();

	/*
		trans(station):
		set bike's station to new station
		
		@throw BikeonRented: when call RENTED bike
	*/
	void trans(StationType station);
	
	/*
		rent():
		set status to RENTED
	*/
	void rent();
	
	/*
		returns(returnMile):
		set status to FREE
		NOTE: NO set bike's station by passing new station
		increment mile by returnMile
	*/
	void returns(Mileage returnMile);
	
	/*
		setCursor(_cursor):
		set position in the station heap, accelerate removing from heap
		always called by station's function update() when heap was updated(pop, delete, insert)
	*/
	void setCursor(BikeHeapCursor _cursor);
	
	LicenseType getLicense() const;
	Mileage getMile() const;
	BikeType getBikeType() const;
	StationType getStationType() const;
	StatusType getStatus() const;
	
	bool operator ==(const Bike b);
	friend std::ostream& operator <<(std::ostream& os, const Bike& b);
private:

	/* License Number */
	LicenseType license;
	
	/* Accumulated mileages */
	Mileage mile; 
	
	/* BikeType: 	
		Electric,
		Lady,
		Road,
		Hybrid 
	*/
	const BikeType bikeType;
	
	/*
		StationType:
		12 kinds of station
	*/
	StationType stationType;
	
	/*
		FREE, RENTED
	*/
	StatusType status;
	
	/*
		Position in the heap, updated by heap always before any heap operations
	*/
	BikeHeapCursor cursor;
};

#endif