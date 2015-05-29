#ifndef _BIKEBASE_H_
#define _BIKEBASE_H_

#include "standard.h"
#include <list>

typedef struct HNodeRecord{
	Licencse license;
	BikePtr bikePtr;
}HNodeRecord;

typedef std::list<HNodeRecord> HNode; 

class Bikebase{
public:
	Bikebase(size_t table_size);
	~Bikebase();
	
	/*
		get(license):
		find bikeptr in the hashtable by the unique license number
		and return the bikeptr

		Return:
		when success, BikePtr
		when failed, null
	*/
	BikePtr get(LicencseType license);
	
	/*
		remove(license):
		remove the bikeptr from hashtable. Note, Bikebase will not handle the memory management

		Return:
		when success, true
		when failed, false
	*/
	bool remove(LicencseType license);

	/*
		insert(bikeptr):
		insert a bikeptr into the hashtable
	*/
	void insert(BikePtr bikeptr);
	
	/*
		report():
		print the hash_table status
	*/
	String report();
private:
	HNode *hash_table;
	unsigned int bike_num;

	/*
		toHash(license):
		hash function
	*/
	Hashcode toHash(LicencseType license);
};

#endif