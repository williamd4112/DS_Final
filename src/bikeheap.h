#ifndef _HEAP_H_
#define _HEAP_H_

#include "standard.h"
#include "bike.h"

bool bikePtrCmp(const BikePtr a, const BikePtr b);

class BikeHeap {
public:
	class Iterator;

	BikeHeap();
	~BikeHeap();

	/*
		size():
		return the size of the heap
	*/
	int size();

	/*
		empty():
		check the heap is empty
	*/
	bool empty();

	/*
		top():
		retrieve the first element in the heap
	*/
	BikePtr top();

	/*
		pop():
		dicard the first element in the heap
	*/
	BikePtr pop();

	/*
		insert(ptr):
		insert a Bike into the vector and update
		@throw NullpointerException: when passing null pointer
	*/
	void insert(BikePtr ptr);

	/*
		deletes(ptr):
		delete a Bike of the vector and update all bikes' cursor
	*/
	void deletes(BikePtr bikeptr);

	Iterator begin();
	Iterator end();

	/* Custom Iterator */
	class Iterator {
	public:
		Iterator() {

		}

		Iterator(const std::vector<BikePtr>::iterator& it): it(it) {

		}

		~Iterator() {

		}

		BikePtr operator *() {
			return *it;
		}

		Iterator& operator ++() {
			it++;
			return *this;
		}

		bool operator ==(const Iterator& b) {
			return it == b.it;
		}

		bool operator !=(const Iterator& b) {
			return it != b.it;
		}
	private:
		std::vector<BikePtr>::iterator it;
	};
private:
	std::vector<BikePtr> heap;
	int heapsize;

	/*
		find(bikeptr):
		find the index of the passing bikeptr

		return 0 when not found, a non-zero positive number when found
	*/
	int find(BikePtr bikeptr);

	void bubble_up(int currentnode, BikePtr e);
	void bubble_down(int currentnode, BikePtr e);

	void dbg();
};

#endif