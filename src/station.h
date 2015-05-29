#ifndef _STATION_H_
#define _STATION_H_

#include "standard.h"

class Station {
public:
	Station(StationType type);
	~Station();

	/*
		rent(type):
		returns a bikeptr from heap according the passed type
	*/
	BikePtr rent(BikeType type);

	/*
		junk(bikeptr):
		remove the bike from heap. Note, just remove the pointer, no free the memory
	*/
	void junk(BikePtr bikeptr);

	/*
		returns(BikePtr bikeptr, Mileage returnMile, bool isDiscount):
		add the bike to the heap
	*/
	void returns(BikePtr bikeptr, Mileage returnMile, bool isDiscount);

	/*
		report():
		print the status of the station
	*/
	String report();
private:
	
	static DiscountRecord discount_table;

	int net; /* total income of station */
	int netElectric;
	int netLady;
	int netRoad;
	int netHybrid;
	int numElectric; /* number of electric bikes */
	int numLady; /* number of lady bikes */
	int numRoad; /* number of road bikes */
	int numHybrid; /* number of hybrid bikes */
	BikeHeap hRent;
	BikeHeap hElectric;
	BikeHeap hLady;
	BikeHeap hRoad;
	BikeHeap hHybrid;
};

#endif