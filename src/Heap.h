#ifndef _HEAP_H_
#define _HEAP_H_

#include "standard.h"

bool bikePtrCmp(const BikePtr a, const BikePtr b){
	if(a != NULL && b != NULL)
		return a->mileage > b->mileage;
	else
		return false;
}

class BikeHeap {
public:
	BikeHeap();
	~BikeHeap();

	/*
		insert(ptr):
		insert a Bike into the vector and update
	*/
	void insert(BikePtr ptr);

	/*
		deletes(ptr):
		delete a Bike into the vector and update
	*/
	void deletes(CursorType cursor);

	/*
		update():
		heaplify the vectory again
		and refresh all bikes' cursor in the heap
	*/
	void update();
private:
	vector<BikePtr> heap;
};

#endif