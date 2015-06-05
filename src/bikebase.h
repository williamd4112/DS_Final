#ifndef _BIKEBASE_H_
#define _BIKEBASE_H_

#include "standard.h"
#include "bike.h"
#include <list>

typedef std::list<BikePtr> HNode; 

extern String UBIKE_REPORT_FREEBIKES_FIELDS[];
extern String UBIKE_REPORT_TOTAL_FIELDS[];

class Bikebase{
public:
	Bikebase(size_t table_size);
	~Bikebase();
	
	/*
		get(license):
		find bikeptr in the hashtable by the unique license number
		and return the bikeptr

		@throw LicenseNotFoundException: when license not found in the table
		@throw NullPointerException: when encounterd null pointer
	*/
	BikePtr get(LicenseType license);
	
	/*
		remove(license):
		remove the bikeptr from hashtable. Note, Bikebase will not handle the memory management

		@throw NullpointerException: when passing null pointer
	*/
	void remove(BikePtr bikeptr);

	/*
		add(LicenseType license, Mileage mile, BikeType bikeType, StationType station):
		create a new bike pointer in the bikebase 
	*/
	BikePtr add(LicenseType license, Mileage mile, BikeType bikeType, StationType station);
	
	void report();

	BikePtr operator [](const LicenseType license);
private:

	/* Hastable instance */
	std::vector<HNode> hash_table;
	
	/* Number of bikes */
	unsigned int bike_num;
	
	/* HashTable size */
	size_t table_size;

	/*
		toHash(license):
		hash function
	*/
	Hashcode toHash(LicenseType license);
};

#endif