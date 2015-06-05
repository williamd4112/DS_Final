#ifndef _STATION_H_
#define _STATION_H_

#include "standard.h"
#include "bikeheap.h"
#include "bike.h"

class Station {
public:
	Station(StationType type);
	~Station();
	
	/*
		add(BikePtr bikeptr):
		add a bike to the corresponding heap
	*/
	void add(BikePtr bikeptr);
	
	/*
		rent(type):
		returns a bikeptr from heap according the passed type
	*/
	void rent(BikeType type);

	/*
		remove(bikeptr):
		remove the bike from heap. Note, just remove the pointer, no free the memory
	*/
	void remove(BikePtr bikeptr);

	/*
		returns(BikePtr bikeptr, Mileage returnMile):
		delete from rent heap
		add the bike to the appropriate heap
		call bike's return function
	*/
	void returns(BikePtr bikeptr, Mileage returnMile);
	
	/*
		charge(profit):
		increment the net of the station
	*/
	void charge(BikeType bikeType, int profit);
	
	/*
		getMetrics():
		get 5 metrics of this station
		Net, Electric, Lady, Road, Hybrid
	*/
	std::vector<int> getMetrics();
	
	/*
		print the status of the station
	*/
	void report();
	void report_net();
private:

	StationType stationType;
	
	 /* total income of station */
	int net;
	int netType[NUM_TYPE_OF_BIKE];
	
	BikeHeap bikeheaps[NUM_TYPE_OF_BIKE];
	BikeHeap rentheap;
};

#endif